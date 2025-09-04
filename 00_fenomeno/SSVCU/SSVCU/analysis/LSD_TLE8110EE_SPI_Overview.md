# LSD(TLE8110EE) SPI 통신 및 모듈 동작 개요

본 문서는 SSVCU 프로젝트 내 TLE8110EE(Lower Side Driver, 이하 LSD)와의 SPI 통신 구조 및 모듈 동작 흐름을 시스템 파악용으로 정리한 것입니다. 후속 질문/분석 결과는 본 문서에 계속 업데이트합니다.

## 하드웨어/핀 구성
- EN/RST 핀: `PE14(TLE8110ED_EN)`, `PE15(TLE8110ED_RST)`
  - 정의: `Core/Inc/main.h:91` ~ `Core/Inc/main.h:94`
  - 제어: `Asw/CtrlPin.c:172` ~ `Asw/CtrlPin.c:189`
- SPI: `SPI2` 사용, CS는 수동 GPIO 제어 `PB12`
  - CS Low/High: `Asw/LSD_Driver.c:150` ~ `Asw/LSD_Driver.c:157`

## SPI 설정(큐브MX/HAL)
- 인스턴스: `SPI2`
- 파라미터: 16비트, MSB First, CPOL=LOW, CPHA=2EDGE, NSS=SOFT, 분주=64
  - 설정: `Core/Src/spi.c:43` ~ `Core/Src/spi.c:48`

## 프로토콜 핵심
- 프레임 크기: 16비트(MSB first)
- 응답 지연: 1 프레임 지연(one‑frame latency). 보낸 명령의 결과는 다음 프레임에서 수신
- 명령 구성(일부):
  - R/W 비트: bit15 (1=Read, 0=Write)
  - DCC 그룹: bit12
  - DRA/DRB(진단), DRACL/DRBCL(클리어) 등
- 상태코드(채널별 2비트): 00=Short, 01=Open, 02=Overload, 03=No error

## 통신 시퀀스(코드 구현)
- 전송: `HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&cmd, (uint8_t*)&response, 1, SPI2_TIMEOUT_MS)`
  - 호출 위치: `Asw/LSD_Driver.c:176`
  - 준비 대기/타임아웃 처리 포함: `Asw/LSD_Driver.c:165` ~ `Asw/LSD_Driver.c:173`
- CS 제어: 프레임 단위로 `PB12` Low→TxRx→High
  - `LSD_Select()/LSD_deSelect()`: `Asw/LSD_Driver.c:150` ~ `Asw/LSD_Driver.c:157`
- 파이프라인(지연 응답 처리):
  - DRACL → DRBCL → DRA요청 → (응답)DRB → DRB요청 → (응답)DRA 순으로 더미/요청을 교차
  - 구현: `Asw/LSD_Driver.c:205` ~ `Asw/LSD_Driver.c:210`

## 모듈 동작(태스크 연계)
- 초기화: `LSD_init()`
  - EN High, RST Inactive(High) 설정, CS 핀(`PB12`) 출력 초기화
  - 위치: `Asw/LSD_Driver.c` (EN/RST 제어는 `Asw/CtrlPin.c` 참조)
- 주기 함수:
  - 10ms: `LSD_Proc_10ms()` — 상위 입력 취득/출력 반영(현재 SPI 없음)
    - 호출: `Core/Src/freertos.c:230`
  - 100ms: `LSD_100ms()` — SPI 기반 진단 읽기/파싱 수행
    - 호출: `Core/Src/freertos.c:306`
- 외부 조회 API: `LSD_getChannel_diagVal(channel)` — 디바운싱 반영된 채널 진단 결과 리턴

## 간단 요약: 주요 함수가 하는 일
- `LSD_init()`
  - EN 핀을 켜고(칩 전원/활성), RST를 비활성(High)로 둡니다.
  - SPI의 칩셀렉트용 `PB12`를 출력으로 설정하고 기본값 High(미선택)으로 올려 둡니다.
  - SPI 레지스터 초기화는 여기서 하지 않습니다(별도 `Core/Src/spi.c`).
  - 위치: `Asw/LSD_Driver.c` / EN/RST 제어 함수: `Asw/CtrlPin.c:172`~`189`.

- `LSD_Proc_10ms()`
  - 상위 모듈이 준 목표값을 가져와(`LSD_Get_Data`), 실제 출력을 갱신합니다(`LSD_Set_Data`).
  - 예: 좌/우 솔레노이드 목표 상태를 읽어서 해당 액추에이터를 켜고 끕니다.
  - SPI 통신은 하지 않습니다(순수 로직/제어만 수행).
  - 호출: `Core/Src/freertos.c:230`.

- `LSD_getChannel_diagVal(channel)`
  - 최근 100ms 주기에 수집·디바운싱된 채널 진단 결과를 반환합니다.
  - 반환: `0` 정상, `1` 이상(오픈/쇼트/과전류 등). 인자는 0부터의 채널 인덱스.
  - 진단 데이터는 `LSD_100ms()`에서 SPI로 읽고 해석합니다.

## 현재 기능 범위 요약
- 통신: 16비트 SPI 블로킹 전송, CS 수동 토글, one‑frame latency 처리 구현 완료
- 사용 용도: 주로 진단(Read) 중심. 래치/에러 클리어는 Write 사용. 채널 On/Off 쓰기 제어는 미구현

## 개선 포인트(요약)
- 타임아웃 1ms → 2~5ms 여유 및 `HAL_StatusTypeDef` 체크/로깅/재시도 추가
- RST 시퀀스 명시화(EN High → RST Low≥tRST → High)
- 상위 추상화(TLF 스타일): 레지스터 주소 enum/구조체, 기능별 API(`LSD_ReadDiag`, `LSD_ClearLatchedErrors`, 추후 `LSD_SetChannel`)로 가독성/재사용성 향상
- 필요 시 IT/DMA+콜백으로 전환하여 완료 시점에 CS High 복귀/에러 핸들링 일원화

## 참고 파일/라인
- `Core/Inc/main.h:91` ~ `Core/Inc/main.h:94`
- `Core/Src/spi.c:43` ~ `Core/Src/spi.c:48`
- `Asw/LSD_Driver.c:150` ~ `Asw/LSD_Driver.c:176`, `Asw/LSD_Driver.c:205` ~ `Asw/LSD_Driver.c:210`
- `Core/Src/freertos.c:230`, `Core/Src/freertos.c:306`
- `Asw/CtrlPin.c:172` ~ `Asw/CtrlPin.c:189`
