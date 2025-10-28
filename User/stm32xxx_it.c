/**
  ******************************************************************************
  * @file    stm32xxx_it.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    22-September-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t _tick_count;
__IO unsigned short _v_us_timer_1msec_count = 0;
/* Private function prototypes -----------------------------------------------*/
#if defined (STM32F429_439xx)
extern void LTDC_ISR_Handler(void);
extern void DMA2D_ISR_Handler(void);
#endif

extern __IO int32_t OS_TimeMS;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*             Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}



/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void){
  	OS_TimeMS++;
}

void TIM2_IRQHandler(void){					// 25ms Timer Interrupt
	TIM2->SR = (uint16_t)~TIM_IT_Update;
	_handle_touchflag = true;
}

void TIM3_IRQHandler(void){					// 100us Timer Interrupt
	TIM3->SR = (uint16_t)~TIM_IT_Update;
#if 0
	if(IS_AUTHORIZING_ACCESS_TOKEN()){
		if(draw_order.off_token) 	draw_order.off_token = 0;

		if(draw_order.on_token < CHATTERING_COUNT){
			draw_order.on_token++;
		}else{
			draw_order.order_list.bit.auth_access_token = true;
			draw_order.on_token = 0;
			TIM3_INT_DISABLE();
			//printf("authorizing on token\r\n");
		}
	}else{
		if(draw_order.on_token)		draw_order.on_token = 0;

		if(draw_order.off_token < CHATTERING_COUNT){
			draw_order.off_token++;
		}else{
			draw_order.order_list.bit.auth_access_token = false;
			draw_order.off_token = 0;
			TIM3_INT_DISABLE();
			//printf("authorizing off token\r\n");
		}
	}
#endif

}

void TIM4_IRQHandler(void){					// 1mSec Timer
	TIM4->SR = (uint16_t)~TIM_IT_Update;
	_tick_count++;
}

void TIM5_IRQHandler(void){					//100us Timer
	TIM5->SR = (uint16_t)~TIM_IT_Update;
	g_wTimerCnt100us++;
	g_bTimerSync100us = true;
}

void TIM8_IRQHandler(void){		//100us Timer
	TIM8->SR = (uint16_t)~TIM_IT_Update;
}


void TIM7_IRQHandler(void){		//100us Timer
	TIM7->SR = (uint16_t)~TIM_IT_Update;
	//TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

	if(pwm_status.pwm_list.bit.operation == true){
		if(pwm_status.pwm_list.bit.acceleration == true){
			if(pwm_status.reload < pwm_status.table_size - 1){
				if(pwm_status.pwm_list.bit.phase == true){
					AC_MOTOR_RUN();
					TIM7->ARR = TIMER_PERIOD_MAX - sine_acc_32[pwm_status.reload];
				}else{
					AC_MOTOR_BRAKE();
					TIM7->ARR = sine_acc_32[pwm_status.reload];
					if(pwm_status.reload < (pwm_status.table_size - 1))		pwm_status.reload++;
				}
				pwm_status.pwm_list.bit.phase = !pwm_status.pwm_list.bit.phase;
			}else{
				if(pwm_status.pwm_list.bit.phase == true){
					AC_MOTOR_RUN();
					TIM7->ARR = TIMER_PERIOD_MAX - sine_acc_32[pwm_status.table_size - 1];
				}else{
					AC_MOTOR_BRAKE();
					TIM7->ARR = sine_acc_32[pwm_status.table_size - 1];
				}
				pwm_status.pwm_list.bit.phase = !pwm_status.pwm_list.bit.phase;
			}
		}else if(pwm_status.pwm_list.bit.deceleration == true){
			if(pwm_status.reload > 0){
				if(pwm_status.pwm_list.bit.phase == true){
					AC_MOTOR_RUN();
					TIM7->ARR = TIMER_PERIOD_MAX - sine_acc_32[pwm_status.reload];
				}else{
					AC_MOTOR_BRAKE();
					TIM7->ARR = sine_acc_32[pwm_status.reload];
					if(pwm_status.reload > 0)			pwm_status.reload--;
				}
			}else{
				if(draw_order.order_list.bit.intermediate_stop == true){
					draw_order.order_list.bit.intermediate_stop = false;
					draw_order.order_list.bit.stop_order = true;
				}else{
					if(pwm_status.pwm_list.bit.phase == true){
						AC_MOTOR_RUN();
						TIM7->ARR = TIMER_PERIOD_MAX - sine_acc_32[0];
					}else{
						AC_MOTOR_BRAKE();
						TIM7->ARR = sine_acc_32[0];
					}
					draw_status.status_list.bit.active = false;
				}
			}
			pwm_status.pwm_list.bit.phase = !pwm_status.pwm_list.bit.phase;
		}else{
			if(pwm_status.pwm_list.bit.phase == true){
				AC_MOTOR_RUN();
				TIM7->ARR = (1000-acc_freq_array[MANUAL_MOVING_SPD]);
			}else{
				AC_MOTOR_BRAKE();
				TIM7->ARR = acc_freq_array[MANUAL_MOVING_SPD];
			}
			pwm_status.pwm_list.bit.phase = !pwm_status.pwm_list.bit.phase;
		}
	}else{
		draw_order.order_list.bit.intermediate_stop = false;
		AC_MOTOR_BRAKE();
		TIM7_INT_DISABLE();
	}
}

void USART1_IRQHandler(void){
	if((USART1->CR1 & USART_CR1_TCIE) && (USART1->SR & USART_FLAG_TC)){
		USART1->CR1 &= ~USART_CR1_TCIE;
		_main_send.transmit_line_ready = _TRUE;
		TX_DISABLE();
	}
}

void DMA2_Stream7_IRQHandler(void){					// USART1 TX DMA
	if((DMA2_Stream7->CR & DMA_SxCR_TCIE) && (DMA2->HISR & DMA_HISR_TCIF7)){
		DMA2->HIFCR = DMA_HIFCR_CTCIF7;
		USART1->CR1 |= USART_CR1_TCIE;
	}
}

void DMA2_Stream6_IRQHandler(void){					// USART6 TX DMA
	if((DMA2_Stream6->CR & DMA_SxCR_TCIE) && (DMA2->HISR & DMA_HISR_TCIF6)){
		_debug_send.transmit_line_ready = true;
		DMA2->HIFCR = DMA_HIFCR_CTCIF6;
	}
}
/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}


#if defined (STM32F429_439xx)
/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
  LTDC_ISR_Handler();
}

/**
  * @brief  This function handles DMA2D global interrupt request.
  * @param  None
  * @retval None
  */
void DMA2D_IRQHandler(void)
{
  DMA2D_ISR_Handler();
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
