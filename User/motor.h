 /**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file		MOTOR.H
  * @author  	Firmware Team(LMI)
  * @attention
  *
  ******************************************************************************
  */

  /* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef __MOTOR_H
#define __MOTOR_H

#ifdef __cplusplus
 extern "C" {
#endif
   /* Includes ------------------------------------------------------------------*/
#include "main.h"
  /* Private typedef -------------------------------------------------------------*/
#define STOP_POINT						12
#define LIMIT_SENSOR_COUNT				3
#define MAX_ENCODER						0xffff
//#define MINIMUM_INTERVAL				10
#define INTERVAL						5
#define MINIMUM_ENC_RANGE				300
#define ACC_DEC_RATIO					30

//#define ENCODER_TIMEOUT					3000
#define ENCODER_TIMEOUT					5000
#define MOTOR_TIMEOUT					15000
#define DEFAULT_TABLE_SIZE				500

#define ERR_CST_CNT						10

#define INTERMEDIATE_STOP_VOLUME		200
#define SENSOR_CHECK_TIME				10
#define CHATTERING_COUNT				3


typedef enum{
	SEN_UNPOS = 0,
	SEN_OPENPOS,
	SEN_CLOSEPOS,
}SenPos_Typedef;

typedef enum{
	DRAW_MAGNETIC_PARAM_01 = 0,
	DRAW_MAGNETIC_PARAM_02,
	DRAW_MAGNETIC_PARAM_03,
}MAGNETIC_PARAM;

typedef enum{
	ENC_RH,
	ENC_RL,
	ENC_FH,
	ENC_FL,
}ENC_STATUS;

typedef enum{
	DRAW_TACHO_HOLD,
	DRAW_TACHO_CW,
	DRAW_TACHO_CCW,
}DRAW_TACHO_STATUS;

typedef enum{
	DRAW_PARAM_CLOSE = 0,
	DRAW_PARAM_01,
	DRAW_PARAM_02,
	DRAW_PARAM_03,
	DRAW_PARAM_04,
	DRAW_PARAM_05,
	DRAW_PARAM_06,
	DRAW_PARAM_07,
	DRAW_PARAM_08,
	DRAW_PARAM_09,
	DRAW_PARAM_10,
	DRAW_PARAM_11,
	DRAW_PARAM_12,
	DRAW_PARAM_13,
	DRAW_PARAM_14,
	DRAW_PARAM_15,
	DRAW_PARAM_16,
	DRAW_PARAM_17,
	DRAW_PARAM_18,
	DRAW_PARAM_19,
	DRAW_PARAM_20,
	DRAW_PARAM_OPEN,
	DRAW_PARAM_UNKNOWN = 99,
}DRAW_LOCATION_PARAM;

typedef enum{
	_EEPROM_DRAW_PARAM_CLOSE_INFO = 0,
	_EEPROM_DRAW_PARAM_01_INFO = 2,
	_EEPROM_DRAW_PARAM_02_INFO = 4,
	_EEPROM_DRAW_PARAM_03_INFO = 6,
	_EEPROM_DRAW_PARAM_04_INFO = 8,
	_EEPROM_DRAW_PARAM_05_INFO = 10,
	_EEPROM_DRAW_PARAM_06_INFO = 12,
	_EEPROM_DRAW_PARAM_07_INFO = 14,
	_EEPROM_DRAW_PARAM_08_INFO = 16,
	_EEPROM_DRAW_PARAM_09_INFO = 18,
	_EEPROM_DRAW_PARAM_10_INFO = 20,
	_EEPROM_DRAW_PARAM_11_INFO = 22,
	_EEPROM_DRAW_PARAM_12_INFO = 24,
	_EEPROM_DRAW_PARAM_13_INFO = 26,
	_EEPROM_DRAW_PARAM_14_INFO = 28,
	_EEPROM_DRAW_PARAM_15_INFO = 30,
	_EEPROM_DRAW_PARAM_16_INFO = 32,
	_EEPROM_DRAW_PARAM_17_INFO = 34,
	_EEPROM_DRAW_PARAM_18_INFO = 36,
	_EEPROM_DRAW_PARAM_19_INFO = 38,
	_EEPROM_DRAW_PARAM_20_INFO = 40,
	_EEPROM_DRAW_PARAM_OPEN_INFO = 42,
	//_EEPROM_DRAW_PARAM_LAST_INFO = 44,
}EEPROM_TABLE;

typedef struct{
	volatile WORD cst_interval;
	volatile WORD draw_tacho_cw;
	volatile WORD draw_tacho_ccw;
	volatile WORD draw_my_encoder;
	volatile WORD draw_last_encoder;
	volatile WORD draw_dec_point;
	volatile BYTE draw_final_param;

	volatile WORD draw_dec_encoder;
	volatile WORD open_dec_encoder;
	WORD draw_enc_point[DRAW_PARAM_OPEN+1];

	WORD overall_range;
	WORD minimum_range;
	float unit;
	float float_acc_dec;
	WORD acc_dec_section;
	WORD stable_section;
	WORD elapsed_time;
	WORD limit_time;
	BOOL keep_limit;
}GET_ENC_POINT;

typedef struct{
	unsigned close:1;
	unsigned open_limit:1;
	unsigned close_limit:1;
	unsigned init_cmpl:1;
	unsigned active_lock:1;
	unsigned manual_lock:1;
	unsigned active:1;
	unsigned manual:1;

	unsigned timeout:1;
	unsigned encoder_error:1;
	unsigned abnormal_motion:1;
	unsigned dummy_11:1;
	unsigned dummy_12:1;
	unsigned dummy_13:1;
	unsigned dummy_14:1;
	unsigned dummy_15:1;

	unsigned not_closed:1;
	unsigned dummy_17:1;
	unsigned dummy_18:1;
	unsigned dummy_19:1;
	unsigned dummy_20:1;
	unsigned dummy_21:1;
	unsigned dummy_22:1;
	unsigned dummy_23:1;

	unsigned PINRST:1;
	unsigned PORRST:1;
	unsigned IWDGRST:1;
	unsigned LPWRRST:1;
	unsigned dummy_28:1;
	unsigned dummy_29:1;
	unsigned dummy_30:1;
	unsigned reseted:1;
}status_bit;

typedef union{
	status_bit bit;
	BYTE byte[4];
	WORD word;
}union_status_bit;

typedef struct{
	union_status_bit status_list;
	//display_draw_union display_draw_list;
	BYTE display_screen;
	BYTE current_point;
	BYTE error_point;

	WORD err_cst_address[ERR_CST_CNT];
	BYTE err_cst_count;
	BYTE senpos;
	BYTE lastPos;
	//volatile BOOL open_limit_point[LIMIT_SENSOR_COUNT];
	//volatile BOOL close_limit_point[LIMIT_SENSOR_COUNT];
	//volatile BYTE open_count;
	//volatile BYTE close_count;

	volatile WORD cst_point[STOP_POINT];
	volatile WORD encoder_time;
	volatile WORD timeout_time;
}status_module;

typedef struct{
	unsigned remote_order:1;
	unsigned stop_order:1;
	unsigned manual_order:1;
	unsigned init_order:1;
	unsigned fault_reserve:1;
	unsigned fault_handling:1;
	unsigned watchdog:1;
	unsigned intermediate_stop:1;

	unsigned auth_access_token:1;			//외부 제어권 허가
	unsigned enable_access_token:1;			//외부 제어권 활성화
	unsigned set_access_token:1;			//외부 제어권 설정
	unsigned refill_set_no:1;
	unsigned refill_set_yes:1;
	unsigned display:1;
	unsigned display_token:1;
	unsigned dummy_07:1;
}draw_order_bit;

typedef union{
	draw_order_bit bit;
	BYTE byte[2];
	USHORT word;
}draw_order_union;

typedef struct{
	draw_order_union order_list;
	BYTE last_location;
	BYTE my_location;
	BYTE order_location;
	BYTE fault_location;
	BYTE direction;
	BYTE last_direction;
	WORD last_time;
	WORD button_time;
	volatile WORD key_time;
	BOOL move_order;
	BOOL loop_order;
	BYTE loop_step;
	BOOL loop_err;
	WORD loop_cnt;
	BOOL token_enable;
	volatile BYTE on_token;
	volatile BYTE off_token;
}draw_order_module;

typedef enum{
	DRAW_DIR_NONE,
	DRAW_DIR_OPEN,
	DRAW_DIR_CLOSE,
}DRAW_DIR_LIST;

typedef struct{
	unsigned operation:1;
	unsigned manual_operation:1;
	unsigned phase:1;
	unsigned acceleration:1;
	unsigned deceleration:1;
	unsigned slow_section:1;
	unsigned dummy_05:1;
	unsigned dummy_06:1;
}pwm_list_bit;

typedef union{
	pwm_list_bit bit;
	BYTE byte;
}pwm_list_union;

typedef struct{
	pwm_list_union pwm_list;
	BYTE section;

	WORD table_size;
	volatile WORD reload;
	BYTE step;
	BYTE last_step;
}pwm_typedef;

typedef enum{
	NONE_SECTION = 0,
	ACC_SECTION,
	STABLE_SECTION,
	DEC_SECTION,
}pwm_acc_typedef;

typedef struct{
	unsigned screen_default:1;
	unsigned screen_dispense:1;
	unsigned screen_refill:1;
	unsigned screen_moving:1;
	unsigned screen_lock:1;
	unsigned screen_init:1;
	unsigned dummy_01:1;
	unsigned dummy_02:1;
}display_draw_typedef;

typedef union{
	display_draw_typedef bit;
	BYTE byte;
}display_draw_union;

typedef enum{
	DISP_DRAW_DEFAULT = 0,
	DISP_DRAW_DISPENSE,
	DISP_DRAW_REFILL,
	DISP_DRAW_LOCK,
}display_draw_screen;

  /* Define to prevent recursive inclusion -------------------------------------*/
#define MOTORn                           	2

#define MOTOR_DIR_GPIO_PIN                 	GPIO_Pin_6
#define MOTOR_DIR_GPIO_PORT                 GPIOF
#define MOTOR_DIR_GPIO_CLK                  RCC_AHB1Periph_GPIOF

#define MOTOR_RUN_GPIO_PIN 					GPIO_Pin_8
#define MOTOR_RUN_GPIO_PORT					GPIOF
#define MOTOR_RUN_GPIO_CLK					RCC_AHB1Periph_GPIOF

#define GPIOA_SPI1_EEP_NSS					GPIO_Pin_4
#define GPIOA_SPI1_EEP_SCK					GPIO_Pin_5
#define GPIOA_SPI1_EEP_MISO					GPIO_Pin_6
#define GPIOA_SPI1_EEP_MOSI					GPIO_Pin_7

#define GPIOC_SPI1_EEP_WE					GPIO_Pin_4
#define GPIOC_SPI1_EEP_RESET				GPIO_Pin_5

#define GPIOA_SPI1_PORT						GPIOA
#define GPIOC_SPI1_PORT						GPIOC
#define GPIOA_SPI1_CLK						RCC_AHB1Periph_GPIOA
#define GPIOC_SPI1_CLK						RCC_AHB1Periph_GPIOC

#define _EEPROM_WREN				0x06
#define _EEPROM_WRDI				0x04
#define _EEPROM_RDSR				0x05
#define _EEPROM_WRSR				0x01
#define _EEPROM_READ				0x03
#define _EEPROM_WRITE				0x02
#define _EEPROM_RDID				0x83
#define _EEPROM_WRID				0x82
#define _EEPROM_RDLS				0x83
#define _EEPROM_LID					0x82

#define _EEPROM_WIP_FLAG        	0x01  /*!< Write In Progress (WIP) flag */
#define _EEPROM_PAGESIZE        	32

#define _EEPROM_READ_ALLDATA		15
#define _EEPROM_READ_SYNCPOINT		10
#define _EEPROM_READ_ENCPOINT		22

#define _EEPROM_READ_WORD			2
#define _DUMMY_DATA					0x00
#define _EEPROM_SYNCDATA_LIST		6
#define _NONE						0xFF

#define MANUAL_ORDER_END				0x30
#define MANUAL_ORDER					0x0c

#define CLOSE_ENCODER					0
#define OPEN_ENCODER					65535

#define AC_MOTOR_CCW()						(GPIOF->BSRRL = GPIO_Pin_6)
#define AC_MOTOR_CW()						(GPIOF->BSRRH = GPIO_Pin_6)
#define AC_MOTOR_RUN()						(GPIOF->BSRRL = GPIO_Pin_8)
#define AC_MOTOR_BRAKE()					(GPIOF->BSRRH = GPIO_Pin_8)
#define AC_MOTOR_READ()						(GPIOF->IDR & GPIO_Pin_8)

#define READ_DRAW_PHASE_A()					((GPIOB->IDR & GPIO_Pin_7) != RESET)
#define READ_DRAW_PHASE_B() 				((GPIOB->IDR & GPIO_Pin_6) != RESET)

#define SPI1_CS_ENABLE()					(GPIOA->BSRRH = GPIO_Pin_4)
#define SPI1_CS_DISABLE()					(GPIOA->BSRRL = GPIO_Pin_4)

#define SPI1_WE_ENABLE()					(GPIOC->BSRRH = GPIO_Pin_4)
#define SPI1_WE_DISABLE()					(GPIOC->BSRRL = GPIO_Pin_4)

//#define SPI1_RST_ENABLE()					GPIO_SetBits(GPIOC_SPI1_PORT, GPIOC_SPI1_EEP_RESET)
//#define SPI1_RST_DISABLE()					GPIO_ResetBits(GPIOC_SPI1_PORT, GPIOC_SPI1_EEP_RESET)

#define NOP_1  			__NOP()
#define NOP_2  			NOP_1; NOP_1
#define NOP_3			NOP_1; NOP_1; NOP_1
#define NOP_4  			NOP_2; NOP_2
#define NOP_5  			NOP_4; NOP_1
#define NOP_6  			NOP_2; NOP_2; NOP_2
#define NOP_8  			NOP_2; NOP_2; NOP_2; NOP_2
#define NOP_10   		NOP_4; NOP_4; NOP_2
#define NOP_12   		NOP_4; NOP_4; NOP_4
#define NOP_16			NOP_4; NOP_4; NOP_4; NOP_4
#define NOP_20  		NOP_10; NOP_10
#define NOP_30  		NOP_10; NOP_10; NOP_10
#define NOP_35			NOP_10; NOP_10; NOP_10; NOP_5
#define NOP_40  		NOP_20; NOP_20
#define NOP_80  		NOP_40; NOP_40
#define NOP_160  		NOP_80; NOP_80
#define NOP_320  		NOP_160; NOP_160

 /* Exported types ------------------------------------------------------------*/
 typedef enum
{
	MOTOR_DIR = 0,
	MOTOR_RUN = 1,
}MOTOR_TypeDef;

#define SENSORn                            7

#define SENSOR1_GPIO_PIN					GPIO_Pin_2
#define SENSOR1_GPIO_PORT					GPIOG
#define SENSOR1_GPIO_CLK					RCC_AHB1Periph_GPIOG
#define SENSOR1_EXTI_PORT					EXTI_PortSourceGPIOG
#define SENSOR1_EXTI_LINE					EXTI_Line2
#define SENSOR1_EXTI_SOURCE					GPIO_PinSource2

#define SENSOR2_GPIO_PIN					GPIO_Pin_3
#define SENSOR2_GPIO_PORT					GPIOG
#define SENSOR2_GPIO_CLK					RCC_AHB1Periph_GPIOG
#define SENSOR2_EXTI_PORT					EXTI_PortSourceGPIOG
#define SENSOR2_EXTI_LINE					EXTI_Line3
#define SENSOR2_EXTI_SOURCE					GPIO_PinSource3

#define SENSOR3_GPIO_PIN					GPIO_Pin_7
#define SENSOR3_GPIO_PORT					GPIOB
#define SENSOR3_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define SENSOR3_EXTI_PORT					EXTI_PortSourceGPIOB
#define SENSOR3_EXTI_LINE					EXTI_Line7
#define SENSOR3_EXTI_SOURCE					GPIO_PinSource7

#define SENSOR4_GPIO_PIN					GPIO_Pin_6
#define SENSOR4_GPIO_PORT					GPIOB
#define SENSOR4_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define SENSOR4_EXTI_PORT					EXTI_PortSourceGPIOB
#define SENSOR4_EXTI_LINE					EXTI_Line6
#define SENSOR4_EXTI_SOURCE					GPIO_PinSource6

#define SENSOR5_GPIO_PIN					GPIO_Pin_0
#define SENSOR5_GPIO_PORT					GPIOB
#define SENSOR5_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define SENSOR5_EXTI_PORT					EXTI_PortSourceGPIOB
#define SENSOR5_EXTI_LINE					EXTI_Line0
#define SENSOR5_EXTI_SOURCE					GPIO_PinSource0

#define ACCESS_TOKEN1_GPIO_PIN				GPIO_Pin_1
#define ACCESS_TOKEN1_GPIO_PORT				GPIOB
#define ACCESS_TOKEN1_GPIO_CLK				RCC_AHB1Periph_GPIOB
#define ACCESS_TOKEN1_EXTI_PORT				EXTI_PortSourceGPIOB
#define ACCESS_TOKEN1_EXTI_LINE				EXTI_Line1
#define ACCESS_TOKEN1_EXTI_SOURCE			GPIO_PinSource1

#define ACCESS_TOKEN2_GPIO_PIN				GPIO_Pin_2
#define ACCESS_TOKEN2_GPIO_PORT				GPIOB
#define ACCESS_TOKEN2_GPIO_CLK				RCC_AHB1Periph_GPIOB
#define ACCESS_TOKEN2_EXTI_PORT				EXTI_PortSourceGPIOB
#define ACCESS_TOKEN2_EXTI_LINE				EXTI_Line2
#define ACCESS_TOKEN2_EXTI_SOURCE			GPIO_PinSource2

#define BUZZER_GPIO_PIN						GPIO_Pin_1
#define BUZZER_GPIO_PORT					GPIOA
#define BUZZER_GPIO_CLK						RCC_AHB1Periph_GPIOA


typedef enum
{
	SENSOR_OPEN = 0,
	SENSOR_CLOSE = 1,
	SENSOR_PHASE_A = 2,
	SENSOR_PHASE_B = 3,
	SENSOR_ORIGIN = 4,
	ACCESS_TOKEN1 = 5,
	ACCESS_TOKEN2 = 6,
}SENSOR_TypeDef;

#define ADDR_GPIO_PORT					GPIOC
#define ADDR_GPIO_CLK					RCC_AHB1Periph_GPIOC

#define ADDR1_GPIO_PIN               	GPIO_Pin_0
#define ADDR2_GPIO_PIN					GPIO_Pin_1
#define ADDR3_GPIO_PIN               	GPIO_Pin_2
#define ADDR4_GPIO_PIN					GPIO_Pin_3

#define SLOTn							4

#define SLOT1_GPIO_PORT					GPIOC
#define SLOT1_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define SLOT1_GPIO_PIN					GPIO_Pin_13

#define SLOT234_GPIO_PORT				GPIOI
#define SLOT234_GPIO_CLK				RCC_AHB1Periph_GPIOI

#define SLOT2_GPIO_PIN					GPIO_Pin_6
#define SLOT3_GPIO_PIN					GPIO_Pin_7
#define SLOT4_GPIO_PIN					GPIO_Pin_11

//#define PH 					3.1415926535
#define PH 						3.14159
//#define PH 					314.15926535

#define SINE_ARRAY_LENGTH		2048
#define ACC_FREQ_MAX			300
#define ACC_FREQ_SLOW_MIN		700
#define ACC_FREQ_MIN			650
#define ACC_FREQ_SLOW_MAX		500

#define _ACC_FREQ_MAX			250
#define _ACC_FREQ_SLOW_MIN		550
#define _ACC_FREQ_MIN			550
#define _ACC_FREQ_SLOW_MAX		400

#define _FREQ_MOVING_SPD		600

#if 0
#define ACC_FREQ_MIN			700
#define ACC_FREQ_SLOW_MAX		500
#define _ACC_FREQ_MIN			550
#define _ACC_FREQ_SLOW_MIN		600
#endif

typedef enum{
	ACC_MAX = 0,
	ACC_MIN,
	ACC_SLOW_MAX,
	ACC_SLOW_MIN,
	MANUAL_MOVING_SPD,
	ACC_LOOP_TEST,
	IDLE,
}ACC_Typedef;

#define FREQn		5

#define TIMER_PERIOD_MAX		1000
#define TIMER_PERIOD_NORMAL		300
#define TIMER_PERIOD_SLOW		600

#define ACC_DEC_LIMIT			300
#define ABNORMAL_MOTION_ERR		10
#define SLOW_SECTION			35		//ms


extern device_address my_address;
extern status_module draw_status;
extern draw_order_module draw_order;
extern GET_ENC_POINT draw_encoder;
extern pwm_typedef pwm_status;

extern GPIO_TypeDef* MOTOR_SET_GPIO_PORT[MOTORn];
extern const uint16_t MOTOR_SET_GPIO_PIN[MOTORn];
extern const uint32_t MOTOR_SET_GPIO_CLK[MOTORn];

extern GPIO_TypeDef* SENSOR_SET_GPIO_PORT[SENSORn];
extern const uint16_t SENSOR_SET_GPIO_PIN[SENSORn];
extern const uint32_t SENSOR_SET_GPIO_CLK[SENSORn];

extern float sine_acc[SINE_ARRAY_LENGTH];
extern WORD sine_acc_32[SINE_ARRAY_LENGTH];

extern WORD acc_freq_array[FREQn];

#define IS_ACCESS_TOKEN()					((GPIOB->IDR & GPIO_Pin_1) == SET)

#define ACCESS_TOKEN_DISABLE()				(GPIOB->BSRRL = GPIO_Pin_2)//;	\
											//(draw_order.order_list.bit.enable_access_token = false)

#define ACCESS_TOKEN_ENABLE()				(GPIOB->BSRRH = GPIO_Pin_2)//;	\
											//(draw_order.order_list.bit.enable_access_token = true)

#define IS_NOT_AVAIL_ACCESS_TOKEN()			((GPIOB->ODR & GPIO_Pin_2) == RESET)

#define IS_AUTHORIZING_ACCESS_TOKEN()		((GPIOB->IDR & GPIO_Pin_1) != RESET)
#define IS_SET_ACCESS_TOKEN()				((GPIOI->IDR & GPIO_Pin_6) == RESET)

#define BUZZER_ON()							(GPIOA->BSRRL = GPIO_Pin_1)
#define BUZZER_OFF()						(GPIOA->BSRRH = GPIO_Pin_1)
#define READ_BUZZER()						((GPIOA->ODR) & GPIO_Pin_1)

extern void Motor_Configuration(MOTOR_TypeDef Motor);
extern void Sensor_Configuration(BYTE Sensor);
extern void Addr_Configuration(void);
extern void GPIO1_Configuration(void);
extern void GPIO2_Configuration(void);
extern void ReadMyAddr(WORD *arr);
extern void GetDrawEncoder(void);
extern void GetEncPoint(void);
extern void PutEncPoint(void);
extern void DrawerOperationProc(void);
extern void DrawStatusUpdate(void);
extern void SensorInputProc(void);
extern void DrawerLoopTest(void);
//extern void SineAccelerationTable(WORD array_size,WORD ratio, WORD min_freq, WORD max_freq);
extern void SineAccelerationTable(WORD array_size, WORD min_freq, WORD max_freq);
extern void DrawerAccRatioProc(void);
extern void DrawerWatchDog(void);
extern void GetAccessToken(void);
extern void GetSlotFunc(void);
extern void Buzzer_Configuration(void);
extern void BuzzerProc(void);
extern void MyLocation(void);
//extern void DisplayMainToken(void);
//extern void DisplayLastPos(void);
extern void DisplayChanges(void);
extern void Slot_Configuration(BYTE Slot);
extern void EXTI_Sensor_Enable(BYTE Sensor);
extern void EXTI_Sensor_Disable(BYTE Sensor);

//EEPROM
extern void EEP_Configuration(void);					//LMI
extern inline void EEP_WriteEnable(void);
extern inline void EEP_WriteDisable(void);
extern inline void EEP_SPI_SendInstruction(BYTE *pData, BYTE size);
extern void EEP_WriteStatusRegister(BYTE regval);
extern BYTE EEP_SPI_WaitStandbyState(void);
extern void EEP_SPI_WritePage(BYTE* pData, SHORT WriteAddr, SHORT NumByteToWrite);
extern void EEP_SPI_WriteBuffer(BYTE* pData, SHORT WriteAddr, SHORT NumByteToWrite);
extern void EEP_SPI_ReadBuffer(BYTE* pData, SHORT ReadAddr, SHORT NumByteToRead);
extern BYTE EEP_SPI_ReadData(WORD ReadToAddr);
extern BYTE EEP_SPI_WriteData(WORD WriteToAddr, BYTE WriteData);
extern void PutEncoder(WORD location_param, WORD encoder);


#endif		/* __MOTOR_H */

/*****************************************************************END OF FILE****/





