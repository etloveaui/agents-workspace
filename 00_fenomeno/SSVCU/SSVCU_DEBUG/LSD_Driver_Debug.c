/*
 * LSD_Driver_Debug.c - 진단 비활성화 + T32 테스트 전용 버전
 *
 *  Created on: Mar 2, 2025
 *      Author: sungsoo (modified for debug)
 */

#include "LSD_Driver.h"
#include "ifc.h"
#include "gpio.h"
#include "spi.h"
#include "CtrlPin.h"

// 진단 완전 비활성화
// #define FOR_LSD_DEBUG

// ===== 기존 진단 관련 변수들 (사용 안 함) =====
uint16_t LSD_DRA_Val = 0;
uint16_t LSD_DRB_Val = 0;
uint16_t cmd_DRA = DCC_DRA_CMD;
uint16_t cmd_DRB = DCC_DRB_CMD;
uint8_t LSD_tempStatVal = 0;
uint8_t LSD_channelFault[CHANNEL_MAX] = {0};
static uint8_t LSD_channelDiag_NormalCnt[CHANNEL_MAX] = {0};
static uint8_t LSD_channelDiag_abNormalCnt[CHANNEL_MAX] = {0};

// ===== 출력 제어 관련 (기존 유지) =====
uint8_t tmp_SwtMixer = 0;
uint8_t tmp_StSolnLD = 0;
uint8_t tmp_StSolnRD = 0;
uint8_t tmp_SwtHdLamp = 0;
uint8_t tmp_SwtEmgy = 0;
uint8_t tmp_SwtAutoCtrl = 0;

// ===== 테스트 전용 변수들 =====
LSD_DEVS_t vLSD_DEVS_R;
LSD_DEVS_t vLSD_DEVS_W;
LSD_OUT_t  vLSD_OUT_R;
LSD_OUT_t  vLSD_OUT_W;
LSD_ISA_t  vLSD_ISA_R;
LSD_ISA_t  vLSD_ISA_W;
LSD_ISB_t  vLSD_ISB_R;
LSD_ISB_t  vLSD_ISB_W;
LSD_PM_t   vLSD_PM_R;
LSD_PM_t   vLSD_PM_W;

uint8_t vLSD_Testnum = 0;  // T32에서 이 값을 변경

// ===== 디버그 추가 변수들 =====
uint16_t vLSD_Debug_LastRead = 0;      // 마지막 읽은 값
uint16_t vLSD_Debug_ReadCount = 0;     // 읽기 횟수
uint16_t vLSD_Debug_SameCount = 0;     // 같은 값 연속 횟수
uint16_t vLSD_Debug_DiffCount = 0;     // 다른 값 횟수
uint16_t vLSD_Debug_History[10] = {0}; // 최근 10개 값 히스토리
uint8_t  vLSD_Debug_HistoryIdx = 0;    // 히스토리 인덱스
uint16_t vLSD_Debug_ErrorFlags = 0;    // 에러 플래그

// ===== 진단 파싱 함수 (완전 비활성화) =====
static void LSD_ParseDiagVal(void)
{
    // 진단 로직 완전 비활성화 - 아무것도 안 함
    return;
}

// ===== SPI 기본 함수들 (기존 유지) =====
static inline void LSD_Select(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
}

static inline void LSD_deSelect(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

static uint16_t LSD_TransmitReceive(uint16_t cmd)
{
    uint16_t response = 0xFFFF;
    uint32_t startTick = HAL_GetTick();

    LSD_Select();

    // SPI 준비 상태 대기
    while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
    {
        if ((HAL_GetTick() - startTick) > SPI2_TIMEOUT_MS)
        {
            LSD_deSelect();
            vLSD_Debug_ErrorFlags |= 0x0001;  // 타임아웃 에러
            return 0xFFFF;
        }
    }

    // SPI 통신 실행
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&cmd, (uint8_t*)&response, 1, SPI2_TIMEOUT_MS);
    
    LSD_deSelect();

    // SPI 상태 체크
    if (status != HAL_OK)
    {
        vLSD_Debug_ErrorFlags |= 0x0002;  // SPI 에러
        return 0xFFFF;
    }

    return response;
}

// ===== 통신 함수 (기존 유지) =====
uint16_t LSD_Communication(uint8_t wr, uint8_t addr3, uint8_t sub4, uint8_t data8)
{
    uint16_t frame = 0;
    frame |= ((uint16_t)(wr   & 0x1u) << LSD_SI_WR_SHIFT);
    frame |= ((uint16_t)(addr3 & 0x7u) << LSD_SI_ADDR_SHIFT);
    frame |= ((uint16_t)(sub4  & 0xFu) << LSD_SI_SUB_SHIFT);
    frame |= ((uint16_t)(data8 & 0xFFu) << LSD_SI_DATA_SHIFT);
    return LSD_TransmitReceive(frame);
}

// ===== 디버그용 읽기 함수 (일관성 체크 포함) =====
static inline void lsd_read12_debug(uint8_t addr3, uint16_t* out12)
{
    // 첫 번째 읽기 (더미)
    uint16_t dummy = LSD_Communication(LSD_WR_READ, addr3, 0x0u, 0x00u);
    
    // 두 번째 읽기 (실제 데이터)
    uint16_t rx = LSD_Communication(LSD_WR_READ, addr3, 0x0u, 0x00u);
    uint16_t data = (rx & 0x0FFFu);
    
    // 디버그 정보 업데이트
    vLSD_Debug_ReadCount++;
    
    // 히스토리 저장
    vLSD_Debug_History[vLSD_Debug_HistoryIdx] = data;
    vLSD_Debug_HistoryIdx = (vLSD_Debug_HistoryIdx + 1) % 10;
    
    // 일관성 체크
    if (vLSD_Debug_ReadCount > 1)
    {
        if (vLSD_Debug_LastRead == data)
        {
            vLSD_Debug_SameCount++;
        }
        else
        {
            vLSD_Debug_DiffCount++;
        }
    }
    
    vLSD_Debug_LastRead = data;
    
    if (out12) *out12 = data;
}

static inline void lsd_write12(uint8_t addr3, uint16_t val12)
{
    uint8_t sub4  = (uint8_t)((val12 >> 8) & 0x0Fu);
    uint8_t data8 = (uint8_t)( val12       & 0xFFu);
    (void)LSD_Communication(LSD_WR_WRITE, addr3, sub4, data8);
}

// ===== 레지스터별 읽기/쓰기 함수들 (디버그 버전) =====

/* DEVS */
void LSD_Read_DEVS(LSD_DEVS_t* out)
{
    lsd_read12_debug(LSD_ADDR_DEVS, &out->word);
}

void LSD_Write_DEVS(LSD_DEVS_t in)
{
    uint8_t sub4  = (uint8_t)((in.word >> 8) & 0x0Fu);
    uint8_t data8 = (uint8_t)( in.word       & 0xFFu);
    (void)LSD_Communication(LSD_WR_WRITE, LSD_ADDR_DEVS, sub4, data8);
}

/* OUTx */
void LSD_Read_OUT(LSD_OUT_t* out)
{
    uint16_t v = 0; 
    lsd_read12_debug(LSD_ADDR_OUT, &v);
    if (out) out->word = (v | 0x0C00u);
}

void LSD_Write_OUT(LSD_OUT_t in)
{
    uint16_t v = (in.word & 0x0FFFu);
    v = (v & 0x03FFu) | 0x0C00u;
    lsd_write12(LSD_ADDR_OUT, v);
}

/* ISAx */
void LSD_Read_ISA(LSD_ISA_t* out)
{
    lsd_read12_debug(LSD_ADDR_ISA, &out->word);
}

void LSD_Write_ISA(LSD_ISA_t in)
{
    lsd_write12(LSD_ADDR_ISA, (in.word & 0x0FFFu));
}

/* ISBx */
void LSD_Read_ISB(LSD_ISB_t* out)
{
    lsd_read12_debug(LSD_ADDR_ISB, &out->word);
}

void LSD_Write_ISB(LSD_ISB_t in)
{
    lsd_write12(LSD_ADDR_ISB, (in.word & 0x0FFFu));
}

/* PMx */
void LSD_Read_PM(LSD_PM_t* out)
{
    lsd_read12_debug(LSD_ADDR_PM, &out->word);
}

void LSD_Write_PM(LSD_PM_t in)
{
    lsd_write12(LSD_ADDR_PM, (in.word & 0x0FFFu));
}

// ===== T32 테스트 전용 함수 (개선된 버전) =====
void LSD_Test(void)
{
    static uint8_t test_busy = 0;  // 테스트 진행 중 플래그
    
    // 이미 테스트 진행 중이면 스�ip
    if (test_busy) return;
    
    if (vLSD_Testnum == 0) return;  // 0이면 아무것도 안 함
    
    test_busy = 1;  // 테스트 시작
    
    // 디버그 카운터 초기화 (새로운 테스트 시작 시)
    static uint8_t last_testnum = 0;
    if (last_testnum != vLSD_Testnum)
    {
        vLSD_Debug_ReadCount = 0;
        vLSD_Debug_SameCount = 0;
        vLSD_Debug_DiffCount = 0;
        vLSD_Debug_ErrorFlags = 0;
        vLSD_Debug_HistoryIdx = 0;
        for (int i = 0; i < 10; i++) vLSD_Debug_History[i] = 0;
        last_testnum = vLSD_Testnum;
    }
    
    switch (vLSD_Testnum)
    {
    case 1:
        LSD_Read_DEVS(&vLSD_DEVS_R);
        break;
    case 2:
        LSD_Write_DEVS(vLSD_DEVS_W);
        break;
    case 3:
        LSD_Read_OUT(&vLSD_OUT_R);
        break;
    case 4:
        LSD_Write_OUT(vLSD_OUT_W);
        break;
    case 5:
        LSD_Read_ISA(&vLSD_ISA_R);
        break;
    case 6:
        LSD_Write_ISA(vLSD_ISA_W);
        break;
    case 7:
        LSD_Read_ISB(&vLSD_ISB_R);
        break;
    case 8:
        LSD_Write_ISB(vLSD_ISB_W);
        break;
    case 9:
        LSD_Read_PM(&vLSD_PM_R);
        break;
    case 10:
        LSD_Write_PM(vLSD_PM_W);
        break;
    case 99:  // 연속 테스트 모드
        // 같은 레지스터를 연속으로 10번 읽어서 일관성 체크
        for (int i = 0; i < 10; i++)
        {
            LSD_Read_DEVS(&vLSD_DEVS_R);  // 예: DEVS를 10번 연속 읽기
        }
        break;
    default:
        break;
    }
    
    test_busy = 0;  // 테스트 완료
    // vLSD_Testnum = 0;  // 자동 리셋하지 않음 (T32에서 수동 제어)
}

// ===== 초기화 함수 (기존 유지) =====
void LSD_init(void)
{
    // Lower side Driver
    CtrlPin_TLE8110ED_EN_On();  // Lower side Driver enable
    CtrlPin_TLE8110ED_RST_Off(); // Reset :  Active --> wait 10ms --> Inactive

    // CS 핀 초기화
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // slave deselect
    
    // 디버그 변수 초기화
    vLSD_Debug_ReadCount = 0;
    vLSD_Debug_SameCount = 0;
    vLSD_Debug_DiffCount = 0;
    vLSD_Debug_ErrorFlags = 0;
    vLSD_Debug_HistoryIdx = 0;
    for (int i = 0; i < 10; i++) vLSD_Debug_History[i] = 0;
}

// ===== 100ms 주기 함수 (진단 완전 비활성화) =====
void LSD_100ms(void)
{
    // 기존 진단 로직 완전 제거
    // uint16_t dummy_Cmd = 0;
    // LSD_TransmitReceive(DCC_DRACL_CMD);  // 주석처리
    // LSD_TransmitReceive(DCC_DRBCL_CMD);  // 주석처리
    // dummy_Cmd = LSD_TransmitReceive(cmd_DRA);     // 주석처리
    // LSD_DRA_Val = LSD_TransmitReceive(cmd_DRB);   // 주석처리
    // LSD_DRB_Val = LSD_TransmitReceive(dummy_Cmd); // 주석처리
    // LSD_ParseDiagVal();  // 주석처리

    // 테스트 함수만 실행
    LSD_Test();
}

// ===== 기존 인터페이스 함수들 (dummy로 유지) =====
uint8_t LSD_getChannel_diagVal(uint8_t channelNum)
{
    return 0;  // 진단 비활성화로 항상 0 리턴
}

void LSD_Control_Init(void)
{
    // 기존과 동일
}

void LSD_Set_Data(void)
{
    Set_ActLeftSolenoid(tmp_StSolnLD);
    Set_ActRightSolenoid(tmp_StSolnRD);
}

void LSD_Get_Data(void)
{
    tmp_StSolnLD = Get_TgtLeftSolenoid();
    tmp_StSolnRD = Get_TgtRightSolenoid();
}

void LSD_Proc_10ms(void)
{
    LSD_Get_Data();
    LSD_Set_Data();
}