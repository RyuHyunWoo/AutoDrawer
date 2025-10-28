/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	FSP_JIG
  * @file    	MAIN.H
  * @author  	Firmware Team(Nexus)
  ******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __MAIN_H_
#define __MAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "integer.h"
//#include "ffconf.h"
//#include "ff.h"
//#include "diskio.h"
//#include "sdio_debug.h"
//#include "stm32f4_discovery.h"
//#include "stm32f4_discovery_sdio_sd.h"

#include "misc.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_exti.h"

/* Private typedef -----------------------------------------------------------*/
typedef bool   			BOOL;
typedef unsigned char	BYTE;
typedef unsigned int	WORD;
typedef unsigned long	DWORD;

typedef unsigned char	UCHAR;
typedef unsigned int	UINT;
typedef unsigned short  USHORT;
typedef unsigned long	ULONG;

typedef char			CHAR;
typedef int				INT;
typedef long			LONG;
typedef short			SHORT;

typedef union{
   struct{
      BYTE low;
      BYTE high;
   }B;
   WORD W;
}device_address;

typedef void (*pFunc)(void);

typedef enum{
	NVIC_PREEMPTION_PRIORITY_0 = 0,
	NVIC_PREEMPTION_PRIORITY_1,
	NVIC_PREEMPTION_PRIORITY_2,
	NVIC_PREEMPTION_PRIORITY_3,
}NVIC_PREEMPTION_PRIORITY;

typedef enum{
	NVIC_SUB_PRIORITY_0 = 0,
	NVIC_SUB_PRIORITY_1,
	NVIC_SUB_PRIORITY_2,
	NVIC_SUB_PRIORITY_3,
	NVIC_SUB_PRIORITY_4,
	NVIC_SUB_PRIORITY_5,
	NVIC_SUB_PRIORITY_6,
	NVIC_SUB_PRIORITY_7,
	NVIC_SUB_PRIORITY_8,
	NVIC_SUB_PRIORITY_9,
	NVIC_SUB_PRIORITY_10,
	NVIC_SUB_PRIORITY_11,
	NVIC_SUB_PRIORITY_12,
	NVIC_SUB_PRIORITY_13,
	NVIC_SUB_PRIORITY_14,
	NVIC_SUB_PRIORITY_15,
}NVIC_SUB_PRIORITY;

//#define DEBUG
//#define DEBUG_TOKEN
//#define DEBUG_PWM_RATIO
//#define DEBUG_ENCODER
//#define DEBUG_OPERATION
//define DEBUG_EEPROM_DISP
//#define DEBUG_BUTTON
//#define DEBUG_TOUCH
//#define DEBUG_SENSOR_DISP
//#define DEBUG_EEPROM_DISP
//#define DEBUG_UART
//#define _USE_DEBUG
//#define _USE_DEBUG_EEP

#define FALSE		0
#define TRUE		!FALSE
#define _FALSE		0
#define _TRUE		1
#define ON			1
#define OFF			0

#define DEFAULT_DRAWER_ADDR            0x4F10
/* Includes ------------------------------------------------------------------*/
#include "GUI.h"
#include "DIALOG.h"
#include "GUIDEMO.h"

#include "GUIConf.h"
#include "GUIDEMO.h"
#include "uart.h"
#include "timer.h"
#include "fmc_sdram.h"
#include "touch.h"
#include "gpio.h"
#include "motor.h"
#include "LCD_Draw.h"
#include "lcd_image.h"
#include <math.h>
/* Private define ------------------------------------------------------------*/
#define CHECKVERSION "VER ELECDRAWER-422-0.0.01-001-21.12.21END"
#define DISPLAY_VERSION "Ver.211221"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern BYTE	g_bFWUpdata;
extern BYTE	ChekVer[];
extern uint8_t GUI_Initialized;

extern void (*STEP10MSFunction[])(void);
extern void (*STEP1MSFunction[])(void);
extern void TimeService10ms(void);
extern void TimeService1ms(void);
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */



