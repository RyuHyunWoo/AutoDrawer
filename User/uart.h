/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file		UART.H
  * @author  	Firmware Team(Nexus)
  ******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported define -----------------------------------------------------------*/
#define ASCII_STX	0x02
#define ASCII_ETX	0x03
#define ASCII_EOT	0x04
#define ASCII_ENQ	0x05
#define ASCII_ACK	0x06
#define ASCII_NAK	0x15
#define ASCII_SYN	0x16

#define BRD_ADDR	0xBBBB


#define UART_RECEIVE_INTERVAL	15

#define REQ_VER					0x56
#define REQ_STATUS				0x53
#define REQ_INIT				0x49
#define REQ_MOVE				0x4D
#define REQ_LOCK				0x4C
#define REQ_LED_ON				0x41
#define REQ_ERR_CLR				0x43
#define REQ_DISPLAY_DRAW		0x44
#define REQ_CALIBRATION_RESET	0x45
#define RECV_FAULT_CST			0x46
#define REQ_MOVE_FAULT_CST		0x4A
#define RECV_OK					0x06

#define _DEBUG_UART_SEND_BUFFER_SIZE    1024
#define _DEBUG_UART_RECEIVE_BUFFER_SIZE 256

#define _DEBUG_UART_SEND_DMA_SIZE		1024

#define USART_DEBUG_TX_PIN					GPIO_Pin_6
#define USART_DEBUG_RX_PIN					GPIO_Pin_7
#define USART_DEBUG_GPIO_PORT				GPIOC
#define USART_DEBUG_GPIO_CLK				RCC_AHB1Periph_GPIOC

#define USART1_TX_PIN						GPIO_Pin_9
#define USART1_RX_PIN						GPIO_Pin_10
#define USART1_GPIO_PORT					GPIOA
#define USART1_GPIO_CLK						RCC_AHB1Periph_GPIOA

#define _MAIN_UART_RECEIVE_BUFFER_SIZE	8192
#define _MAIN_UART_RECRIVE_PAYLOAD_SIZE	256

#define _MAIN_UART_SEND_BUFFER_SIZE		256
#define _MAIN_UART_SEND_PAYLOAD_SIZE	128
#define _MAIN_UART_SEND_DMA_SIZE		256

#define _MAIN_UART_SEND_BUFFER_ARRY		5

#define _UART_PRINT_BLOCK_NUMBER_SIZE	2

//BOOTLOADER
#define _CST_CMD_FWUPDATA_START		0x65
#define _FW_UPDATE_KEY				0x55
#define _BOOT_CHECK_ADDRESS			0x100

#define USARTn		3
/* Exported types ------------------------------------------------------------*/
typedef enum{
	STATUS_1ST = 0,
	STATUS_2ND,
	STATUS_RST = 3,
}status_enum_typedef;

typedef struct debug_send_module{
	volatile WORD put_index;
	volatile WORD get_index;

	volatile WORD dma_put_index;
	volatile WORD dma_get_index;

	volatile BOOL transmit_line_ready;


	BYTE dma_buffer[_DEBUG_UART_SEND_DMA_SIZE];
	WORD dma_count;

	BYTE buffer[_DEBUG_UART_SEND_BUFFER_SIZE];
	volatile BOOL busy;
}debug_uart_send;

typedef struct debug_receive_module{
	volatile WORD put_index;
	volatile WORD get_index;
	BYTE command;
	BYTE length;
	BYTE buffer[_DEBUG_UART_RECEIVE_BUFFER_SIZE];
	BYTE packet_number;
	BYTE packet_number_prev;
	BYTE packet_Addrh;
	BYTE packet_Addrl;
	BYTE packet_Addr;

	BYTE lrc;

	BYTE parsing_count;

	BYTE ext_command;
	WORD last_time;

	BYTE receive_cmd;
}debug_uart_receive;

typedef struct _uart_buffer_module{
	BYTE count;
	BYTE data[_MAIN_UART_SEND_BUFFER_SIZE];
}uart_buffer_module;

typedef struct _main_uart_send_module{
	volatile BYTE dma_put_index;
	volatile BYTE dma_get_index;

	volatile BOOL transmit_line_ready;

	BYTE buffer_put_index;
	BYTE buffer_get_index;
	uart_buffer_module buffer[_MAIN_UART_SEND_BUFFER_ARRY];

	BYTE payload[_MAIN_UART_SEND_PAYLOAD_SIZE];
	BYTE packet_number;

	device_address length;

	BYTE command;
	BYTE extension_command;
}main_uart_send;

typedef struct _main_uart_receive_module{
#if(_MAIN_UART_RECEIVE_BUFFER_SIZE == 256)
	volatile BYTE put_index;
	volatile BYTE get_index;
#else
	volatile WORD put_index;
	volatile WORD get_index;
#endif
	BYTE buffer[_MAIN_UART_RECEIVE_BUFFER_SIZE];
	BYTE payload[_MAIN_UART_RECRIVE_PAYLOAD_SIZE];
	BYTE packet_number;
	BYTE packet_number_prev;

	device_address length;
	BYTE lrc;

	BYTE parsing_count;

	BYTE command;
	BYTE extension_command;

	device_address address;

	WORD last_time;
}main_uart_receive;

#define _MAIN_UART_TXE_ENABLE()		_main_send.busy = _TRUE;		\
									USART_ITConfig(USART6, USART_IT_TXE, ENABLE)

#define _MAIN_UART_TXE_DISABLE()	_main_send.busy = _FALSE;		\
									USART_ITConfig(USART6, USART_IT_TXE, DISABLE)

#define _IS_MAIN_UART_TX_BUSY()   	(_main_send.busy)
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern debug_uart_send 	_debug_send;
extern debug_uart_receive 	_debug_receive;

extern main_uart_send _main_send;
extern main_uart_receive _main_receive;

/* Exported functions ------------------------------------------------------- */
extern void Debug_Send_Process(void);
extern void Main_Send_Process(void);
extern void Usart_Configuration(void);
extern void USART6_DMA_Configuration(void);
extern void USART6_Configuration(void);
extern BYTE RecvPcPacket(void);
extern void RecvPcProc(void);
extern void ReqStatus(void);
#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


