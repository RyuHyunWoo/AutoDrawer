/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file		TIMER.C
  * @author  	Firmware Team(Nexus)
  ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
const uint8_t TIM_SET_PREEMPTION_PRIORITY[TIMERn] = {NVIC_PREEMPTION_PRIORITY_0,NVIC_PREEMPTION_PRIORITY_0,NVIC_PREEMPTION_PRIORITY_0,NVIC_PREEMPTION_PRIORITY_0,NVIC_PREEMPTION_PRIORITY_0, NVIC_PREEMPTION_PRIORITY_0};
const uint8_t TIM_SET_SUB_PRIORITY[TIMERn] = {NVIC_SUB_PRIORITY_3,NVIC_SUB_PRIORITY_0,NVIC_SUB_PRIORITY_1,NVIC_SUB_PRIORITY_2,NVIC_SUB_PRIORITY_0, NVIC_SUB_PRIORITY_5};
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t _tick_count;
__IO WORD 	g_wTimerCnt100us;
__IO BOOL 	g_bTimerSync100us = false;
/* Private function prototypes -----------------------------------------------*/
void SysTimer_Configuration(void){
  	/* Setup SysTick Timer for 1 msec interrupts */
  	SysTick_Config(SystemCoreClock / 1000);
}

void Timer2_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM_SET_PREEMPTION_PRIORITY[TIM2_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM_SET_SUB_PRIORITY[TIM2_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Time base configuration */
	//TIM_TimeBaseStructure.TIM_Period = 25000 - 1;  // 1us * 50000 = 50ms
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;  // 1us * 50000 = 50ms
	TIM_TimeBaseStructure.TIM_Prescaler = 90 - 1; // 90 MHz/90 = 1Mhz(1us)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/* TIM enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

void Timer3_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM_SET_PREEMPTION_PRIORITY[TIM3_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM_SET_SUB_PRIORITY[TIM3_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 50 - 1;	// 1us * 1000 = 1ms
	TIM_TimeBaseStructure.TIM_Prescaler = 90 - 1; 	// 90MHz/90 = 1Mhz(1us)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	//TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	/* TIM enable counter */
	//TIM_Cmd(TIM3, ENABLE);
}

void Timer4_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM_SET_PREEMPTION_PRIORITY[TIM4_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM_SET_SUB_PRIORITY[TIM4_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1;	// 1us * 1000 = 1ms
	TIM_TimeBaseStructure.TIM_Prescaler = 90 - 1; 	// 90MHz/90 = 1Mhz(1us)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* TIM IT enable */
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	/* TIM enable counter */
	TIM_Cmd(TIM4, ENABLE);
}

void Timer5_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the TIM5 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM_SET_PREEMPTION_PRIORITY[TIM5_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM_SET_SUB_PRIORITY[TIM5_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 90 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	/* TIM IT enable */
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	/* TIM enable counter */
	TIM_Cmd(TIM5, ENABLE);
}

void Timer7_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the TIM7 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM_SET_PREEMPTION_PRIORITY[TIM7_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM_SET_SUB_PRIORITY[TIM7_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM7 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 90 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	/* TIM IT enable */
	//TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	/* TIM enable counter */
	//TIM_Cmd(TIM7, ENABLE);
}
#if 1
void Timer8_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the TIM8 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIM_SET_PREEMPTION_PRIORITY[TIM8_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIM_SET_SUB_PRIORITY[TIM8_PRIORITY];
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM8 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 90 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	/* TIM IT enable */
	//TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
	/* TIM enable counter */
	//TIM_Cmd(TIM8, ENABLE);
}
#endif

void Timer_Configuration(void){
	Timer2_Configuration();
	Timer3_Configuration();
	Timer4_Configuration();
	Timer5_Configuration();
	Timer7_Configuration();
}

void TIM7_INT_ENABLE(void)
{
	/* TIM clear */
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	/* TIM IT enable */
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	/* TIM7 enable counter */
	TIM_Cmd(TIM7, ENABLE);
}

void TIM7_INT_DISABLE(void)
{
	/* TIM clear */
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	/* TIM IT enable */
	TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE);
	/* TIM7 enable counter */
	TIM_Cmd(TIM7, DISABLE);
}

void TIM3_INT_ENABLE(void)
{
	/* TIM clear */
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	/* TIM IT enable */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	/* TIM7 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_INT_DISABLE(void)
{
	/* TIM clear */
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	/* TIM IT enable */
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
	/* TIM7 enable counter */
	TIM_Cmd(TIM3, DISABLE);
}
void Delay_100us(uint32_t time_us){		/* time delay for ms */
	uint32_t iTickCnt;
	iTickCnt = g_wTimerCnt100us;
	while(GetElapsed100usTickCnt(iTickCnt) < (time_us)){
		WatchDog();
	}
}

void Delay_Ms(uint32_t time_ms){		/* time delay for ms */
	uint32_t iTickCnt;
	iTickCnt = _tick_count;
	while(GetElapsedTickCount(iTickCnt) < (time_ms)){
		WatchDog();
	}
}

uint32_t GetElapsedTickCount(uint32_t tick){
	uint32_t current_tick;

	current_tick = _tick_count;

	if(current_tick >= tick)
		return current_tick - tick;
	else
		return 0xffffffff - tick + current_tick;
}

inline uint32_t GetElapsed100usTickCnt(uint32_t tick){
	uint32_t current_tick;

	current_tick = g_wTimerCnt100us;

	if(current_tick >= tick)
		return current_tick - tick;
	else
		return 0xffffffff - tick + current_tick;
}

void WatchDog(void)
{
	IWDG_ReloadCounter();
}

void Iwdg_Configuration(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(1000);

	while(IWDG_GetFlagStatus(IWDG_FLAG_RVU) == RESET);

	IWDG_Enable();
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

