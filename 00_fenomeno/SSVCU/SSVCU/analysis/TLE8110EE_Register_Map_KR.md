# TLE8110EE 레지스터 맵 요약(한글)

본 요약은 Infineon TLE8110EE 데이터시트(Rev.1.4) 기준 주요 레지스터 그룹과 기본 필드 의미를 정리한 것입니다. 실제 적용 시에는 원문 데이터시트를 최우선 참조하세요.

## 주소 그룹(3비트) 개요
- 000b: CMD — Commands (W 전용)
- 001b: DCC — Diagnosis Registers and Compact Control (W 전용)
- 010b: OUTx — 채널 출력 제어 레지스터(CHx) (R/W)
- 011b: DEVS — Device Settings (R/W)
- 100b: MSCS — Reserved (R/W)
- 101b: ISAx — Input or Serial Mode Register CHx Bank A (R/W)
- 110b: ISBx — Input or Serial Mode Register CHx Bank B (R/W)
- 111b: PMx — Parallel Mode Control of CHx with CHy (R/W)

주: CMD/DCC는 Read를 보내도 무시되며 S_SO(Serial Output)에는 ‘0’ 프레임이 반환됩니다.

## 레지스터별 요약(디폴트 값은 리셋 후 값)

- CMD (Addr=000b, Type=W)
  - 용도: 디바이스 명령(예: 클리어/트리거 등). Read 명령은 무시됨.
  - 필드: Command 비트들로 구성.
  - 기본값: —

- DCC (Addr=001b, Type=W)
  - 용도: 진단 관련 레지스터/컴팩트 제어(진단 래치 클리어 등).
  - 필드: Command 비트들로 구성.
  - 기본값: —

- OUTx (Addr=010b, Type=R/W)
  - 용도: 채널 출력 제어(각 채널 ON/OFF 및 관련 모드 비트).
  - 채널: OUT1..OUT10 포함.
  - 리셋 기본값: 0xC00 (데이터시트 표기 기준)

- DEVS (Addr=011b, Type=R/W)
  - 용도: 디바이스 설정(예: 복구/재시도 정책, 입력 디바운스 시간, DCC 관련 옵션 등).
  - 비트 필드(데이터시트 표 기준, 상위→하위 비트):
    - [11] RCP: 복구/정책 관련 비트(정확 의미는 데이터시트 본문 참조)
    - [10] DBT2: 디바운스 시간 선택 비트 2
    - [9]  DBT1: 디바운스 시간 선택 비트 1
    - [8:3] 예약(0)
    - [2] DCC10: DCC 관련 설정(채널군 연계) — 데이터시트 본문 참조
    - [1] DCC9:  DCC 관련 설정(채널군 연계) — 데이터시트 본문 참조
    - [0] DCC18: DCC 관련 설정(채널군 연계) — 데이터시트 본문 참조
  - 리셋 기본값: 0x007 (즉, 비트[2:0]=1,1,1 이고 나머지는 0)
  - 비고: 본 프로젝트에서는 현재 DEVS를 쓰지 않으며(미설정), 리셋 기본값(0x007)에 의존하여 동작합니다.

### DEVS = 0x007일 때 동작(해석)
- 비트 분해: 0x007 = 0000 0000 0111b
  - [11] RCP = 0
  - [10] DBT2 = 0
  - [9]  DBT1 = 0
  - [8:3] = 0
  - [2] DCC10 = 1
  - [1] DCC9  = 1
  - [0] DCC18 = 1

- 의미(데이터시트 표 기준 일반 해석, 정확 동작은 원문 참조 권장):
  - DCC18/DCC9/DCC10 = 1: 진단/컴팩트 제어(DCC) 관련 옵션이 기본 활성 상태. 채널군(1~8, 9, 10)에 대한 DCC 동작이 활성화됨.
  - DBT2:DBT1 = 00: 입력 신호 디바운스 시간 선택이 “기본(최소치/디폴트)”로 설정. 실제 시간 값은 데이터시트의 디바운스 타이밍 표를 따름.
  - RCP = 0: 복구/정책 관련 옵션이 기본(비활성 또는 표준) 상태.

- 본 프로젝트 관점 영향:
  - 현재 코드가 DCC 명령(진단 래치 클리어/진단 읽기)을 사용하므로, DCC 관련 비트가 1인 기본값은 기대 동작과 부합합니다.
  - 디바운스 시간(DBT)이 기본값이므로, 외부 입력(병렬 제어 사용 시)의 노이즈 환경에 따라 필요하면 DEVS에서 디바운스 시간을 명시적으로 조정하는 것이 좋습니다.
  - RCP가 0이므로, 특수 복구 정책을 요구하지 않는 한 기본값 유지로도 정상 동작 가능. 정책 변경 필요 시 DEVS를 Write로 설정 권장.

### RCP 비트(Reverse Current Compensation) 설명
- 의미: RCP=1로 설정하면 모든 채널에 대해 “역전류 보정(Reverse Current Compensation)” 기능이 활성화됩니다.
- 효과(일반적 해석):
  - 부하/배선 조건상 역방향 전류가 흐를 수 있는 상황(병렬 채널, 외부 구동원, 모터 역기전력, 다른 채널의 바디 다이오드 경유 등)에서, 내부 진단(오픈/쇼트 판정)과 전류감지 동작이 역전류로 인해 오동작/오검출되지 않도록 보정합니다.
  - 특히 PWM 동작이나 채널 간 상호작용으로 순간적인 역전류가 발생할 때, 불필요한 Fault 판정을 줄이는 데 도움이 됩니다.
- 유의사항:
  - RCP 활성화 시 일부 진단 민감도/임계가 보정되므로, 시스템 요구에 따라 오픈로드/과전류 검출 특성이 달라질 수 있습니다. 데이터시트의 해당 장/주석(타이밍·조건)을 반드시 확인하세요.
  - 기본값(RCP=0)으로 문제가 없다면 굳이 변경할 필요는 없습니다. 역전류로 인한 오검출(예: 유도성 부하, 병렬 채널 구성) 이슈가 관찰될 때 RCP=1을 고려하십시오.

- MSCS (Addr=100b, Type=R/W)
  - 용도: 예약됨(Reserved).
  - 기본값: 0x000

- ISAx (Addr=101b, Type=R/W)
  - 용도: 채널 Bank A 입력/시리얼 모드 설정(IS1..IS6 등).
  - 기본값: 0xAAA

- ISBx (Addr=110b, Type=R/W)
  - 용도: 채널 Bank B 입력/시리얼 모드 설정(IS7..IS10 등).
  - 기본값: 0x0AA

- PMx (Addr=111b, Type=R/W)
  - 용도: 채널 병렬 모드 제어(채널 페어링: PM12, PM23, PM34, PM56, PM78, PM89, PM91 등).
  - 기본값: 0x000

## 통신 프레임 관련 주의
- 프레임 길이: 16비트(MSB first)
- R/W: 프레임 MSB(비트15) — 1=Read, 0=Write
- 응답 지연: 1프레임 지연(one‑frame latency) — 보낸 명령의 결과는 다음 프레임에서 반환
- CS: 명령당 CS Low→High 토글로 16비트 단위 트랜잭션 구성

## 진단 상태코드(요약)
- 채널별 2비트 코드: 00=GND 쇼트, 01=오픈 로드, 02=과부하/과전류, 03=정상
- DRA(채널1~6), DRB(채널7~10)에서 읽어 해석(진단 클리어는 DCC로 수행)

참고: 상세 비트필드/타이밍/경계조건은 데이터시트 각 장(특히 12.3.x)을 확인하세요.

## 본 프로젝트 사용 현황(코드 매핑)
- 사용 그룹: 주로 DCC(001b)만 사용. OUTx/DEVS/ISAx/ISBx/PMx는 현재 미사용.

- 사용 레지스터/명령(모두 DCC Write로 요청 후, 다음 프레임에 결과 수신)
  - DRACL (Addr=001b 내 0x100): 진단 래치 클리어 A
    - 코드 상 정의: `DRACL_CMD (0x100)` → `DCC_DRACL_CMD`
    - 사용 위치: `Asw/LSD_Driver.c:205` (`LSD_100ms()`에서 먼저 전송)
  - DRBCL (Addr=001b 내 0x200): 진단 래치 클리어 B
    - 코드 상 정의: `DRBCL_CMD (0x200)` → `DCC_DRBCL_CMD`
    - 사용 위치: `Asw/LSD_Driver.c:206`
  - DRA (Addr=001b 내 0x500): 진단 레지스터 A 읽기 요청(채널 1~6 상태)
    - 코드 상 정의: `DRA_CMD (0x500)` → `DCC_DRA_CMD`
    - 사용 위치: `Asw/LSD_Driver.c:208`
    - 주의: 실제 DRA 값은 “다음 프레임”에서 수신되어 `LSD_100ms()` 내 `LSD_DRA_Val`에 저장됨(`:209`)
  - DRB (Addr=001b 내 0x600): 진단 레지스터 B 읽기 요청(채널 7~10 상태)
    - 코드 상 정의: `DRB_CMD (0x600)` → `DCC_DRB_CMD`
    - 사용 위치: `Asw/LSD_Driver.c:209`
    - 주의: 실제 DRB 값은 그 다음 프레임에서 수신되어 `LSD_DRB_Val`에 저장됨(`:210`)

- 프레임 형식(코드 조립 방식)
  - R/W(비트15)=0(Write), DCC(비트12)=1, 하위 어드레스 코드(DRACL/DRBCL/DRA/DRB)를 OR 조합
    - 예: `DCC_DRA_CMD = (WRITE_CMD /*0*/ | DCC_CMD /*1<<12*/ | DRA_CMD /*0x500*/)`
  - 전송 API: `HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&cmd, (uint8_t*)&response, 1, SPI2_TIMEOUT_MS)`
    - CS 제어: `PB12` GPIO 수동 토글(`LSD_Select/LSD_deSelect`)

- 파이프라인 순서(지연 응답 처리)
  1) `DRACL` → 2) `DRBCL` → 3) `DRA` 요청(수신은 이전 프레임 더미) → 4) 수신값을 `LSD_DRA_Val`에 반영하며 동시에 `DRB` 요청 → 5) 다음 수신값을 `LSD_DRB_Val`에 반영
  - 구현: `Asw/LSD_Driver.c:205`~`:210`
  - 해석/디바운싱: `LSD_ParseDiagVal()`에서 채널별 2비트 상태코드(00/01/02/03)를 읽어 `LSD_channelFault[]` 갱신

- 미사용 항목(현재 시점)
  - OUTx(출력 제어), DEVS(디바이스 설정), ISAx/ISBx(입력/시리얼 모드), PMx(병렬 모드)는 코드에서 직접 접근/설정하지 않음
  - 따라서 현재 프로젝트는 “진단(Read) 중심 + 진단 래치 클리어(Write)” 수준으로 TLE8110EE를 사용 중
