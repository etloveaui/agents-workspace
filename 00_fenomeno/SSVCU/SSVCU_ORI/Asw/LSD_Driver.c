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
	uint16_t dummy_Cmd = 0;

	LSD_TransmitReceive(DCC_DRACL_CMD);
	LSD_TransmitReceive(DCC_DRBCL_CMD);
	//HAL_Delay(1);
	dummy_Cmd = LSD_TransmitReceive(cmd_DRA);
	LSD_DRA_Val = LSD_TransmitReceive(cmd_DRB);
	LSD_DRB_Val	= LSD_TransmitReceive(dummy_Cmd);

	LSD_ParseDiagVal();
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
