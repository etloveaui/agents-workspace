/*
 * LSD_Driver.c
 *
 *  Created on: Mar 2, 2025
 *      Author: sungsoo
 */


#include "LSD_Driver.h"
#include "ifc.h"
#include "gpio.h"
#include "spi.h"
#include "CtrlPin.h"

// #define FOR_LSD_DEBUG

uint16_t LSD_DRA_Val;
uint16_t LSD_DRB_Val;

uint16_t cmd_DRA = DCC_DRA_CMD;
uint16_t cmd_DRB = DCC_DRB_CMD;

uint8_t LSD_tempStatVal;

uint8_t LSD_channelFault[CHANNEL_MAX];
static uint8_t LSD_channelDiag_NormalCnt[CHANNEL_MAX];
static uint8_t LSD_channelDiag_abNormalCnt[CHANNEL_MAX];

uint8_t tmp_SwtMixer 				= 0;		// 0 : off, 1 : on
uint8_t tmp_StSolnLD 				= 0;		// 좌측 0 : 전부 open, 1 : '하'만 close(상은 open), 2 : '상'만 close(하는 open) 3 : 전부 close
uint8_t tmp_StSolnRD 				= 0;		// 우측 0 : 전부 open, 1 : '하'만 close(상은 open), 2 : '상'만 close(하는 open) 3 : 전부 close
uint8_t tmp_SwtHdLamp				= 0;		// 헤드램프 1: off, 0 : on
uint8_t tmp_SwtEmgy					= 0;		// 0 : off, 1 : on
uint8_t tmp_SwtAutoCtrl				= 0;		// 0 : off, 1 : on

LSD_DEVS_t vLSD_DEVS_R;
LSD_DEVS_t vLSD_DEVS_W;
LSD_OUT_t  vLSD_OUT_R;
LSD_OUT_t vLSD_OUT_W;
LSD_ISA_t  vLSD_ISA_R;
LSD_ISA_t vLSD_ISA_W;
LSD_ISB_t  vLSD_ISB_R;
LSD_ISB_t vLSD_ISB_W;
LSD_PM_t vLSD_PM_R;
LSD_PM_t vLSD_PM_W;
uint8_t vLSD_Testnum;

static void LSD_ParseDiagVal(void)
{

	if(LSD_DRA_Val == 0xffff || LSD_DRB_Val == 0xffff) return;

	for(uint8_t i = 1; i <= 6; i++) // DRA 값 파싱 (채널 1~6)
	{
		LSD_tempStatVal = GET_DRAn_STAT(i,LSD_DRA_Val);

#ifdef FOR_LSD_DEBUG
		switch(LSD_tempStatVal)
		{
		case 0x00: // Short to GND
			LSD_channelFault[i-1] = 1;
			break;
		case 0x01: // Open Load
			LSD_channelFault[i-1] = 1;
			break;
		case 0x02: // Over Load
			LSD_channelFault[i-1] = 1;
			break;
		case 0x03: // no Err
			LSD_channelFault[i-1] = 0;
			break;
		default:
			break;
		}
#else
		if(LSD_tempStatVal == 0x03)
		{
			LSD_channelDiag_NormalCnt[i - 1]++;
			LSD_channelDiag_abNormalCnt[i - 1] = 0;
		}
		else
		{
			LSD_channelDiag_abNormalCnt[i - 1]++;
			LSD_channelDiag_NormalCnt[i - 1] = 0;
		}

		if(LSD_channelDiag_NormalCnt[i - 1] >= DEBOUNCING_CNT && LSD_tempStatVal == 0x03)
		{
			LSD_channelFault[i - 1] = CHANNEL_NORMAL;
			LSD_channelDiag_NormalCnt[i - 1] = 0;

		}
		else if(LSD_channelDiag_abNormalCnt[i - 1] >= DEBOUNCING_CNT)
		{
			LSD_channelFault[i - 1] = CHANNEL_FAULT;
			LSD_channelDiag_abNormalCnt[i - 1] = 0;
		}
		else{}
#endif
	}

	// reverse_bits(&LSD_DRB_Val); // msb-first 방식이면, 송수신도 똑같은 방식으로 진행됨 -> 그냥 사용하면 된다.

	for(uint8_t i = 7; i <= 10; i++) // DRB 값 파싱 (채널 7~10)
	{
		LSD_tempStatVal = GET_DRBn_STAT(i,LSD_DRB_Val);

#ifdef FOR_LSD_DEBUG
		switch(LSD_tempStatVal)
		{
		case 0x00: // Short to GND
			LSD_channelFault[i-1] = 1;
			break;
		case 0x01: // Open Load
			LSD_channelFault[i-1] = 1;
			break;
		case 0x02: // Over Load
			LSD_channelFault[i-1] = 1;
			break;
		case 0x03: // no Err
			LSD_channelFault[i-1] = 0;
			break;
		default:
			break;
		}
#else

/*
		static uint8_t LSD_channelDiag_NormalCnt[CHANNEL_MAX];
		static uint8_t LSD_channelDiag_abNormalCnt[CHANNEL_MAX];
*/

		if(LSD_tempStatVal == 0x03)
		{
			LSD_channelDiag_NormalCnt[i - 1]++;
			LSD_channelDiag_abNormalCnt[i - 1]=0;
		}
		else
		{
			LSD_channelDiag_abNormalCnt[i - 1]++;
			LSD_channelDiag_NormalCnt[i - 1] = 0;
		}

		//prevFault_flag = LSD_channelFault[i - 1];

		if(LSD_channelDiag_NormalCnt[i - 1] >= DEBOUNCING_CNT && LSD_tempStatVal == 0x03)
		{
			LSD_channelFault[i - 1] = CHANNEL_NORMAL;
			LSD_channelDiag_NormalCnt[i - 1] = 0;

		}
		else if(LSD_channelDiag_abNormalCnt[i - 1] >= DEBOUNCING_CNT)
		{
			LSD_channelFault[i - 1] = CHANNEL_FAULT;
			LSD_channelDiag_abNormalCnt[i - 1] = 0;
		}
		else{}
#endif
	}
}

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
	uint16_t response;
	uint32_t startTick = HAL_GetTick();

	LSD_Select();

	while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY)
	{
		if ((HAL_GetTick() - startTick) > SPI2_TIMEOUT_MS)
		{
			LSD_deSelect();
			return 0xFFFF;
		}
	}

	HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&cmd, (uint8_t*)&response, 1, SPI2_TIMEOUT_MS);
	LSD_deSelect();

	return response;
}


uint16_t LSD_Communication(uint8_t wr, uint8_t addr3, uint8_t sub4, uint8_t data8)
{
    uint16_t frame = 0;
    frame |= ((uint16_t)(wr   & 0x1u) << LSD_SI_WR_SHIFT);
    frame |= ((uint16_t)(addr3 & 0x7u) << LSD_SI_ADDR_SHIFT);
    frame |= ((uint16_t)(sub4  & 0xFu) << LSD_SI_SUB_SHIFT);
    frame |= ((uint16_t)(data8 & 0xFFu) << LSD_SI_DATA_SHIFT);
    return LSD_TransmitReceive(frame);
}

static inline void lsd_read12(uint8_t addr3, uint16_t* out12)
{
    (void)LSD_Communication(LSD_WR_READ, addr3, 0x0u, 0x00u);
    uint16_t rx = LSD_Communication(LSD_WR_READ, addr3, 0x0u, 0x00u);
    if (out12) *out12 = (rx & 0x0FFFu);
}

static inline void lsd_write12(uint8_t addr3, uint16_t val12)
{
    uint8_t sub4  = (uint8_t)((val12 >> 8) & 0x0Fu);
    uint8_t data8 = (uint8_t)( val12       & 0xFFu);
    (void)LSD_Communication(LSD_WR_WRITE, addr3, sub4, data8);
}

/* DEVS */
void LSD_Read_DEVS(LSD_DEVS_t* out)
{
    (void)LSD_Communication(LSD_WR_READ, LSD_ADDR_DEVS, 0x0u, 0x00u);
    uint16_t rx = LSD_Communication(LSD_WR_READ, LSD_ADDR_DEVS, 0x0u, 0x00u);
    if (out)
    {
        out->word = (rx & 0x0FFFu);
    }
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
    uint16_t v = 0; lsd_read12(LSD_ADDR_OUT, &v);
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
    uint16_t v = 0; lsd_read12(LSD_ADDR_ISA, &v);
    if (out) out->word = (v & 0x0FFFu);
}

void LSD_Write_ISA(LSD_ISA_t in)
{
    lsd_write12(LSD_ADDR_ISA, (in.word & 0x0FFFu));
}

/* ISBx */
void LSD_Read_ISB(LSD_ISB_t* out)
{
    uint16_t v = 0; lsd_read12(LSD_ADDR_ISB, &v);
    if (out) out->word = (v & 0x0FFFu);
}

void LSD_Write_ISB(LSD_ISB_t in)
{
    lsd_write12(LSD_ADDR_ISB, (in.word & 0x0FFFu));
}

/* PMx */
void LSD_Read_PM(LSD_PM_t* out)
{
    uint16_t v = 0; lsd_read12(LSD_ADDR_PM, &v);
    if (out) out->word = (v & 0x0FFFu);
}

void LSD_Write_PM(LSD_PM_t in)
{
    lsd_write12(LSD_ADDR_PM, (in.word & 0x0FFFu));
}


void LSD_Test()
{
    static uint16_t test_read_history[5] = {0}; // 최근 5번 읽기 기록
    static uint8_t history_idx = 0;
    static uint8_t same_count = 0;
    static uint8_t diff_count = 0;
    
    switch (vLSD_Testnum)
    {
	case 0 :
		//no action
		break;
    case 1:
    	LSD_Read_DEVS(&vLSD_DEVS_R);
    	// 일관성 체크
    	if (history_idx > 0 && test_read_history[history_idx-1] == vLSD_DEVS_R.word) {
    		same_count++;
    	} else if (history_idx > 0) {
    		diff_count++;
    	}
    	test_read_history[history_idx] = vLSD_DEVS_R.word;
    	history_idx = (history_idx + 1) % 5;
    	// vLSD_Testnum = 0; // 자동 리셋 제거 - T32에서 수동 제어
    	break;
    case 2:
    	LSD_Write_DEVS(vLSD_DEVS_W);
    	// vLSD_Testnum = 0;
    	break;
    case 3:
    	LSD_Read_OUT(&vLSD_OUT_R);
    	if (history_idx > 0 && test_read_history[history_idx-1] == vLSD_OUT_R.word) {
    		same_count++;
    	} else if (history_idx > 0) {
    		diff_count++;
    	}
    	test_read_history[history_idx] = vLSD_OUT_R.word;
    	history_idx = (history_idx + 1) % 5;
    	// vLSD_Testnum = 0;
    	break;
    case 4:
    	LSD_Write_OUT(vLSD_OUT_W);
    	// vLSD_Testnum = 0;
    	break;
    case 5:
    	LSD_Read_ISA(&vLSD_ISA_R);
    	if (history_idx > 0 && test_read_history[history_idx-1] == vLSD_ISA_R.word) {
    		same_count++;
    	} else if (history_idx > 0) {
    		diff_count++;
    	}
    	test_read_history[history_idx] = vLSD_ISA_R.word;
    	history_idx = (history_idx + 1) % 5;
    	// vLSD_Testnum = 0;
    	break;
    case 6:
    	LSD_Write_ISA(vLSD_ISA_W);
    	// vLSD_Testnum = 0;
    	break;
    case 7:
    	LSD_Read_ISB(&vLSD_ISB_R);
    	if (history_idx > 0 && test_read_history[history_idx-1] == vLSD_ISB_R.word) {
    		same_count++;
    	} else if (history_idx > 0) {
    		diff_count++;
    	}
    	test_read_history[history_idx] = vLSD_ISB_R.word;
    	history_idx = (history_idx + 1) % 5;
    	// vLSD_Testnum = 0;
    	break;
    case 8:
    	LSD_Write_ISB(vLSD_ISB_W);
    	// vLSD_Testnum = 0;
    	break;
    case 9:
    	LSD_Read_PM(&vLSD_PM_R);
    	if (history_idx > 0 && test_read_history[history_idx-1] == vLSD_PM_R.word) {
    		same_count++;
    	} else if (history_idx > 0) {
    		diff_count++;
    	}
    	test_read_history[history_idx] = vLSD_PM_R.word;
    	history_idx = (history_idx + 1) % 5;
    	// vLSD_Testnum = 0;
    	break;
    case 10:
    	LSD_Write_PM(vLSD_PM_W);
    	// vLSD_Testnum = 0;
    	break;
    case 99:
    	// 히스토리 및 카운터 초기화
    	for(int i = 0; i < 5; i++) test_read_history[i] = 0;
    	history_idx = 0;
    	same_count = 0;
    	diff_count = 0;
    	vLSD_Testnum = 0;
    	break;
    default:
    	break;
    }
}





void LSD_init(void)
{
	// Lower side Driver
	CtrlPin_TLE8110ED_EN_On(); //Lower side Driver enable
	CtrlPin_TLE8110ED_RST_Off(); //Reset :  Active --> wait 10ms --> Inactive

	// cubeMX configuration에서 직접 설정이 불가능함 -> userCode begin 항목이 없음
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); // slave deselect
}

void LSD_100ms(void)
{
	// 테스트 모드일 때는 진단 비활성화
	if (vLSD_Testnum == 0)
	{
		// 정상 진단 모드
		uint16_t dummy_Cmd = 0;

		LSD_TransmitReceive(DCC_DRACL_CMD);
		LSD_TransmitReceive(DCC_DRBCL_CMD);
		//HAL_Delay(1);
		dummy_Cmd = LSD_TransmitReceive(cmd_DRA);
		LSD_DRA_Val = LSD_TransmitReceive(cmd_DRB);
		LSD_DRB_Val	= LSD_TransmitReceive(dummy_Cmd);

		LSD_ParseDiagVal();
	}
	
	// 테스트 함수는 항상 실행
	LSD_Test();
}

uint8_t LSD_getChannel_diagVal(uint8_t channelNum)
{
	return LSD_channelFault[channelNum];
}

void LSD_Control_Init(void)
{
	;
}

void LSD_Set_Data(void)
{
	Set_ActLeftSolenoid(tmp_StSolnLD);
	Set_ActRightSolenoid(tmp_StSolnRD);
}

void LSD_Get_Data(void)
{
	tmp_StSolnLD				= Get_TgtLeftSolenoid();
	tmp_StSolnRD				= Get_TgtRightSolenoid();
}

void LSD_Proc_10ms(void)
{
	LSD_Get_Data();
	LSD_Set_Data();
}
