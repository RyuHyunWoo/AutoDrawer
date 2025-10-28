/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file		TOUCH.C
  * @author  	Firmware Team(Nexus)
  ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define THRESHOLD 			2

#if 1
#define TOUCH_NOT_TP_COUNT	3
#define TOUCH_VALUE_ARRY 	9
#define TOUCH_INVALID_COUNT	5
#else
#define TOUCH_NOT_TP_COUNT	6
#define TOUCH_VALUE_ARRY 	18
#define TOUCH_INVALID_COUNT	10
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
matrix _matrix;
coordinate _display;
coordinate _screen_sample[3] = {
			{ 3284, 481 },
			{ 3075, 3258},
            { 548, 2039 }};
coordinate _display_sample[3] = {
         	{ 45, 45 },
			{ 400,60 },
            { 240,250}};

coordinate _new_screen_sample[9];
coordinate _new_display_sample[9];

volatile BYTE _handle_touchflag;

BYTE _spi2_rx_buffer[6];
BYTE _spi2_tx_buffer[6] = {CHX,0,0,CHY,0,0};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void ADS7843_SPI_Configuration(void){
  	SPI_InitTypeDef SPI_InitStruct;

  	RCC_APB1PeriphClockCmd(Open_RCC_SPI,ENABLE);

  	SPI_I2S_DeInit(Open_SPI);
  	/* Open_SPI Config -------------------------------------------------------------*/
  	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
  	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
  	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  	SPI_InitStruct.SPI_CRCPolynomial = 7;

  	SPI_Init(Open_SPI, &SPI_InitStruct);
	SPI_Cmd(Open_SPI, ENABLE);

	ADS7843_DmaRx_Configuration();
	ADS7843_DmaTx_Configuration();
}

void ADS7843_DmaRx_Configuration(void){
  	DMA_InitTypeDef DMA_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	DMA_DeInit(DMA1_Stream3);
	while(DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);

	DMA_StructInit(&DMA_InitStructure);

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					  // Mode fifo valide
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOMode_Disable;	  // Taille de la fifo : HalfFull (2 words, 8 octets)
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 			  // Transfert en memoire en un seul burst
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 	  // Transfert du peripherique en 1 seul burst

  	DMA_InitStructure.DMA_Channel = DMA_Channel_0;							  // DMA channel 0
	DMA_InitStructure.DMA_BufferSize = 3;
  	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
  	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)_spi2_rx_buffer;

   	DMA_Init(DMA1_Stream3, &DMA_InitStructure);
	SPI_I2S_DMACmd(Open_SPI, SPI_I2S_DMAReq_Rx, ENABLE);
}

void ADS7843_DmaTx_Configuration(void){
  	DMA_InitTypeDef DMA_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	DMA_DeInit(DMA1_Stream4);
	while(DMA_GetCmdStatus(DMA1_Stream4) != DISABLE);

	DMA_StructInit(&DMA_InitStructure);

	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;					  // Mode fifo valide
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOMode_Disable;	  // Taille de la fifo : HalfFull (2 words, 8 octets)
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 			  // Transfert en memoire en un seul burst
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 	  // Transfert du peripherique en 1 seul burst

  	DMA_InitStructure.DMA_Channel = DMA_Channel_0;							  // DMA channel 0
	DMA_InitStructure.DMA_BufferSize = 3;
  	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
  	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)_spi2_tx_buffer;

   	DMA_Init(DMA1_Stream4, &DMA_InitStructure);
	SPI_I2S_DMACmd(Open_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
}

void TSC_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(Open_SPI_SCK_GPIO_CLK | Open_SPI_MISO_GPIO_CLK | Open_SPI_MOSI_GPIO_CLK,ENABLE);

	RCC_AHB1PeriphClockCmd(Open_TP_CS_CLK | Open_TP_IRQ_CLK,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	Open_SPI_CLK_INIT(Open_RCC_SPI,ENABLE);

	GPIO_PinAFConfig(Open_SPI_SCK_GPIO_PORT,  Open_SPI_SCK_SOURCE,  Open_GPIO_AF_SPI);
	GPIO_PinAFConfig(Open_SPI_MISO_GPIO_PORT, Open_SPI_MISO_SOURCE, Open_GPIO_AF_SPI);
	GPIO_PinAFConfig(Open_SPI_MOSI_GPIO_PORT, Open_SPI_MOSI_SOURCE, Open_GPIO_AF_SPI);

	GPIO_InitStructure.GPIO_Pin = Open_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(Open_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Open_SPI_MISO_PIN;
	GPIO_Init(Open_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Open_SPI_MOSI_PIN;
	GPIO_Init(Open_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  	/*7 inch TP_CS  */
  	GPIO_InitStructure.GPIO_Pin = Open_TP_CS_PIN;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  	GPIO_Init(Open_TP_CS_PORT, &GPIO_InitStructure);

   	/*4.3 inch TP_CS  */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_Init(GPIOI, &GPIO_InitStructure);

    /*TP_IRQ */
    GPIO_InitStructure.GPIO_Pin = Open_TP_IRQ_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Open_TP_IRQ_PORT, &GPIO_InitStructure);

  	GPIO_SetBits(GPIOI,GPIO_Pin_3);
  	TP_CS(0);
  	ADS7843_SPI_Configuration();
}

void SPI_DMA_WRITE(void){
	DMA1_Stream3->M0AR = (uint32_t)_spi2_rx_buffer;
    DMA1_Stream3->NDTR = 6;
	DMA1_Stream4->M0AR = (uint32_t)_spi2_tx_buffer;
    DMA1_Stream4->NDTR = 6;

	/* Enable SPI Rx/Tx DMA Request*/
	DMA_Cmd(DMA1_Stream3, ENABLE);
	DMA_Cmd(DMA1_Stream4, ENABLE);
}

#if 0
static void DelayUS(vu32 cnt){
  	uint16_t i;
  	for(i = 0;i<cnt;i++){
     	uint8_t us = 10;
     	while(us--){;}
  	}
}

static void SPI_Write_Cmd(uint8_t cmd){
	USHORT timeout;

  	/* Wait for SPI3 Tx buffer empty */
  	while((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET);
  	/* Send SPI3 data */
  	SPI_I2S_SendData(Open_SPI,cmd);
  	/* Wait for SPI3 data reception */
  	timeout = 0;
	do{
		if(SPI_I2S_GetFlagStatus(Open_SPI, SPI_I2S_FLAG_RXNE) == SUCCESS)		break;
		else																	timeout++;
	}while(timeout < SPI_TIMEOUT_COUNT);
	if(timeout == SPI_TIMEOUT_COUNT)		return;
  	/* Read Open_SPI received data */
  	SPI_I2S_ReceiveData(Open_SPI);
}

static int SPI_Read_Analog(uint8_t cmd, uint8_t *err){
  	unsigned short buf,temp;
	USHORT timeout;
	uint8_t result;

  	/* Wait for Open_SPI Tx buffer empty */
  	while((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET);
  	/* Send Open_SPI data */
  	SPI_I2S_SendData(Open_SPI,0x0000);
  	/* Wait for SPI3 data reception */
  	timeout = 0;
	do{
		if(SPI_I2S_GetFlagStatus(Open_SPI, SPI_I2S_FLAG_RXNE) == SUCCESS){
			result = false;
			timeout=0;
			break;
		}else{
			timeout++;
		}
	}while(timeout < SPI_TIMEOUT_COUNT);

	if(timeout == SPI_TIMEOUT_COUNT){
		result = true;
		*err = result;
	}

  	/* Read Open_SPI received data */
  	temp=SPI_I2S_ReceiveData(Open_SPI);
  	buf=temp<<8;
  	DelayUS(1);
  	while((SPI2->SR & SPI_I2S_FLAG_TXE) == RESET);
  	/* Send Open_SPI data */
  	SPI_I2S_SendData(Open_SPI,0x0000);
  	/* Wait for Open_SPI data reception */
	timeout = 0;
	do{
		if(SPI_I2S_GetFlagStatus(Open_SPI, SPI_I2S_FLAG_RXNE) == SUCCESS){
			result = false;
			timeout=0;
			break;
		}else{
			timeout++;
		}
	}while(timeout < SPI_TIMEOUT_COUNT);

	if(timeout == SPI_TIMEOUT_COUNT){
		result = true;
		*err = result;
	}
  	/* Read Open_SPI received data */
  	temp=SPI_I2S_ReceiveData(Open_SPI);
  	buf |= temp;
  	buf>>=3;
  	buf&=0xfff;
  	return buf;
}

int SPI_Read_X_Position(void){
  	int i;
	uint8_t err = false;

  	DelayUS(1);
  	SPI_Write_Cmd(CHX);
  	DelayUS(1);
  	i = SPI_Read_Analog(CHX, &err);
	if(err == true){
		i = 4096;
	}
  	return i;
}

int SPI_Read_Y_Position(void){
  	int i;
	uint8_t err = false;

  	DelayUS(1);
  	SPI_Write_Cmd(CHY);
  	DelayUS(1);
  	i = SPI_Read_Analog(CHY, &err);
	if(err == true){
		i=0;
	}
  	return i;
}

void TP_Get_XY_Position(int *x,int *y){
  	int adx,ady;
  	adx = SPI_Read_X_Position();
  	DelayUS(1);
  	ady = SPI_Read_Y_Position();
  	*x = adx;
  	*y = ady;
}

coordinate *Read_Ads7846(void){
  	static coordinate  screen;
  	int m0,m1,m2,TP_X,TP_Y,temp[3];
  	uint8_t count=0,invalid_count = 0;;
  	int buffer[2][TOUCH_VALUE_ARRY]={{0},{0}};
	int pre_buffer[2];
	uint8_t retry=0;
	uint8_t press_irq_count = 0;

	uint8_t arry=TOUCH_VALUE_ARRY/3;

	screen.pressed = _FALSE;

	do{
		if(!TP_INT_IN){
			TP_Get_XY_Position(&TP_X,&TP_Y);
			if((TP_X < 4095) && (TP_Y > 0)){
				if(count){
					if( ( (TP_X-pre_buffer[0]<20) && (TP_X-pre_buffer[0]>-20) ) &&
						( (TP_Y-pre_buffer[1]<20) && (TP_Y-pre_buffer[1]>-20) ) ){
						buffer[0][count]=TP_X;
						buffer[1][count++]=TP_Y;
						pre_buffer[0]=TP_X;
						pre_buffer[1]=TP_Y;
						retry=0;
					}else{
						if(retry>5){
							count=0;
							retry=0;
						}else{
							retry++;
#ifdef DEBUG_TOUCH
							Myprintf("%d %d %d %d %d %d\n\r",TP_X,pre_buffer[0],TP_Y,pre_buffer[1],count,retry);
#endif
						}
					}
				}else{
					buffer[0][count]=TP_X;
					buffer[1][count++]=TP_Y;
					pre_buffer[0]=TP_X;
					pre_buffer[1]=TP_Y;
				}
			}else{
				invalid_count++;
			}
			press_irq_count = 0;
		}else{
			press_irq_count++;
		}
  	}while((invalid_count < TOUCH_INVALID_COUNT) &&
  		(press_irq_count < TOUCH_NOT_TP_COUNT) &&
  		(count < TOUCH_VALUE_ARRY));  /* TP_INT_IN  */

	if(press_irq_count == TOUCH_NOT_TP_COUNT){
		screen.state = TOUCH_STATE_IDLE;
		return &screen;
	}

	if(invalid_count == TOUCH_INVALID_COUNT){
		screen.state = TOUCH_STATE_IDLE;
		return &screen;
	}

#if 0
  	temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2]+buffer[0][3]+buffer[0][4])/5;
	temp[1]=(buffer[0][5]+buffer[0][6]+buffer[0][7]+buffer[0][8]+buffer[0][9])/5;
	temp[2]=(buffer[0][10]+buffer[0][11]+buffer[0][12]+buffer[0][13]+buffer[0][14])/5;
#else
	temp[0]=0;
	temp[1]=0;
	temp[2]=0;

	for(char i=0;i<arry;i++){
		temp[0]+=buffer[0][i];
		temp[1]+=buffer[0][arry+i];
		temp[2]+=buffer[0][arry*2+i];
	}
	temp[0]=temp[0]/arry;
	temp[1]=temp[1]/arry;
	temp[2]=temp[2]/arry;
#endif
	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];

	m0=m0>0?m0:(-m0);
  	m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);

	if((m0 > THRESHOLD) && (m1 > THRESHOLD) && (m2 > THRESHOLD)){
		screen.state = TOUCH_STATE_X_UNKONW;
		return &screen;
	}

	if(m0<m1){
		if(m2<m0){
	   		screen.x=(temp[0]+temp[2])/2;
		}else{
	   		screen.x=(temp[0]+temp[1])/2;
		}
	}else if(m2<m1){
		screen.x=(temp[0]+temp[2])/2;
	}else{
		screen.x=(temp[1]+temp[2])/2;
	}

	/* Average Y  */
#if 0
  	temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2]+buffer[1][3]+buffer[1][4])/5;
	temp[1]=(buffer[1][5]+buffer[1][6]+buffer[1][7]+buffer[1][8]+buffer[1][9])/5;
	temp[2]=(buffer[1][10]+buffer[1][11]+buffer[1][12]+buffer[1][13]+buffer[1][14])/5;
#else
	temp[0]=0;
	temp[1]=0;
	temp[2]=0;

	for(char i=0;i<arry;i++){
		temp[0]+=buffer[1][i];
		temp[1]+=buffer[1][arry+i];
		temp[2]+=buffer[1][arry*2+i];
	}
	temp[0]=temp[0]/arry;
	temp[1]=temp[1]/arry;
	temp[2]=temp[2]/arry;

#endif
	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];

	m0=m0>0?m0:(-m0);
	m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);

	if((m0 > THRESHOLD) && (m1 > THRESHOLD) && (m2 > THRESHOLD)){
		screen.pressed = TOUCH_STATE_Y_UNKONW;
		return &screen;
	}

	if(m0<m1){
		if(m2<m0){
	  		screen.y=(temp[0]+temp[2])/2;
		}else{
	   		screen.y=(temp[0]+temp[1])/2;
		}
    }else if(m2<m1){
		screen.y=(temp[0]+temp[2])/2;
    }else{
		screen.y=(temp[1]+temp[2])/2;
    }

	screen.state = TOUCH_STATE_PRESS;

	return &screen;
}
#endif
FunctionalState setCalibrationMatrix(coordinate * displayPtr,
                          							coordinate * screenPtr,matrix * matrixPtr){
  	FunctionalState retTHRESHOLD = ENABLE ;
  	/* K£½(X0£­X2) (Y1£­Y2)£­(X1£­X2) (Y0£­Y2) */
  	matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) -
                       ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  	if(matrixPtr->Divider == 0){
    	retTHRESHOLD = DISABLE;
  	}else{
    	/* A£½((XD0£­XD2) (Y1£­Y2)£­(XD1£­XD2) (Y0£­Y2))£¯K	*/
    	matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) -
       		            ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
		/* B£½((X0£­X2) (XD1£­XD2)£­(XD0£­XD2) (X1£­X2))£¯K	*/
    	matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) -
    	                ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
    	/* C£½(Y0(X2XD1£­X1XD2)+Y1(X0XD2£­X2XD0)+Y2(X1XD0£­X0XD1))£¯K */
    	matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                    	(screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                    	(screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
    	/* D£½((YD0£­YD2) (Y1£­Y2)£­(YD1£­YD2) (Y0£­Y2))£¯K	*/
    	matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) -
                    	((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
    	/* E£½((X0£­X2) (YD1£­YD2)£­(YD0£­YD2) (X1£­X2))£¯K	*/
    	matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) -
                    	((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
    	/* F£½(Y0(X2YD1£­X1YD2)+Y1(X0YD2£­X2YD0)+Y2(X1YD0£­X0YD1))£¯K */
    	matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                    	(screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                    	(screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
  	}
  	return(retTHRESHOLD) ;
}

FunctionalState getDisplayPoint(coordinate * displayPtr,
                     						coordinate * screenPtr,matrix * matrixPtr){
  	FunctionalState retTHRESHOLD = ENABLE;
  	/*
		An=168
	*/
  	if(matrixPtr->Divider != 0){
    	/* XD = AX+BY+C */
    	displayPtr->x = ( (matrixPtr->An * screenPtr->x) +
                      	(matrixPtr->Bn * screenPtr->y) +
                       	matrixPtr->Cn
                    	) / matrixPtr->Divider ;
		/* YD = DX+EY+F */
    	displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) +
                      	(matrixPtr->En * screenPtr->y) +
                       	matrixPtr->Fn
                    	) / matrixPtr->Divider ;
  	}else{
    	retTHRESHOLD = DISABLE;
  	}
  	return(retTHRESHOLD);
}

BYTE Touch_State_Shaft_X(int *buffer,coordinate *screen){
	int temp[3] = {0,0,0};
	int m0,m1,m2;
	uint8_t arry = TOUCH_VALUE_ARRY / 3;

	for(char i = 0;i < arry;i++){
		temp[0] += buffer[i];
		temp[1] += buffer[arry + i];
		temp[2] += buffer[arry * 2 + i];
	}
	temp[0] = temp[0] / arry;
	temp[1] = temp[1] / arry;
	temp[2] = temp[2] / arry;

	m0 = temp[0] - temp[1];
	m1 = temp[1] - temp[2];
	m2 = temp[2] - temp[0];

	m0 = m0 > 0 ? m0 : (-m0);
	m1 = m1 > 0 ? m1 : (-m1);
	m2 = m2 > 0 ? m2 : (-m2);

	if((m0 > THRESHOLD) && (m1 > THRESHOLD) && (m2 > THRESHOLD)){
		return TRUE;
	}else{
		if(m0 < m1){
			if(m2 < m0){
		 		screen->x = (temp[0] + temp[2]) / 2;
			}else{
		   		screen->x = (temp[0] + temp[1]) / 2;
			}
		}else if(m2 < m1){
			screen->x = (temp[0] + temp[2]) / 2;
		}else{
			screen->x = (temp[1] + temp[2]) / 2;
		}
		return FALSE;
	}
}

BYTE Touch_State_Shaft_Y(int *buffer,coordinate *screen){
	int temp[3] = {0,0,0};
	int m0,m1,m2;
	uint8_t arry = TOUCH_VALUE_ARRY / 3;

	for(char i = 0;i < arry;i++){
		temp[0] += buffer[i];
		temp[1] += buffer[arry + i];
		temp[2] += buffer[arry * 2 + i];
	}
	temp[0] = temp[0] / arry;
	temp[1] = temp[1] / arry;
	temp[2] = temp[2] / arry;

	m0 = temp[0] - temp[1];
	m1 = temp[1] - temp[2];
	m2 = temp[2] - temp[0];

	m0 = m0 > 0 ? m0 : (-m0);
	m1 = m1 > 0 ? m1 : (-m1);
	m2 = m2 > 0 ? m2 : (-m2);

	if((m0 > THRESHOLD) && (m1 > THRESHOLD) && (m2 > THRESHOLD)){
		return TRUE;
	}else{
		if(m0 < m1){
			if(m2 < m0){
		 		screen->y = (temp[0] + temp[2]) / 2;
			}else{
		   		screen->y = (temp[0] + temp[1]) / 2;
			}
		}else if(m2 < m1){
			screen->y = (temp[0] + temp[2]) / 2;
		}else{
			screen->y = (temp[1] + temp[2]) / 2;
		}
		return FALSE;
	}
}

void Touch_Process(void){
	GUI_PID_STATE TS_State;
	static coordinate screen;
	static uint8_t touch_old_change = TOUCH_CHANGE_IDLE;
	static uint8_t touch_change = TOUCH_CHANGE_IDLE;
  	static uint8_t count = 0,invalid_count = 0;;
  	static int buffer[2][TOUCH_VALUE_ARRY]={{0},{0}};
	static int pre_buffer[2];
	static uint8_t retry = 0;
	static uint8_t press_irq_count = 0;
	static BYTE state = TOUCH_IDLE;
	static int TP_X,TP_Y;

	switch(state){
		case TOUCH_IDLE:
			if(_handle_touchflag){
				_handle_touchflag = FALSE;
				TP_CS(0);
				count = 0;
				retry = 0;
				invalid_count = 0;
				press_irq_count = 0;
				screen.pressed = FALSE;
				buffer[0][0] = 0;
				buffer[1][0] = 0;
				state = TOUCH_CS_DELAY;
			}
			break;
		case TOUCH_CS_DELAY:
			state = TOUCH_PIN_CHECK;
			break;
		case TOUCH_PIN_CHECK:
			if(!TP_INT_IN){
				SPI_DMA_WRITE();
				state = TOUCH_READ_END;
			}else{
				press_irq_count++;
				if(press_irq_count == TOUCH_NOT_TP_COUNT){
					screen.state = TOUCH_STATE_IDLE;
					state = TOUCH_RESULT;
					TP_CS(1);
				}
			}
		case TOUCH_READ_END:
			if((DMA_GetFlagStatus(DMA1_Stream3, DMA_FLAG_TCIF3) == SET) &&
				(DMA_GetFlagStatus(DMA1_Stream4, DMA_FLAG_TCIF4) == SET)){

				DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
				DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);

				DMA_Cmd(DMA1_Stream3, DISABLE);
				DMA_Cmd(DMA1_Stream4, DISABLE);

				TP_X = (((_spi2_rx_buffer[1] << 8) | _spi2_rx_buffer[2]) >> 3) & 0xfff;
				TP_Y = (((_spi2_rx_buffer[4] << 8) | _spi2_rx_buffer[5]) >> 3) & 0xfff;
				if((TP_X > 0) && (TP_Y > 0)){
					if(count){
						if(((TP_X - pre_buffer[0] < 20) && (TP_X - pre_buffer[0] > -20)) &&
							((TP_Y - pre_buffer[1] < 20) && (TP_Y - pre_buffer[1] > -20))){
							buffer[0][count] = TP_X;
							buffer[1][count++] = TP_Y;
							pre_buffer[0] = TP_X;
							pre_buffer[1] = TP_Y;
							retry = 0;
						}else{
							if(retry > 5){
								count = 0;
								retry = 0;
							}else{
								retry++;
							}
						}
					}else{
						buffer[0][count] = TP_X;
						buffer[1][count++] = TP_Y;
						pre_buffer[0] = TP_X;
						pre_buffer[1] = TP_Y;
					}

					if(count == TOUCH_VALUE_ARRY){
						screen.state = TOUCH_STATE_CHECK;
						state = TOUCH_RESULT;
						TP_CS(1);
					}else{
						state = TOUCH_PIN_CHECK;
					}
				}else{
					invalid_count++;
					if(invalid_count == TOUCH_INVALID_COUNT){
						screen.state = TOUCH_STATE_IDLE;
						state = TOUCH_RESULT;
						TP_CS(1);
					}else{
						state = TOUCH_PIN_CHECK;
					}
				}
				press_irq_count = 0;
			}
			break;
		case TOUCH_RESULT:
			if(screen.state == TOUCH_STATE_CHECK){
				if(Touch_State_Shaft_X(&buffer[0][0],&screen)){
					screen.state = TOUCH_STATE_X_UNKONW;
				}else{
					if(Touch_State_Shaft_Y(&buffer[1][0],&screen))	screen.state = TOUCH_STATE_Y_UNKONW;
					else{
						screen.state = TOUCH_STATE_PRESS;
					}
				}
			}

			switch(screen.state){
				case TOUCH_STATE_IDLE:
					if(touch_old_change == TOUCH_CHANGE_IDLE){
						touch_change = TOUCH_CHANGE_IDLE;
					}else if(touch_old_change == TOUCH_CHANGE_PUSH){
						touch_change = TOUCH_CHANGE_POP;
					}else if(touch_old_change == TOUCH_CHANGE_POP_WAIT){
						touch_change = TOUCH_CHANGE_POP;
					}else if(touch_old_change == TOUCH_CHANGE_POP){
						touch_change = TOUCH_CHANGE_IDLE_WAIT;
					}
					break;
				case TOUCH_STATE_X_UNKONW:
				case TOUCH_STATE_Y_UNKONW:
					if(touch_old_change == TOUCH_CHANGE_IDLE){
						touch_change = TOUCH_CHANGE_IDLE;
					}else if(touch_old_change == TOUCH_CHANGE_PUSH){
						touch_change = TOUCH_CHANGE_POP_WAIT;
					}else if(touch_old_change == TOUCH_CHANGE_POP_WAIT){
						touch_change = TOUCH_CHANGE_POP_WAIT;
					}else if(touch_old_change == TOUCH_CHANGE_POP){
						touch_change = TOUCH_CHANGE_POP_WAIT;
					}
					break;
				case TOUCH_STATE_PRESS:
					if(touch_old_change == TOUCH_CHANGE_IDLE){
						touch_change = TOUCH_CHANGE_PUSH;
						screen.pressed = TRUE;
					}else if(touch_old_change == TOUCH_CHANGE_PUSH){
						touch_change = TOUCH_CHANGE_PUSH;
					}else if(touch_old_change == TOUCH_CHANGE_POP_WAIT){
						touch_change = TOUCH_CHANGE_PUSH;
					}else if(touch_old_change == TOUCH_CHANGE_POP){
						touch_change = TOUCH_CHANGE_PUSH;
					}
					break;
			}

			if(touch_change != TOUCH_CHANGE_IDLE){
				if(touch_change == TOUCH_CHANGE_PUSH){
					getDisplayPoint(&_display,&screen,&_matrix);
				}

				if(touch_change == TOUCH_CHANGE_IDLE_WAIT){
					touch_change = 	TOUCH_CHANGE_IDLE;
					TS_State.Pressed = 0;
				}else{
					TS_State.Pressed = 1;
				}

				TS_State.x = _display.x;
		  		TS_State.y = _display.y;

				TS_State.Layer = Display.layer;

				if((TS_State.x >= 0 ) && (TS_State.x < LCD_GetXSize()) &&
		     		(TS_State.y >= 0 ) && (TS_State.y < LCD_GetYSize())){
		    		GUI_TOUCH_StoreStateEx(&TS_State);
		  		}
			}

			touch_old_change = touch_change;
			state = TOUCH_IDLE;
			break;
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

