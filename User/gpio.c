/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file		GPIO.C
  * @author  	Firmware Team(Nexus)
  ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void LCD_Back_Light_Initialize(void){
	GPIO_InitTypeDef GPIO_InitStructure;

/* GPIOA,GPIOB,GPIOC,GPIOD clock enable */
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);

	GPIO_InitStructure.GPIO_Pin = D_OUT_LCD_BACKLIGHT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	BACK_LIGHT_OFF();
}

void RUNLED_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI , ENABLE);

	GPIO_InitStructure.GPIO_Pin = I_OUT_RUNLED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOI, &GPIO_InitStructure);
}

void UART_RST_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = A_OUT_USART_RTS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TX_DISABLE();
}

void GPIO1_Configuration(void)
{
	Motor_Configuration(MOTOR_DIR);
	Motor_Configuration(MOTOR_RUN);

	RUNLED_Configuration();
	LCD_Back_Light_Initialize();

	Addr_Configuration();
	EEP_Configuration();
	UART_RST_Configuration();
}

void GPIO2_Configuration(void)
{
	for(BYTE i=0; i<SENSORn; i++){
		Sensor_Configuration(i);
	}

	for(BYTE i=0; i<SLOTn; i++){
		Slot_Configuration(i);
	}

	Buzzer_Configuration();
}

void Toggle_RUNLED(void){
	static WORD last_time;

	if(GetElapsedTickCount(last_time)>500){
		TOOGLE_RUNLED();
		last_time=_tick_count;
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

