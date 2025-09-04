/*
 * LSD_Driver.h
 *
 *  Created on: Mar 2, 2025
 *      Author: sungsoo
 */

#ifndef LSD_DRIVER_H_
#define LSD_DRIVER_H_

#include "stm32f4xx_hal.h"

/*----for spi2 option----*/
#define SPI2_TIMEOUT_MS (1)

/*----TLE8110EE LSD standard----*/
#define READ_CMD 	(1 << 15)
#define WRITE_CMD 	(0 << 15)	// 1 : read, 0 : write
#define DCC_CMD 	(1 << 12)	// 0x0001
#define DRA_CMD		(0x500)
#define DRB_CMD 	(0x600)
#define DRACL_CMD 	(0x100)
#define DRBCL_CMD 	(0x200)

#define DCC_DRA_CMD (WRITE_CMD | DCC_CMD | DRA_CMD)
#define DCC_DRB_CMD (WRITE_CMD | DCC_CMD | DRB_CMD)
#define DCC_DRACL_CMD (WRITE_CMD | DCC_CMD | DRACL_CMD)
#define DCC_DRBCL_CMD (WRITE_CMD | DCC_CMD | DRBCL_CMD)

#define GET_DRAn_STAT(pos,statVal) (((statVal) >> ((pos - 1) * 2)) & 0x03)
#define GET_DRBn_STAT(pos,statVal) (((statVal) >> ((pos - 7) * 2)) & 0x03)

#define CHANNEL_MAX 	(10)
#define USE_CHANNEL_NUM (7)

#define DEBOUNCING_CNT 	(5)
#define CHANNEL_FAULT	(1) // open load & short 2 gnd & over current
#define CHANNEL_NORMAL	(0)

enum LSD_channelConfig
{
	MAINRLY = 0,
	MIXER,
	HEADLAMP,
	RESERVE1,
	RESERVE2,
	RESERVE3,
	RESERVE4,
};

extern uint8_t LSD_channelFault[CHANNEL_MAX];
extern uint16_t LSD_DRA_Val;
extern uint16_t LSD_DRB_Val;

extern void LSD_100ms(void);
extern void LSD_init(void);
extern uint8_t LSD_getChannel_diagVal(uint8_t channelNum);

////////////////////////////////////////////////// EXT_FUNCTION /////////////////////////////////////////////////////
extern void LSD_Control_Init(void);
extern void LSD_Proc_10ms(void);
extern void SS500_Solenoid_Control(void);

#endif /* LSD_DRIVER_H_ */
