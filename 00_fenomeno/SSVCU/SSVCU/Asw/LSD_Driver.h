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

/*
 * frame = (wr<<15) | (addr3<<12) | (sub4<<8) | (data8)
 * - wr:   LSD_WR_WRITE(0) or LSD_WR_READ(1)
 * - addr3: LSD_ADDR_* (3-bit)
 * - sub4:
 * - data8:
 */
extern uint16_t LSD_Communication(uint8_t wr, uint8_t addr3, uint8_t sub4, uint8_t data8);

#define LSD_SI_WR_SHIFT   15u
#define LSD_SI_ADDR_SHIFT 12u  /* 3-bit ADDR */
#define LSD_SI_SUB_SHIFT   8u  /* 4-bit SUB/CMD */
#define LSD_SI_DATA_SHIFT  0u  /* 8-bit DATA */

#define LSD_SI_WR_MASK    (1u   << LSD_SI_WR_SHIFT)   /* 0x8000 */
#define LSD_SI_ADDR_MASK  (0x7u << LSD_SI_ADDR_SHIFT) /* 0x7000 */
#define LSD_SI_SUB_MASK   (0xFu << LSD_SI_SUB_SHIFT)  /* 0x0F00 */
#define LSD_SI_DATA_MASK  (0xFFu<< LSD_SI_DATA_SHIFT) /* 0x00FF */

/* ADDR(3-bit) 값: 표(Table 1) 기준 */
#define LSD_ADDR_CMD   0u /* 000b */
#define LSD_ADDR_DCC   1u /* 001b */
#define LSD_ADDR_OUT   2u /* 010b */
#define LSD_ADDR_DEVS  3u /* 011b */
#define LSD_ADDR_MSCS  4u /* 100b */
#define LSD_ADDR_ISA   5u /* 101b */
#define LSD_ADDR_ISB   6u /* 110b */
#define LSD_ADDR_PM    7u /* 111b */

/* DCC 하위 SUB/CMD(4-bit) */
#define LSD_SUB_DRACL  0x1u
#define LSD_SUB_DRBCL  0x2u
#define LSD_SUB_DRA    0x5u
#define LSD_SUB_DRB    0x6u

/* W/R 값 */
#define LSD_WR_WRITE   0u
#define LSD_WR_READ    1u

/* DEVS */
typedef union {
    uint16_t word;
    struct {
        uint16_t DCC18 : 1;  /* bit0  */
        uint16_t DCC9  : 1;  /* bit1  */
        uint16_t DCC10 : 1;  /* bit2  */
        uint16_t rsvd3_8 : 6;/* bit3..8 */
        uint16_t DBT1  : 1;  /* bit9  */
        uint16_t DBT2  : 1;  /* bit10 */
        uint16_t RCP   : 1;  /* bit11 */
        uint16_t rsvd12_15 : 4;
    } signal;
} LSD_DEVS_t;
/* DEVS 비트 설명
 - bit11 RCP: Reverse Current Compensation, 1=활성, 0=비활성
 - bit10:9 DBT2:DBT1: 입력 디바운스 시간 선택(00=최단 ~ 11=최장) [정확 시간은 데이터시트 표 참조]
 - bit8..3: Reserved(0 유지)
 - bit2 DCC10: 채널10용 DCC 옵션 활성(1)/비활성(0)
 - bit1 DCC9:  채널9 용 DCC 옵션 활성(1)/비활성(0)
 - bit0 DCC18: 채널1~8 DCC 옵션 활성(1)/비활성(0)
 기본값 0x007: DCC18/DCC9/DCC10=1, 나머지 0
*/

/* OUT */
typedef union {
    uint16_t word;
    struct {
        uint16_t OUT1  : 1; /* bit0  */
        uint16_t OUT2  : 1; /* bit1  */
        uint16_t OUT3  : 1; /* bit2  */
        uint16_t OUT4  : 1; /* bit3  */
        uint16_t OUT5  : 1; /* bit4  */
        uint16_t OUT6  : 1; /* bit5  */
        uint16_t OUT7  : 1; /* bit6  */
        uint16_t OUT8  : 1; /* bit7  */
        uint16_t OUT9  : 1; /* bit8  */
        uint16_t OUT10 : 1; /* bit9  */
        uint16_t C0    : 1; /* bit10:*/
        uint16_t C1    : 1; /* bit11:*/
        uint16_t rsvd12_15 : 4;
    } signal;
} LSD_OUT_t;
/* OUT 비트 설명
 - bit11..10: 상수 1(0으로 쓰지 않도록 주의), 기본값 0xC00에 해당
 - bit9..0: OUT10..OUT1 채널 제어(일반적으로 1=ON, 0=OFF)
*/


typedef union {
    uint16_t word;
    struct {
        uint16_t IS1:1;
        uint16_t IS2:1;
        uint16_t IS3:1;
        uint16_t IS4:1;
        uint16_t IS5:1;
        uint16_t IS6:1;
        uint16_t rsvd6_11:6;
        uint16_t rsvd12_15:4;
    } signal;
} LSD_ISA_t;
/* ISAx 설명: IS1..IS6 채널(1~6) 모드 비트. 리셋 기본값 0xAAA. */

typedef union {
    uint16_t word;
    struct {
        uint16_t IS7:1;
        uint16_t IS8:1;
        uint16_t IS9:1;
        uint16_t IS10:1;
        uint16_t rsvd4_11:8;
        uint16_t rsvd12_15:4;
    } signal;
} LSD_ISB_t;
/* ISBx 설명: IS7..IS10 채널(7~10) 모드 비트. 리셋 기본값 0x0AA. */

typedef union {
    uint16_t word;
    struct {
        uint16_t PM12:1;
        uint16_t PM23:1;
        uint16_t PM34:1;
        uint16_t rsvd3:1;
        uint16_t PM56:1;
        uint16_t rsvd5:1;
        uint16_t PM78:1;
        uint16_t PM89:1;
        uint16_t PM910:1;
        uint16_t rsvd9_11:3;
        uint16_t rsvd12_15:4;
    } signal;
} LSD_PM_t;
/* PMx 설명: PM12/PM23/PM34/PM56/PM78/PM89/PM910 채널 페어링 비트(1=페어링). */

#define LSD_OUT_CONST     (0x0C00u)
#define LSD_OUT_MASK10    (0x03FFu)
#define LSD_OUT_BIT(ch)   (1u << ((ch) - 1))

extern void LSD_Read_DEVS(LSD_DEVS_t* out);
extern void LSD_Write_DEVS(LSD_DEVS_t in);

extern void LSD_Read_OUT(LSD_OUT_t* out);
extern void LSD_Write_OUT(LSD_OUT_t in);

extern void LSD_Read_ISA(LSD_ISA_t* out);
extern void LSD_Write_ISA(LSD_ISA_t in);

extern void LSD_Read_ISB(LSD_ISB_t* out);
extern void LSD_Write_ISB(LSD_ISB_t in);

extern void LSD_Read_PM(LSD_PM_t* out);
extern void LSD_Write_PM(LSD_PM_t in);

extern LSD_DEVS_t vLSD_DEVS_R;
extern LSD_DEVS_t vLSD_DEVS_W;
extern LSD_OUT_t vLSD_OUT_W;
extern LSD_OUT_t vLSD_OUT_R;
extern LSD_ISA_t  vLSD_ISA_R;
extern LSD_ISA_t  vLSD_ISA_W;
extern LSD_ISB_t  vLSD_ISB_R;
extern LSD_ISB_t  vLSD_ISB_W;
extern LSD_PM_t   vLSD_PM_R;
extern LSD_PM_t   vLSD_PM_W;
extern void LSD_Test();

////////////////////////////////////////////////// EXT_FUNCTION /////////////////////////////////////////////////////
extern void LSD_Control_Init(void);
extern void LSD_Proc_10ms(void);
extern void SS500_Solenoid_Control(void);

#endif /* LSD_DRIVER_H_ */
