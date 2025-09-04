# TLE8110EE SPI 디버깅 가이드 (T32 사용)

## 🎯 목적
- 진단 기능 완전 비활성화
- T32로 각 레지스터별 SPI 통신 개별 테스트
- 값 일관성 문제 추적 및 원인 분석

## 📋 사용법

### 1. 파일 교체
```
기존: SSVCU/Asw/LSD_Driver.c
교체: SSVCU_DEBUG/LSD_Driver_Debug.c로 교체
```

### 2. T32에서 확인할 변수들

#### 🔧 테스트 제어 변수
```t32
; 테스트 번호 설정 (T32에서 직접 변경)
vLSD_Testnum = 1    ; DEVS 읽기
vLSD_Testnum = 3    ; OUT 읽기  
vLSD_Testnum = 5    ; ISA 읽기
vLSD_Testnum = 7    ; ISB 읽기
vLSD_Testnum = 9    ; PM 읽기
vLSD_Testnum = 99   ; 연속 테스트 (DEVS 10번)
vLSD_Testnum = 0    ; 테스트 중지
```

#### 📊 결과 확인 변수
```t32
; 읽은 데이터 확인
vLSD_DEVS_R.word    ; DEVS 레지스터 읽기 결과
vLSD_OUT_R.word     ; OUT 레지스터 읽기 결과
vLSD_ISA_R.word     ; ISA 레지스터 읽기 결과
vLSD_ISB_R.word     ; ISB 레지스터 읽기 결과
vLSD_PM_R.word      ; PM 레지스터 읽기 결과
```

#### 🔍 디버그 정보 변수
```t32
; 일관성 추적
vLSD_Debug_LastRead     ; 마지막 읽은 값
vLSD_Debug_ReadCount    ; 총 읽기 횟수
vLSD_Debug_SameCount    ; 같은 값 연속 횟수
vLSD_Debug_DiffCount    ; 다른 값 횟수 

; 히스토리 (최근 10개 값)
vLSD_Debug_History[0]   ; 가장 최근 값
vLSD_Debug_History[1]   ; 2번째 최근 값
...
vLSD_Debug_History[9]   ; 10번째 최근 값

; 에러 플래그
vLSD_Debug_ErrorFlags   ; bit0: 타임아웃, bit1: SPI에러
```

## 📝 테스트 시나리오

### 시나리오 1: 기본 레지스터 읽기 테스트
```t32
; DEVS 레지스터 테스트
vLSD_Testnum = 1
; 100ms 후 결과 확인
print "DEVS:", vLSD_DEVS_R.word
print "ReadCount:", vLSD_Debug_ReadCount
print "ErrorFlags:", vLSD_Debug_ErrorFlags

; OUT 레지스터 테스트  
vLSD_Testnum = 3
; 100ms 후 결과 확인
print "OUT:", vLSD_OUT_R.word

; 각 레지스터별로 순차 테스트...
```

### 시나리오 2: 일관성 테스트
```t32
; 같은 레지스터 연속 테스트
vLSD_Testnum = 1
; 1초 대기 후 카운터 초기화
vLSD_Debug_ReadCount = 0
vLSD_Debug_SameCount = 0  
vLSD_Debug_DiffCount = 0

; 10초간 대기하며 일관성 확인
; ReadCount가 증가하면서 SameCount와 DiffCount 비율 확인
```

### 시나리오 3: 히스토리 분석
```t32
; 연속 테스트 실행
vLSD_Testnum = 99

; 히스토리 배열 출력
print "History[0-4]:", vLSD_Debug_History[0], vLSD_Debug_History[1], vLSD_Debug_History[2], vLSD_Debug_History[3], vLSD_Debug_History[4]
print "History[5-9]:", vLSD_Debug_History[5], vLSD_Debug_History[6], vLSD_Debug_History[7], vLSD_Debug_History[8], vLSD_Debug_History[9]
```

## 🔍 문제 분석 방법

### Case 1: 타임아웃 에러 (0xFFFF)
```t32
if (vLSD_Debug_ErrorFlags & 0x0001) {
    print "SPI 타임아웃 발생"
    ; SPI 버스 상태 확인 필요
}
```

### Case 2: 완전 랜덤 값
```t32
; 히스토리 확인
if (vLSD_Debug_DiffCount > vLSD_Debug_SameCount * 2) {
    print "값이 너무 자주 변함 - SPI 신호 품질 문제?"
}
```

### Case 3: 특정 패턴
```t32
; 상위 비트만 다른 경우
if ((vLSD_Debug_History[0] & 0x0F00) != (vLSD_Debug_History[1] & 0x0F00)) {
    print "상위 비트 불일치 - 프레임 구성 문제?"
}
```

## ⚠️ 주요 변경사항

### ✅ 완전 비활성화된 것들
- `LSD_100ms()`에서 진단 통신 (DCC_DRACL_CMD, DCC_DRBCL_CMD 등)
- `LSD_ParseDiagVal()` 진단 파싱 로직  
- 모든 채널 fault 감지 및 디바운싱

### ✅ 추가된 디버그 기능
- 각 읽기마다 일관성 추적
- 최근 10개 값 히스토리 저장
- SPI 에러 상태 추적
- 테스트 충돌 방지 (test_busy 플래그)

### ✅ 기존 기능 유지
- 출력 제어 (솔레노이드 등)
- SPI 초기화 및 기본 통신
- CS 제어 타이밍

## 🚨 사용 시 주의사항

1. **테스트 후 원본 복구**: 디버깅 완료 후 원본 LSD_Driver.c로 복구 필요
2. **한 번에 하나씩**: vLSD_Testnum을 자주 바꾸지 말고 충분히 테스트 후 변경
3. **결과 기록**: 각 레지스터별 테스트 결과를 문서화해서 패턴 분석

## 📞 결과 보고 양식

```
=== TLE8110EE SPI 테스트 결과 ===

테스트 조건:
- vLSD_Testnum: [설정값]
- 테스트 시간: [몇 초간]

결과:
- 읽기 횟수: [ReadCount]
- 같은 값: [SameCount]  
- 다른 값: [DiffCount]
- 에러 플래그: [ErrorFlags]
- 최근 5개 값: [History[0-4]]

패턴:
- 완전 랜덤 / 특정 비트만 다름 / 특정 값으로 고정 등
```

이 정보로 문제의 정확한 원인을 찾을 수 있을 것입니다! 🎯