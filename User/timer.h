/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file		TIMER.H
  * @author  	Firmware Team(Nexus)
  ******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
#define TIMERn		6

typedef enum{
	TIM2_PRIORITY = 0,
	TIM3_PRIORITY,
	TIM4_PRIORITY,
	TIM5_PRIORITY,
	TIM7_PRIORITY,
	TIM8_PRIORITY,
}TIM_PRIORITY_Typedef;
/* Exported constants --------------------------------------------------------*/
extern __IO uint32_t _tick_count;
extern __IO WORD g_wTimerCnt100us;
extern __IO BOOL g_bTimerSync100us;
/* Exported define -----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void SysTimer_Configuration(void);
extern void Timer_Configuration(void);
extern void Timer8_Configuration(void);
extern void TIM7_INT_ENABLE(void);
extern void TIM7_INT_DISABLE(void);
extern void Delay_Ms(uint32_t time_ms);
extern void Delay_100us(uint32_t time_us);
extern uint32_t GetElapsedTickCount(uint32_t tick);
extern uint32_t GetElapsed100usTickCnt(uint32_t tick);
extern void WatchDog(void);
extern void Iwdg_Configuration(void);
extern void TIM8_INT_ENABLE(void);
extern void TIM8_INT_DISABLE(void);
extern void TIM3_INT_ENABLE(void);
extern void TIM3_INT_DISABLE(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H__ */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

