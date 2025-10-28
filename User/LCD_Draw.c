/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file   	 LCD_Draw.c
  * @author 	 Firmware Team
  ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
//#define _USE_SHOW_CRETEM_LOGO
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
int _aRefX[NUM_CALIB_POINTS];
int _aRefY[NUM_CALIB_POINTS];
int _aSamX[NUM_CALIB_POINTS];
int _aSamY[NUM_CALIB_POINTS];

WM_HWIN _hDialogKeypad[2];			//2018.11.08   seo

Editor_module Editor;
Display_module Display;
Button_Module button_status;

const GUI_WIDGET_CREATE_INFO _aFrameWinKey[] = {
   { WINDOW_CreateIndirect	,""		,Main_window		,0			,0		,480	,272},
   { BUTTON_CreateIndirect	,""		,BUTTON_OPEN		,25			,160	,203	,70	},
   { BUTTON_CreateIndirect	,""		,BUTTON_CLOSE		,255		,160	,203	,70	},
   { BUTTON_CreateIndirect	,""		,BUTTON_YES			,25			,160	,203	,70	},
   { BUTTON_CreateIndirect	,""		,BUTTON_NO			,255		,160	,203	,70	},
   { TEXT_CreateIndirect	,"" 	,Text_Encoder		,5			,250	,50		,30	,	TEXT_CF_LEFT },   //2018.11.08   seo
   { TEXT_CreateIndirect	,"" 	,Text_ElapsedTime 	,130		,35		,50		,30	,	TEXT_CF_LEFT },   //019.10.24 -LMI-
   { TEXT_CreateIndirect	,"" 	,TEXT_CW 	,140	,250		,50		,30	,	TEXT_CF_LEFT },   //019.10.24 -LMI-
   { TEXT_CreateIndirect	,"" 	,TEXT_CCW 	,185	,250		,50		,30	,	TEXT_CF_LEFT },   //019.10.24 -LMI-

#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
   { TEXT_CreateIndirect	,"" 	,TEXT_VERSION		,100		,255	,70		,30	,	TEXT_CF_LEFT },   //2018.11.08   seo
#else
   { TEXT_CreateIndirect	,"" 	,TEXT_VERSION		,29			,255	,120	,30	,	TEXT_CF_LEFT },   //2018.11.08   seo
#endif

   { IMAGE_CreateIndirect	,""		,IMAGE_CRETEM_LOGO	,29			,242	,65		,22,	IMAGE_CF_MEMDEV},
   { BUTTON_CreateIndirect	,""		,BUTTON_CALIBRATION	,277		,175	,70		,40},

   { BUTTON_CreateIndirect	,""		,Keypad_NUM_1	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_NUM_2	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_NUM_3	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,OPTION_EXIT 	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_XSIZE,	KEYPAD_YSIZE},

   { BUTTON_CreateIndirect	,""		,Keypad_NUM_4	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_NUM_5	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_NUM_6	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,OPTION_OPEN	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_XSIZE,	KEYPAD_YSIZE},

   { BUTTON_CreateIndirect	,""		,Keypad_NUM_7	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_NUM_8	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_NUM_9	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,OPTION_CLOSE	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_XSIZE,	KEYPAD_YSIZE},

   { BUTTON_CreateIndirect	,""		,Keypad_CLR		,KEYPAD_START_X_POINT+KEYPAD_XSIZE*0+BUTTON_INTERVAL*0	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_NUM_0	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*1+BUTTON_INTERVAL*1	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,Keypad_DEL		,KEYPAD_START_X_POINT+KEYPAD_XSIZE*2+BUTTON_INTERVAL*2	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_XSIZE,	KEYPAD_YSIZE},
   { BUTTON_CreateIndirect	,""		,OPTION_INIT	,KEYPAD_START_X_POINT+KEYPAD_XSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*3+BUTTON_INTERVAL*3	,KEYPAD_XSIZE,	KEYPAD_YSIZE},

   { EDIT_CreateIndirect	,""		,EDIT_DRAWER_NUM,17		,KEYPAD_START_Y_POINT+KEYPAD_YSIZE*1+BUTTON_INTERVAL*1		,185		,KEYPAD_YSIZE   },
   { BUTTON_CreateIndirect	,""		,OPTION_SAVE	,17		,145	,FUNCTION_BUTTON_XSIZE   ,FUNCTION_BUTTON_YSIZE},
   { BUTTON_CreateIndirect	,""		,OPTION_MOVE	,125	,145	,FUNCTION_BUTTON_XSIZE   ,FUNCTION_BUTTON_YSIZE},

   { TEXT_CreateIndirect	,""		,TEXT_OPEN		,55		,250	,50		,50		,TEXT_CF_LEFT },   //2018.11.08   seo
   { TEXT_CreateIndirect	,""		,TEXT_CLOSE		,105	,250	,50		,50		,TEXT_CF_LEFT },   //2018.11.08   seo
   { TEXT_CreateIndirect	,""		,TEXT_ORIGIN	,155	,250	,50		,50		,TEXT_CF_LEFT },   //2018.11.08   seo
   { TEXT_CreateIndirect	,""		,TEXT_ACC		,80		,50		,120	,20		,TEXT_CF_RIGHT },

   { BUTTON_CreateIndirect	,""		,BUTTON_INIT	,192	,47		,95		,95},
   { BUTTON_CreateIndirect	,""		,BUTTON_HIDDEN	,0		,0		,80		,70},
};

/* Private functions ---------------------------------------------------------*/

static BUTTON_SKINFLEX_PROPS _Keypad_Num[] = {
// BUTTON_SKINFLEX_PI_PRESSED
  {
    {KEYPAD_NUM_OUTLINE1, KEYPAD_NUM_OUTLINE2, KEYPAD_NUM_OUTLINE3},
    {KEYPAD_NUM_UPPER_UPPER, KEYPAD_NUM_UPPER_LOWER },
    {KEYPAD_NUM_LOWER_UPPER, KEYPAD_NUM_LOWER_LOWER },
     KEYPAD_NUM_RADIOUS
  },
// BUTTON_SKINFLEX_PI_FOCUSSED
  {
    {KEYPAD_NUM_OUTLINE1, KEYPAD_NUM_OUTLINE2, KEYPAD_NUM_OUTLINE3},
    {KEYPAD_NUM_UPPER_UPPER, KEYPAD_NUM_UPPER_LOWER },
    {KEYPAD_NUM_LOWER_UPPER, KEYPAD_NUM_LOWER_LOWER },
     KEYPAD_NUM_RADIOUS
  },
// BUTTON_SKINFLEX_PI_ENABLED
  {
    {KEYPAD_NUM_OUTLINE1, KEYPAD_NUM_OUTLINE2, KEYPAD_NUM_OUTLINE3},
    {KEYPAD_NUM_UPPER_UPPER, KEYPAD_NUM_UPPER_LOWER },
    {KEYPAD_NUM_LOWER_UPPER, KEYPAD_NUM_LOWER_LOWER },
     KEYPAD_NUM_RADIOUS
  },
// BUTTON_SKINFLEX_PI_DISABLED
  {
    {0, 0, 0},
    {0, 0 },
    {0, 0 },
     KEYPAD_NUM_RADIOUS
  },
};

static BUTTON_SKINFLEX_PROPS _Keypad_Option[] = {
// BUTTON_SKINFLEX_PI_PRESSED
  {
    {KEYPAD_OPTION_OUTLINE1, KEYPAD_OPTION_OUTLINE2, KEYPAD_OPTION_OUTLINE3},
    {KEYPAD_OPTION_UPPER_UPPER, KEYPAD_OPTION_UPPER_LOWER },
    {KEYPAD_OPTION_LOWER_UPPER, KEYPAD_OPTION_LOWER_LOWER },
     KEYPAD_OPTION_RADIOUS
  },
// BUTTON_SKINFLEX_PI_FOCUSSED
  {
    {KEYPAD_OPTION_OUTLINE1, KEYPAD_OPTION_OUTLINE2, KEYPAD_OPTION_OUTLINE3},
    {KEYPAD_OPTION_UPPER_UPPER, KEYPAD_OPTION_UPPER_LOWER },
    {KEYPAD_OPTION_LOWER_UPPER, KEYPAD_OPTION_LOWER_LOWER },
     KEYPAD_OPTION_RADIOUS
  },
// BUTTON_SKINFLEX_PI_ENABLED
  {
    {KEYPAD_OPTION_OUTLINE1, KEYPAD_OPTION_OUTLINE2, KEYPAD_OPTION_OUTLINE3},
    {KEYPAD_OPTION_UPPER_UPPER, KEYPAD_OPTION_UPPER_LOWER },
    {KEYPAD_OPTION_LOWER_UPPER, KEYPAD_OPTION_LOWER_LOWER },
     KEYPAD_OPTION_RADIOUS
  },
// BUTTON_SKINFLEX_PI_DISABLED
  {
    {0, 0, 0},
    {0, 0 },
    {0, 0 },
     KEYPAD_OPTION_RADIOUS
  },
};

void Hide_ALL(BYTE layer){
	WM_HideWindow(Editor.Close[layer]);
	WM_HideWindow(Editor.Open[layer]);
	WM_HideWindow(Editor.Yes[layer]);
	WM_HideWindow(Editor.No[layer]);
	WM_HideWindow(Editor.Image_Cretem[layer]);

	WM_HideWindow(Editor.Init[layer]);
	WM_HideWindow(Editor.Encoder_Save[layer]);
	WM_HideWindow(Editor.Encoder_Move[layer]);      //2018.11.08   seo
	WM_HideWindow(Editor.EDIT_DRAWER[layer]);      //2018.11.08   seo
	WM_HideWindow(Editor.TEXT_Encoder[layer]);      //2018.11.08   seo
	WM_HideWindow(Editor.TEXT_Version[layer]);
	WM_HideWindow(Editor.TEXT_Acc[layer]);
	WM_HideWindow(Editor.TEXT_ElapsedTime[layer]);		//2019.10.25 -LMI-
	WM_HideWindow(Editor.display_cw[layer]);		//2019.10.25 -LMI-
	WM_HideWindow(Editor.display_ccw[layer]);		//2019.10.25 -LMI-

	for(BYTE i=0;i<10;i++){
		WM_HideWindow(Editor.Keypad[layer][i]);
	}
	WM_HideWindow(Editor.Key_CLR[layer]);
	WM_HideWindow(Editor.Key_DEL[layer]);
	WM_HideWindow(Editor.Key_EXIT[layer]);
	WM_HideWindow(Editor.Option_Open[layer]);
	WM_HideWindow(Editor.Option_Close[layer]);
	WM_HideWindow(Editor.Option_Init[layer]);

	WM_HideWindow(Editor.TEXT_Open[layer]);      //2018.11.08   seo
	WM_HideWindow(Editor.TEXT_Close[layer]);      //2018.11.08   seo
	WM_HideWindow(Editor.TEXT_Origin[layer]);      //2018.11.08   seo

	WM_HideWindow(Editor.Hidden_Button[layer]);
	WM_HideWindow(Editor.Calibration[layer]);
}

void Show_Main(BYTE layer){
	WM_ShowWindow(Editor.Close[layer]);
	WM_ShowWindow(Editor.Open[layer]);

	WM_ShowWindow(Editor.TEXT_Encoder[layer]);		//2018.11.08   seo
	//WM_ShowWindow(Editor.TEXT_Version[layer]);
#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
	WM_ShowWindow(Editor.Image_Cretem[layer]);
#endif
}

void Show_Setting(BYTE layer){
	WM_ShowWindow(Editor.Encoder_Save[layer]);
	WM_ShowWindow(Editor.Encoder_Move[layer]);      //2018.11.08   seo
	WM_ShowWindow(Editor.TEXT_Encoder[layer]);      //2018.11.08   seo
	WM_ShowWindow(Editor.EDIT_DRAWER[layer]);      //2018.11.08   seo
	WM_ShowWindow(Editor.TEXT_Acc[layer]);
	WM_ShowWindow(Editor.TEXT_ElapsedTime[layer]);		//2019.10.25 -LMI-
	WM_ShowWindow(Editor.display_cw[layer]);
	WM_ShowWindow(Editor.display_ccw[layer]);

	for(BYTE i=0;i<10;i++){
		WM_ShowWindow(Editor.Keypad[layer][i]);
	}
	WM_ShowWindow(Editor.Key_CLR[layer]);
	WM_ShowWindow(Editor.Key_DEL[layer]);
	WM_ShowWindow(Editor.Key_EXIT[layer]);
	WM_ShowWindow(Editor.Option_Open[layer]);
	WM_ShowWindow(Editor.Option_Close[layer]);
	WM_ShowWindow(Editor.Option_Init[layer]);
}

static int _CustomSkin(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
	int       Id;
	BUTTON_SKINFLEX_PROPS aPropsOld[4];

	switch (pDrawItemInfo->Cmd) {
		case WIDGET_ITEM_DRAW_BACKGROUND:
			Id = WM_GetId(pDrawItemInfo->hWin);
			switch (Id) {
				case Keypad_NUM_1:
				case Keypad_NUM_2:
				case Keypad_NUM_3:
				case Keypad_NUM_4:
				case Keypad_NUM_5:
				case Keypad_NUM_6:
				case Keypad_NUM_7:
				case Keypad_NUM_8:
				case Keypad_NUM_9:
				case Keypad_NUM_0:
					for (BYTE i = 0; i < 4; i++) {
						BUTTON_GetSkinFlexProps(&aPropsOld[i], i);  // Get default properties
						BUTTON_SetSkinFlexProps(&_Keypad_Num[i], i);    // Set new properties
					}
						BUTTON_DrawSkinFlex(pDrawItemInfo);           // Draw button with new properties
					for (BYTE i = 0; i < 4; i++) {
						BUTTON_SetSkinFlexProps(&aPropsOld[i], i);  // Restore old properties to avoid other buttons will be drawn with this properties
					}
					break;
				case Keypad_CLR:
				case Keypad_DEL:
				case OPTION_EXIT:
				case OPTION_OPEN:
				case OPTION_CLOSE:
				case OPTION_INIT:
//				case BUTTON_CALIBRATION:
					for (BYTE i = 0; i < 4; i++) {
						BUTTON_GetSkinFlexProps(&aPropsOld[i], i);  // Get default properties
						BUTTON_SetSkinFlexProps(&_Keypad_Option[i], i);    // Set new properties
					}
						BUTTON_DrawSkinFlex(pDrawItemInfo);           // Draw button with new properties
					for (BYTE i = 0; i < 4; i++) {
						BUTTON_SetSkinFlexProps(&aPropsOld[i], i);  // Restore old properties to avoid other buttons will be drawn with this properties
					}
					break;
			}
			return 0;
		default:
			return BUTTON_DrawSkinFlex(pDrawItemInfo);
	}
}

static void FrequencyRange(WORD *min, WORD *max)
{
	switch(Display.set_speed){
		case ACC_MAX:
		case ACC_SLOW_MAX:
			*max = 10;
			*min = acc_freq_array[Display.set_speed+1]-50;
			break;
		case ACC_SLOW_MIN:
		case ACC_MIN:
			*max = acc_freq_array[Display.set_speed-1]+50;
			*min = 900;
			break;
		case MANUAL_MOVING_SPD:
			*max = 10;
			*min = 900;
			break;
	}
}

void Recieved_Key_Option(WORD key){						//2018.11.08   seo
	WORD temp;
	WORD freq_min, freq_max;

	if(Display.set){
		Display.retry=TRUE;
		Display.retry_key=key;
		return;
	}

	//if(draw_order.order_list.bit.auth_access_token)		return;

	switch(key){
		case TOUCH_STATE_IDLE:
			break;
		case Keypad_NUM_1:
		case Keypad_NUM_2:
		case Keypad_NUM_3:
		case Keypad_NUM_4:
		case Keypad_NUM_5:
		case Keypad_NUM_6:
		case Keypad_NUM_7:
		case Keypad_NUM_8:
		case Keypad_NUM_9:
		case Keypad_NUM_0:
			if(draw_order.order_list.bit.manual_order == true){
				draw_order.order_list.bit.manual_order = false;
				//draw_order.order_list.bit.remote_order = false;
				draw_order.direction = DRAW_DIR_NONE;
				draw_status.status_list.bit.active_lock = false;
				draw_status.status_list.bit.manual = false;
				draw_order.order_list.bit.watchdog = false;
				pwm_status.pwm_list.bit.operation = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
						printf("Manual stop\r\n");
#endif
#endif
			}else{
				if(Display.selected_Num>10)	return;

				Display.selected_Num = (Display.selected_Num*10) + (key%10);
				TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
				EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
			}
			break;
		case Keypad_CLR:
			if(Display.set_speed == SET_IDLE){
				Display.selected_Num = 0;
				TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
				EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
			}else{
				Display.set_speed=SET_IDLE;
				Display.selected_Num=0;
				TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
				EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
				BUTTON_SetText(Editor.Option_Open[Display.layer],"Open");
				BUTTON_SetText(Editor.Option_Close[Display.layer],"Close");
				ACC_Text_Disp();
				draw_order.loop_order = false;
				draw_order.loop_err = false;
				draw_order.loop_step = 0;
			}
			draw_order.order_list.bit.watchdog = false;
			draw_status.status_list.bit.encoder_error = false;
			draw_status.status_list.bit.timeout = false;
			draw_encoder.draw_tacho_ccw = 0;
			draw_encoder.draw_tacho_cw = 0;
			draw_encoder.elapsed_time = 0;
			Disp_ElapsedTime();
			break;
		case Keypad_DEL:
			if(draw_order.order_list.bit.manual_order == true){
				draw_order.order_list.bit.manual_order = false;
				//draw_order.order_list.bit.remote_order = false;
				draw_order.direction = DRAW_DIR_NONE;
				draw_status.status_list.bit.active_lock = false;
				draw_status.status_list.bit.manual = false;
				draw_order.order_list.bit.watchdog = false;
				pwm_status.pwm_list.bit.operation = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
				printf("Manual stop\r\n");
#endif
#endif
			}else{
				Display.selected_Num = Display.selected_Num/10;
				TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
				EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
			}
			break;
		case OPTION_SAVE:
			if(Display.set_speed == SET_IDLE){
				PutEncoder(Display.selected_Num, draw_encoder.draw_my_encoder);
				Display.selected_Num = 0;
				TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
				EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
			}else{
				if(Display.selected_Num > 99)			Display.selected_Num = 99;

				temp = (100-Display.selected_Num)*10;

				if(acc_freq_array[Display.set_speed] != temp){			//when into the keypad
					FrequencyRange(&freq_min,&freq_max);

					if(freq_min <= temp)		temp = freq_min;
					else if(freq_max >= temp)	temp = freq_max;

					acc_freq_array[Display.set_speed] = temp;
					ACC_Val_Write(Display.set_speed);
				}else{
					ACC_Val_Write(Display.set_speed);					//when into the +/-
				}

				Display.set_speed = SET_IDLE;
				Display.selected_Num = 0;
				TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
				EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
				BUTTON_SetText(Editor.Option_Open[Display.layer],"Open");
				BUTTON_SetText(Editor.Option_Close[Display.layer],"Close");
				ACC_Text_Disp();
			}
			break;
		case OPTION_MOVE:		//2018.11.08   seo
			switch(Display.selected_Num){
				case DRAW_PARAM_CLOSE:
					//draw_order.last_direction = draw_order.direction;
					draw_order.order_location = Display.selected_Num;

					if((draw_encoder.draw_my_encoder > 0) && (draw_status.status_list.bit.close_limit == false)){
						DrawerAccRatioProc();
						draw_order.direction = DRAW_DIR_CLOSE;
						draw_order.order_list.bit.remote_order = true;
						draw_status.status_list.bit.active = true;
						draw_status.status_list.bit.manual_lock = true;
						draw_order.move_order = true;
						draw_status.encoder_time = _tick_count;
						draw_status.timeout_time = _tick_count;
						draw_order.order_list.bit.watchdog = true;
					}
					break;
				case DRAW_PARAM_01:
				case DRAW_PARAM_02:
				case DRAW_PARAM_03:
				case DRAW_PARAM_04:
				case DRAW_PARAM_05:
				case DRAW_PARAM_06:
				case DRAW_PARAM_07:
				case DRAW_PARAM_08:
				case DRAW_PARAM_09:
				case DRAW_PARAM_10:
				case DRAW_PARAM_11:
				case DRAW_PARAM_12:
				case DRAW_PARAM_13:
				case DRAW_PARAM_14:
				case DRAW_PARAM_15:
				case DRAW_PARAM_16:
				case DRAW_PARAM_17:
				case DRAW_PARAM_18:
				case DRAW_PARAM_19:
				case DRAW_PARAM_20:
					//draw_order.last_direction = draw_order.direction;
					draw_order.order_location = Display.selected_Num;

					if(draw_encoder.draw_my_encoder < draw_encoder.draw_enc_point[draw_order.order_location]-INTERVAL){
						DrawerAccRatioProc();
						draw_order.direction = DRAW_DIR_OPEN;
						draw_order.order_list.bit.remote_order = true;
						draw_status.status_list.bit.active = true;
					}else if(draw_encoder.draw_my_encoder > draw_encoder.draw_enc_point[draw_order.order_location]+INTERVAL){
						DrawerAccRatioProc();
						draw_order.direction = DRAW_DIR_CLOSE;
						draw_order.order_list.bit.remote_order = true;
						draw_status.status_list.bit.active = true;
					}
					Display.selected_Num = 0;
					TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
					EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("my[%d]order[%d]\r\n",draw_order.my_location,draw_order.order_location);
#endif
#endif
					break;
				case DRAW_PARAM_OPEN:
					draw_status.status_list.bit.active = true;
					draw_order.order_location = DRAW_PARAM_OPEN;
					DrawerAccRatioProc();
					draw_order.direction = DRAW_DIR_OPEN;
					draw_order.order_list.bit.remote_order = true;
					Display.selected_Num = 0;
					TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
					EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
					break;
				default:
					break;
				}
				break;
			case OPTION_OPEN:
				if(Display.set_speed == SET_IDLE){
					//if((draw_status.status_list.bit.manual == true) && (draw_order.direction != DRAW_DIR_NONE)){
					if(draw_order.order_list.bit.manual_order == true){
						draw_order.order_list.bit.stop_order = true;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
						printf("Manual stop\r\n");
#endif
#endif
					}
				}else{
					if(Display.set_speed == ACC_LOOP_TEST){
						draw_order.loop_order = true;
					}else{
						if((acc_freq_array[Display.set_speed] > 10)
							&& (acc_freq_array[Display.set_speed] <= 900)){
							if(Display.selected_Num != (100 - (acc_freq_array[Display.set_speed] / 10))){
								acc_freq_array[Display.set_speed] = (100 - Display.selected_Num) * 10;
							}

							FrequencyRange(&freq_min,&freq_max);

							if(freq_max >= acc_freq_array[Display.set_speed]){
								acc_freq_array[Display.set_speed] = freq_max;
							}else{
								if(freq_min < acc_freq_array[Display.set_speed])	acc_freq_array[Display.set_speed] = freq_min;
								acc_freq_array[Display.set_speed] -= 10;
							}
							Display.selected_Num = (100 - (acc_freq_array[Display.set_speed] / 10));
							TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
						}
					}
				}
				break;
			case OPTION_CLOSE:
				if(Display.set_speed == SET_IDLE){
					if(draw_order.order_list.bit.manual_order == true){
						draw_order.order_list.bit.stop_order = true;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
						printf("Manual stop\r\n");
#endif
#endif
					}
				}else{
					if(Display.set_speed == ACC_LOOP_TEST){
						draw_order.loop_order = false;
						draw_order.loop_err = false;
						draw_order.loop_step = 0;
						draw_status.status_list.bit.encoder_error = false;
						draw_status.status_list.bit.timeout = false;
					}else{
						if((acc_freq_array[Display.set_speed] >= 10)
							&& (acc_freq_array[Display.set_speed] < 900)){
							if(Display.selected_Num != (100 - (acc_freq_array[Display.set_speed] / 10))){
								acc_freq_array[Display.set_speed] = (100 - Display.selected_Num) * 10;
							}

							FrequencyRange(&freq_min,&freq_max);

							if(freq_min <= acc_freq_array[Display.set_speed]){
								acc_freq_array[Display.set_speed] = freq_min;
							}else{
								if(freq_max >= acc_freq_array[Display.set_speed])	acc_freq_array[Display.set_speed] = freq_max;
								acc_freq_array[Display.set_speed] += 10;
							}

							Display.selected_Num = (100 - (acc_freq_array[Display.set_speed] / 10));
							TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
						}
					}
				}
				break;
			case OPTION_INIT:
				if(draw_order.order_list.bit.manual_order == true){
					draw_order.order_list.bit.manual_order = false;
					//draw_order.order_list.bit.remote_order = false;
					draw_order.direction = DRAW_DIR_NONE;
					draw_status.status_list.bit.active_lock = false;
					draw_status.status_list.bit.manual = false;
					draw_order.order_list.bit.watchdog = false;
					pwm_status.pwm_list.bit.operation = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Manual stop\r\n");
#endif
#endif
				}else{
					switch(Display.selected_Num){
						case 90:
							Display.set_speed=SET_IDLE;
							Display.selected_Num=0;
							TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
							BUTTON_SetText(Editor.Option_Open[Display.layer],"Open");
							BUTTON_SetText(Editor.Option_Close[Display.layer],"Close");
							ACC_Text_Disp();
							break;
						case 91:
							Display.set_speed=SET_FREQ_MAX;
							FrequencyRange(&freq_min,&freq_max);

							if(freq_min <= acc_freq_array[Display.set_speed])		 acc_freq_array[Display.set_speed] = freq_min;
							else if(freq_max >= acc_freq_array[Display.set_speed])	 acc_freq_array[Display.set_speed] = freq_max;

							Display.selected_Num = (100 - (acc_freq_array[Display.set_speed] / 10));
							TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
							BUTTON_SetText(Editor.Option_Open[Display.layer],"+1%");
							BUTTON_SetText(Editor.Option_Close[Display.layer],"-1%");
							ACC_Text_Disp();
							break;
						case 92:
							Display.set_speed=SET_FREQ_MIN;
							FrequencyRange(&freq_min,&freq_max);

							if(freq_min <= acc_freq_array[Display.set_speed])		 acc_freq_array[Display.set_speed] = freq_min;
							else if(freq_max >= acc_freq_array[Display.set_speed])	 acc_freq_array[Display.set_speed] = freq_max;

							Display.selected_Num = (100 - (acc_freq_array[Display.set_speed] / 10));
							TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
							BUTTON_SetText(Editor.Option_Open[Display.layer],"+1%");
							BUTTON_SetText(Editor.Option_Close[Display.layer],"-1%");
							ACC_Text_Disp();
							break;
						case 93:
							Display.set_speed=SET_FREQ_SLOW_MAX;
							FrequencyRange(&freq_min,&freq_max);

							if(freq_min <= acc_freq_array[Display.set_speed])		 acc_freq_array[Display.set_speed] = freq_min;
							else if(freq_max >= acc_freq_array[Display.set_speed])	 acc_freq_array[Display.set_speed] = freq_max;

							Display.selected_Num = (100 - (acc_freq_array[Display.set_speed] / 10));
							TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
							BUTTON_SetText(Editor.Option_Open[Display.layer],"+1%");
							BUTTON_SetText(Editor.Option_Close[Display.layer],"-1%");
							ACC_Text_Disp();
							break;
						case 94:
							Display.set_speed=SET_FREQ_SLOW_MIN;
							FrequencyRange(&freq_min,&freq_max);

							if(freq_min <= acc_freq_array[Display.set_speed])		 acc_freq_array[Display.set_speed] = freq_min;
							else if(freq_max >= acc_freq_array[Display.set_speed])	 acc_freq_array[Display.set_speed] = freq_max;

							Display.selected_Num = (100 - (acc_freq_array[Display.set_speed] / 10));
							TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
							BUTTON_SetText(Editor.Option_Open[Display.layer],"+1%");
							BUTTON_SetText(Editor.Option_Close[Display.layer],"-1%");
							ACC_Text_Disp();
							break;
						case 95:
							Display.set_speed=SET_FREQ_MOVING_SPD;
							FrequencyRange(&freq_min,&freq_max);

							if(freq_min <= acc_freq_array[Display.set_speed])		 acc_freq_array[Display.set_speed] = freq_min;
							else if(freq_max >= acc_freq_array[Display.set_speed])	 acc_freq_array[Display.set_speed] = freq_max;

							Display.selected_Num=acc_freq_array[Display.set_speed];
							temp = (100 - (Display.selected_Num / 10));
							TextBox_Input(Display.Text_Encoder_arr,temp);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
							BUTTON_SetText(Editor.Option_Open[Display.layer],"+1%");
							BUTTON_SetText(Editor.Option_Close[Display.layer],"-1%");
							ACC_Text_Disp();
							break;
						case 99:
							Display.set_speed = SET_LOOP_TEST;
							BUTTON_SetText(Editor.Option_Open[Display.layer],"Test");
							BUTTON_SetText(Editor.Option_Close[Display.layer],"Stop");
							temp = 0;
							TextBox_Input(Display.Text_Encoder_arr,temp);
							EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
							break;
						default:
							if(draw_status.status_list.bit.manual_lock == false){
								if(draw_status.status_list.bit.close_limit == false){
									draw_status.status_list.bit.active = false;
									draw_status.status_list.bit.init_cmpl = false;
									draw_order.order_list.bit.init_order = true;
									draw_order.my_location = DRAW_PARAM_UNKNOWN;
									draw_order.order_location = DRAW_PARAM_CLOSE;
									DrawerAccRatioProc();
									draw_order.direction = DRAW_DIR_CLOSE;
									draw_order.order_list.bit.remote_order = true;
									draw_status.status_list.bit.manual = true;
									//pwm_status.pwm_list.bit.slow_section = false;
									//SineAccelerationTable(500, acc_freq_array[ACC_SLOW_MIN], acc_freq_array[ACC_SLOW_MAX]);
#ifdef DEBUG
#ifdef DEBUG_BUTTON
									printf("Init!\r\n");
#endif
#endif
								}
							}
							break;
					}
				}
				break;
			case BUTTON_CALIBRATION:
				Draw_Calibration();
				break;
			case OPTION_EXIT:
				NVIC_SystemReset();
				break;
	}
}

void Touch_Error_Clear(void){
	GUI_PID_STATE State;
	GUI_TOUCH_GetState(&State);

	if((State.Pressed == false) && (draw_order.order_list.bit.manual_order == false) && (draw_order.order_list.bit.remote_order == false)
		&& (draw_order.move_order == false)){
		if(BUTTON_IsPressed(Editor.Close[0])){
			BUTTON_SetPressed(Editor.Close[0],0);
#ifdef DEBUG
#ifdef DEBUG_BUTTON
			printf("==========close button reset \n\r");
#endif
#endif
		}
		if(BUTTON_IsPressed(Editor.Close[1])){
			BUTTON_SetPressed(Editor.Close[1],0);
#ifdef DEBUG
#ifdef DEBUG_BUTTON
			printf("==========close button reset \n\r");
#endif
#endif
		}
		if(BUTTON_IsPressed(Editor.Open[0])){
			BUTTON_SetPressed(Editor.Open[0],0);
#ifdef DEBUG
#ifdef DEBUG_BUTTON
			printf("==========Open button reset \n\r");
#endif
#endif
		}
		if(BUTTON_IsPressed(Editor.Open[1])){
			BUTTON_SetPressed(Editor.Open[1],0);
#ifdef DEBUG
#ifdef DEBUG_BUTTON
			printf("==========Open button reset \n\r");
#endif
#endif
		}
	}
	Display.open_touch[0]=BUTTON_IsPressed(Editor.Open[0]);
	Display.open_touch[1]=BUTTON_IsPressed(Editor.Open[1]);
	Display.close_touch[0]=BUTTON_IsPressed(Editor.Close[0]);
	Display.close_touch[1]=BUTTON_IsPressed(Editor.Close[1]);
}

void Touch_Drag_Proc(void){
	GUI_PID_STATE State;
	GUI_TOUCH_GetState(&State);

	if(Display.step!=DISPLAY_MAIN)	return;

	Touch_Error_Clear();

	if((State.Pressed && draw_order.direction)
		&& !( ((((25)<State.x) && (State.x< (25+203)))	|| (((255)<State.x) && (State.x< (255+203))))
		&& ((160<State.y) && (State.y< (160+70))) )){
			Display.close_touch[0] = false;
			Display.close_touch[1] = false;
			Display.open_touch[0] = false;
			Display.open_touch[1] = false;

			if((draw_order.order_list.bit.manual_order == true) && (draw_order.move_order == false)){
				draw_order.order_list.bit.stop_order = true;
			}

			if((draw_order.order_list.bit.remote_order == true) && (draw_order.move_order == false)){
				//if(button_status.step == CLICK_DOUBLECLICK){
				if(draw_order.order_list.bit.intermediate_stop == false){
					draw_encoder.acc_dec_section = INTERMEDIATE_STOP_VOLUME;
					//SineAccelerationTable(INTERMEDIATE_STOP_VOLUME, ACC_FREQ_MIN + 100, sine_acc_32[pwm_status.reload]);
					SineAccelerationTable(INTERMEDIATE_STOP_VOLUME, acc_freq_array[ACC_MIN] + 100, sine_acc_32[pwm_status.reload]);
					pwm_status.reload = INTERMEDIATE_STOP_VOLUME;
					pwm_status.pwm_list.bit.acceleration = false;
					pwm_status.pwm_list.bit.deceleration = true;
					pwm_status.pwm_list.bit.phase = false;
					TIM7_INT_ENABLE();
					draw_order.order_list.bit.intermediate_stop = true;
					button_status.step = CLICK_STOP_MOVING;
				}
			}
#ifdef DEBUG
#ifdef DEBUG_BUTTON
			printf("touch drag Manual stop\r\n");
#endif
#endif
	}
}

void Recieved_Option_Clicked(WORD key){
	if(Display.set)	return;
	if(Display.set_speed != SET_IDLE) return;
	//if(draw_order.order_list.bit.auth_access_token)		return;
	switch(key){
		case OPTION_OPEN:
			if(draw_status.status_list.bit.open_limit == false){
				if((draw_order.order_list.bit.manual_order == false) && (draw_order.order_list.bit.remote_order == false)){
					draw_order.order_list.bit.remote_order = false;
					draw_order.order_list.bit.manual_order = true;
					draw_status.status_list.bit.manual = true;
					draw_order.direction = DRAW_DIR_OPEN;
					AC_MOTOR_CW();
					pwm_status.pwm_list.bit.operation = true;
					pwm_status.pwm_list.bit.acceleration = false;
					pwm_status.pwm_list.bit.deceleration = false;
					pwm_status.pwm_list.bit.phase = true;
					pwm_status.pwm_list.bit.slow_section = false;
					TIM7_INT_ENABLE();
					draw_status.encoder_time = _tick_count;
					draw_status.timeout_time = _tick_count;
					draw_encoder.elapsed_time = _tick_count;
					draw_order.order_list.bit.watchdog = true;
					//draw_encoder.keep_limit = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Manual open\r\n");
#endif
#endif
				}
			}
			break;
		case OPTION_CLOSE:
			if(draw_status.status_list.bit.close_limit == false){
				if((draw_order.order_list.bit.manual_order == false) && (draw_order.order_list.bit.remote_order == false)){
					draw_order.order_list.bit.remote_order = false;
					draw_order.order_list.bit.manual_order = true;
					draw_status.status_list.bit.manual = true;
					draw_order.direction = DRAW_DIR_CLOSE;
					AC_MOTOR_CCW();
					pwm_status.pwm_list.bit.acceleration = false;
					pwm_status.pwm_list.bit.deceleration = false;
					pwm_status.pwm_list.bit.operation = true;
					pwm_status.pwm_list.bit.phase = true;
					pwm_status.pwm_list.bit.slow_section = false;
					TIM7_INT_ENABLE();
					draw_status.encoder_time = _tick_count;
					draw_status.timeout_time = _tick_count;
					draw_encoder.elapsed_time = _tick_count;
					draw_order.order_list.bit.watchdog = true;
					//draw_encoder.keep_limit = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Manual close\r\n");
#endif
#endif
				}
			}
			break;
	}
}

void Recieved_Key_Clicked(WORD key){
	if(Display.set)	return;
}


void Recieved_Key_Main(WORD key){
	GUI_PID_STATE State;
	GUI_TOUCH_GetState(&State);

	if(Display.set){
		Display.retry=TRUE;
		Display.retry_key=key;
		return;
	}

	if(draw_order.order_list.bit.auth_access_token)		return;

	switch(key){
		case TOUCH_STATE_IDLE:
			break;
		case BUTTON_OPEN:
		case BUTTON_CLOSE:
		if((button_status.step == CLICK_NORMALCLICK) && (draw_order.order_list.bit.manual_order == true)){
			draw_order.order_list.bit.stop_order = true;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
				printf("Manual stop\r\n");
#endif
#endif
		}
		if(button_status.step == CLICK_STOP_START){
			if(draw_order.order_list.bit.remote_order == true){
				draw_encoder.acc_dec_section = INTERMEDIATE_STOP_VOLUME;
				//SineAccelerationTable(INTERMEDIATE_STOP_VOLUME, ACC_FREQ_MIN + 100, sine_acc_32[pwm_status.reload]);
				SineAccelerationTable(INTERMEDIATE_STOP_VOLUME, acc_freq_array[ACC_MIN] + 100, sine_acc_32[pwm_status.reload]);
				pwm_status.reload = INTERMEDIATE_STOP_VOLUME;
				pwm_status.pwm_list.bit.acceleration = false;
				pwm_status.pwm_list.bit.deceleration = true;
				pwm_status.pwm_list.bit.phase = false;
				TIM7_INT_ENABLE();
				draw_order.order_list.bit.intermediate_stop = true;
				button_status.step = CLICK_STOP_MOVING;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
				printf("intermediate stop start!!\r\n");
#endif
#endif
				}else{
					button_status.step = CLICK_IDLE;
				}
			}
			break;
		case BUTTON_YES:
#ifdef DEBUG
#ifdef DEBUG_BUTTON
			printf("Button Yes!!\r\n");
#endif
#endif

			//if(Display.step==DISPLAY_REFILL){	//open command screen
				if(draw_order.order_list.bit.fault_reserve == true){
					draw_order.order_list.bit.fault_reserve = false;
					draw_order.order_list.bit.fault_handling = true;
					if(draw_order.order_list.bit.set_access_token){
						if(draw_order.order_list.bit.auth_access_token){
							return;
						}else{
							ACCESS_TOKEN_DISABLE();
						}
					}
					switch(draw_order.fault_location){
						case DRAW_PARAM_CLOSE:
							draw_order.order_location = draw_order.fault_location;

							if((draw_encoder.draw_my_encoder > 0) && (draw_status.status_list.bit.close_limit == false)){
								DrawerAccRatioProc();
								draw_order.direction = DRAW_DIR_CLOSE;
								draw_order.order_list.bit.remote_order = true;
								draw_status.status_list.bit.active = true;
								draw_status.status_list.bit.manual_lock = true;
								draw_order.move_order = true;
								draw_status.encoder_time = _tick_count;
								draw_status.timeout_time = _tick_count;
								draw_order.order_list.bit.watchdog = true;
							}
							break;
						case DRAW_PARAM_01:
						case DRAW_PARAM_02:
						case DRAW_PARAM_03:
						case DRAW_PARAM_04:
						case DRAW_PARAM_05:
						case DRAW_PARAM_06:
						case DRAW_PARAM_07:
						case DRAW_PARAM_08:
						case DRAW_PARAM_09:
						case DRAW_PARAM_10:
						case DRAW_PARAM_11:
						case DRAW_PARAM_12:
						case DRAW_PARAM_13:
						case DRAW_PARAM_14:
						case DRAW_PARAM_15:
						case DRAW_PARAM_16:
						case DRAW_PARAM_17:
						case DRAW_PARAM_18:
						case DRAW_PARAM_19:
						case DRAW_PARAM_20:

							draw_order.order_location = draw_order.fault_location;

							if(draw_encoder.draw_my_encoder < draw_encoder.draw_enc_point[draw_order.order_location]-INTERVAL){
								DrawerAccRatioProc();
								draw_order.direction = DRAW_DIR_OPEN;
								draw_order.order_list.bit.remote_order = true;
								draw_status.status_list.bit.active = true;
								draw_status.status_list.bit.manual_lock = true;
							}else if(draw_encoder.draw_my_encoder > draw_encoder.draw_enc_point[draw_order.order_location]+INTERVAL){
								DrawerAccRatioProc();
								draw_order.direction = DRAW_DIR_CLOSE;
								draw_order.order_list.bit.remote_order = true;
								draw_status.status_list.bit.active = true;
								draw_status.status_list.bit.manual_lock = true;
							}
							break;
						case DRAW_PARAM_OPEN:
							draw_order.order_location = draw_order.fault_location;
							DrawerAccRatioProc();
							draw_order.direction = DRAW_DIR_OPEN;
							draw_status.status_list.bit.active = true;
							draw_status.status_list.bit.manual_lock = true;
							draw_order.order_list.bit.remote_order = true;
						break;
					}
				}
				Display.dissolve_time = g_wTimerCnt100us;
			//}
			break;
		case BUTTON_NO:
			Display.change_reserve = true;
			break;
		case BUTTON_INIT:
			if(draw_status.status_list.bit.manual_lock == false){
				if(draw_status.status_list.bit.close_limit == false){
					draw_status.status_list.byte[0] &= 0x06;
					draw_status.status_list.byte[1] = false;
					draw_status.status_list.bit.active = false;
					draw_status.status_list.bit.init_cmpl = false;
					draw_order.my_location = DRAW_PARAM_UNKNOWN;
					draw_order.order_location = DRAW_PARAM_CLOSE;
					DrawerAccRatioProc();
					draw_order.direction = DRAW_DIR_CLOSE;
					draw_order.order_list.bit.remote_order = true;
					draw_status.status_list.bit.manual = true;
					//SineAccelerationTable((DEFAULT_TABLE_SIZE * 2), ACC_FREQ_MIN, ACC_FREQ_MAX);
					//SineAccelerationTable((DEFAULT_TABLE_SIZE * 2), acc_freq_array[ACC_MIN], acc_freq_array[ACC_MAX]);
					draw_status.encoder_time = _tick_count;
					draw_status.timeout_time = _tick_count;
					draw_order.order_list.bit.watchdog = true;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Init!\r\n");
#endif
#endif
				}
			}
			break;
		case OPTION_EXIT:
			NVIC_SystemReset();
			break;
	}
}

void Released_key_Retry(void){
	if(Display.retry){
		if(draw_order.order_list.bit.auth_access_token == false){
			if(!Display.set){
				Recieved_Key_Main(Display.retry_key);
				Recieved_Key_Option(Display.retry_key);
				Display.retry=FALSE;
			}
		}else{
			Display.retry = FALSE;
		}
	}
}

void _cbFrameWinKey(WM_MESSAGE * pMsg) {
	const char *Keypad_Arr[] = {"1","2","3","4","5","6","7","8","9","0"};		//2018.11.08   seo
	WORD	NCode;
	WORD	Id;
	GUI_PID_STATE State;
	GUI_RECT Rect;

	switch (pMsg->MsgId) {
		case WM_KEY:
			WM_SendMessage(WM_HBKWIN, pMsg);
			break;

		case WM_INIT_DIALOG:
			Editor.Open[Display.layer]=WM_GetDialogItem(pMsg->hWin, BUTTON_OPEN);
			BUTTON_SetSkin(Editor.Open[Display.layer], _CustomSkin);
			BUTTON_SetBitmap(Editor.Open[Display.layer], BUTTON_BI_UNPRESSED,& bmopen_unpress);
			BUTTON_SetBitmap(Editor.Open[Display.layer], BUTTON_BI_PRESSED,& bmopen_press);
			BUTTON_SetFont(Editor.Open[Display.layer],&GUI_Font32B_ASCII);
			BUTTON_SetTextColor(Editor.Open[Display.layer],BUTTON_BI_UNPRESSED,LEFT_BUTTON_TEXT_UNPRESS);
			BUTTON_SetTextColor(Editor.Open[Display.layer],BUTTON_BI_PRESSED,LEFT_BUTTON_TEXT_PRESS);
			BUTTON_SetText(Editor.Open[Display.layer],"      OPEN");

			Editor.Close[Display.layer]=WM_GetDialogItem(pMsg->hWin, BUTTON_CLOSE);
			BUTTON_SetSkin(Editor.Close[Display.layer], _CustomSkin);
			BUTTON_SetBitmap(Editor.Close[Display.layer], BUTTON_BI_UNPRESSED,& bmclose_unpress);
			BUTTON_SetBitmap(Editor.Close[Display.layer], BUTTON_BI_PRESSED,& bmclose_press);
			BUTTON_SetFont(Editor.Close[Display.layer],&GUI_Font32B_ASCII);
			BUTTON_SetTextColor(Editor.Close[Display.layer],BUTTON_BI_UNPRESSED,RIGHT_BUTTON_TEXT_UNPRESS);
			BUTTON_SetTextColor(Editor.Close[Display.layer],BUTTON_BI_PRESSED,RIGHT_BUTTON_TEXT_PRESS);
			BUTTON_SetText(Editor.Close[Display.layer],"      CLOSE");

			Editor.Yes[Display.layer]=WM_GetDialogItem(pMsg->hWin, BUTTON_YES);
			BUTTON_SetSkin(Editor.Yes[Display.layer], _CustomSkin);
			BUTTON_SetBitmap(Editor.Yes[Display.layer], BUTTON_BI_UNPRESSED,& bmyes_unpress);
			BUTTON_SetBitmap(Editor.Yes[Display.layer], BUTTON_BI_PRESSED,& bmyes_press);
			BUTTON_SetFont(Editor.Yes[Display.layer],&GUI_Font32B_ASCII);
			BUTTON_SetTextColor(Editor.Yes[Display.layer],BUTTON_BI_UNPRESSED,LEFT_BUTTON_TEXT_UNPRESS);
			BUTTON_SetTextColor(Editor.Yes[Display.layer],BUTTON_BI_PRESSED,LEFT_BUTTON_TEXT_PRESS);
			BUTTON_SetText(Editor.Yes[Display.layer],"    YES");

			Editor.No[Display.layer]=WM_GetDialogItem(pMsg->hWin, BUTTON_NO);
			BUTTON_SetSkin(Editor.No[Display.layer], _CustomSkin);
			BUTTON_SetBitmap(Editor.No[Display.layer], BUTTON_BI_UNPRESSED,& bmno_unpress);
			BUTTON_SetBitmap(Editor.No[Display.layer], BUTTON_BI_PRESSED,& bmno_press);
			BUTTON_SetFont(Editor.No[Display.layer],&GUI_Font32B_ASCII);
			BUTTON_SetTextColor(Editor.No[Display.layer],BUTTON_BI_UNPRESSED,RIGHT_BUTTON_TEXT_UNPRESS);
			BUTTON_SetTextColor(Editor.No[Display.layer],BUTTON_BI_PRESSED,RIGHT_BUTTON_TEXT_PRESS);
			BUTTON_SetText(Editor.No[Display.layer],"     NO");

			Editor.Image_Cretem[Display.layer]=WM_GetDialogItem(pMsg->hWin, IMAGE_CRETEM_LOGO);
			IMAGE_SetBitmap(Editor.Image_Cretem[Display.layer],& bmcretem);

			Editor.Init[Display.layer]=WM_GetDialogItem(pMsg->hWin, BUTTON_INIT);
//			BUTTON_SetBitmap(Editor.Init[Display.layer], BUTTON_BI_PRESSED,& bmInit);
//			BUTTON_SetBitmap(Editor.Init[Display.layer], BUTTON_BI_UNPRESSED,& bmInit);
			BUTTON_SetFont(Editor.Init[Display.layer],&GUI_Font24B_ASCII);
			BUTTON_SetText(Editor.Init[Display.layer],"Init");
//			BUTTON_SetTextColor(Editor.Init[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
//			BUTTON_SetTextColor(Editor.Init[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
//			BUTTON_SetSkin(Editor.Init[Display.layer], _CustomSkin);

			Editor.Calibration[Display.layer]=WM_GetDialogItem(pMsg->hWin, BUTTON_CALIBRATION);
			BUTTON_SetFont(Editor.Calibration[Display.layer],&GUI_Font10_ASCII);
			BUTTON_SetTextColor(Editor.Calibration[Display.layer],BUTTON_BI_UNPRESSED,GUI_BLACK);
			BUTTON_SetTextColor(Editor.Calibration[Display.layer],BUTTON_BI_PRESSED,GUI_WHITE);
			BUTTON_SetFont(Editor.Calibration[Display.layer],&GUI_Font16B_ASCII);
			BUTTON_SetTextColor(Editor.Calibration[Display.layer],BUTTON_BI_UNPRESSED,0x0094D6BB);
			BUTTON_SetTextColor(Editor.Calibration[Display.layer],BUTTON_BI_PRESSED,0x007979E2);
			BUTTON_SetText(Editor.Calibration[Display.layer],"Touch\n\rReset");
			BUTTON_SetSkin(Editor.Calibration[Display.layer], _CustomSkin);

			Editor.TEXT_Encoder[Display.layer]=WM_GetDialogItem(pMsg->hWin, Text_Encoder);		//2018.11.08   seo
			TEXT_SetFont(Editor.TEXT_Encoder[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.TEXT_Encoder[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.TEXT_Encoder[Display.layer],"");

			Editor.TEXT_Version[Display.layer]=WM_GetDialogItem(pMsg->hWin, TEXT_VERSION);		//2018.11.08   seo
			TEXT_SetFont(Editor.TEXT_Version[Display.layer],&GUI_Font10_ASCII);
			TEXT_SetTextColor(Editor.TEXT_Version[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.TEXT_Version[Display.layer],DISPLAY_VERSION);

			Editor.TEXT_ElapsedTime[Display.layer]=WM_GetDialogItem(pMsg->hWin, Text_ElapsedTime);		//2018.11.08   seo
			TEXT_SetFont(Editor.TEXT_ElapsedTime[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.TEXT_ElapsedTime[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.TEXT_ElapsedTime[Display.layer],"");

			Editor.display_cw[Display.layer]=WM_GetDialogItem(pMsg->hWin, TEXT_CW);		//2018.11.08   seo
			TEXT_SetFont(Editor.display_cw[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.display_cw[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.display_cw[Display.layer],"");

			Editor.display_ccw[Display.layer]=WM_GetDialogItem(pMsg->hWin, TEXT_CCW);		//2018.11.08   seo
			TEXT_SetFont(Editor.display_ccw[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.display_ccw[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.display_ccw[Display.layer],"");

			Editor.TEXT_Open[Display.layer]=WM_GetDialogItem(pMsg->hWin, TEXT_OPEN);		//2018.11.08   seo
			TEXT_SetFont(Editor.TEXT_Open[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.TEXT_Open[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.TEXT_Open[Display.layer],"O");

			Editor.TEXT_Close[Display.layer]=WM_GetDialogItem(pMsg->hWin, TEXT_CLOSE);		//2018.11.08   seo
			TEXT_SetFont(Editor.TEXT_Close[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.TEXT_Close[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.TEXT_Close[Display.layer],"O");

			Editor.TEXT_Origin[Display.layer]=WM_GetDialogItem(pMsg->hWin, TEXT_ORIGIN);		//2018.11.08   seo
			TEXT_SetFont(Editor.TEXT_Origin[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.TEXT_Origin[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.TEXT_Origin[Display.layer],"O");

			Editor.TEXT_Acc[Display.layer]=WM_GetDialogItem(pMsg->hWin, TEXT_ACC);
			TEXT_SetFont(Editor.TEXT_Acc[Display.layer],&GUI_Font13_ASCII);
			TEXT_SetTextColor(Editor.TEXT_Acc[Display.layer],GUI_WHITE);
			TEXT_SetText(Editor.TEXT_Acc[Display.layer],"");

			for(BYTE i=0;i<10;i++){		//2018.11.08   seo
				Editor.Keypad[Display.layer][i]=WM_GetDialogItem(pMsg->hWin, Keypad_NUM_1+i);
				BUTTON_SetFont(Editor.Keypad[Display.layer][i],&GUI_Font32_ASCII);
				BUTTON_SetText(Editor.Keypad[Display.layer][i],Keypad_Arr[i]);
				BUTTON_SetTextColor(Editor.Keypad[Display.layer][i],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
				BUTTON_SetTextColor(Editor.Keypad[Display.layer][i],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
				BUTTON_SetSkin(Editor.Keypad[Display.layer][i], _CustomSkin);
			}

			Editor.Key_CLR[Display.layer]=WM_GetDialogItem(pMsg->hWin, Keypad_CLR);
			BUTTON_SetFont(Editor.Key_CLR[Display.layer],&GUI_Font24_ASCII);
			BUTTON_SetText(Editor.Key_CLR[Display.layer],"Clr");
			BUTTON_SetTextColor(Editor.Key_CLR[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
			BUTTON_SetTextColor(Editor.Key_CLR[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
			BUTTON_SetSkin(Editor.Key_CLR[Display.layer], _CustomSkin);

			Editor.Key_DEL[Display.layer]=WM_GetDialogItem(pMsg->hWin, Keypad_DEL);
			BUTTON_SetFont(Editor.Key_DEL[Display.layer],&GUI_Font24_ASCII);
			BUTTON_SetText(Editor.Key_DEL[Display.layer],"Del");
			BUTTON_SetTextColor(Editor.Key_DEL[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
			BUTTON_SetTextColor(Editor.Key_DEL[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
			BUTTON_SetSkin(Editor.Key_DEL[Display.layer], _CustomSkin);

			Editor.Key_EXIT[Display.layer]=WM_GetDialogItem(pMsg->hWin, OPTION_EXIT);
			BUTTON_SetFont(Editor.Key_EXIT[Display.layer],&GUI_Font24_ASCII);
			BUTTON_SetText(Editor.Key_EXIT[Display.layer],"EXIT");
			BUTTON_SetTextColor(Editor.Key_EXIT[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
			BUTTON_SetTextColor(Editor.Key_EXIT[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
			BUTTON_SetSkin(Editor.Key_EXIT[Display.layer], _CustomSkin);

			Editor.Option_Init[Display.layer]=WM_GetDialogItem(pMsg->hWin, OPTION_INIT);
			BUTTON_SetFont(Editor.Option_Init[Display.layer],&GUI_Font24_ASCII);
			BUTTON_SetText(Editor.Option_Init[Display.layer],"INIT");
			BUTTON_SetTextColor(Editor.Option_Init[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
			BUTTON_SetTextColor(Editor.Option_Init[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
			BUTTON_SetSkin(Editor.Option_Init[Display.layer], _CustomSkin);

			Editor.Option_Open[Display.layer]=WM_GetDialogItem(pMsg->hWin, OPTION_OPEN);
	        BUTTON_SetFont(Editor.Option_Open[Display.layer],&GUI_Font20_ASCII);
	        BUTTON_SetText(Editor.Option_Open[Display.layer],"Open");
	        BUTTON_SetTextColor(Editor.Option_Open[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
	        BUTTON_SetTextColor(Editor.Option_Open[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
	        BUTTON_SetSkin(Editor.Option_Open[Display.layer], _CustomSkin);

	        Editor.Option_Close[Display.layer]=WM_GetDialogItem(pMsg->hWin, OPTION_CLOSE);
	        BUTTON_SetFont(Editor.Option_Close[Display.layer],&GUI_Font20_ASCII);
	        BUTTON_SetText(Editor.Option_Close[Display.layer],"Close");
	        BUTTON_SetTextColor(Editor.Option_Close[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
	        BUTTON_SetTextColor(Editor.Option_Close[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
	        BUTTON_SetSkin(Editor.Option_Close[Display.layer], _CustomSkin);

			Editor.Encoder_Save[Display.layer]=WM_GetDialogItem(pMsg->hWin, OPTION_SAVE);
			BUTTON_SetFont(Editor.Encoder_Save[Display.layer],&GUI_Font20_ASCII);
			BUTTON_SetBitmap(Editor.Encoder_Save[Display.layer], BUTTON_BI_PRESSED,& bmButton_Circle);
			BUTTON_SetBitmap(Editor.Encoder_Save[Display.layer], BUTTON_BI_UNPRESSED,& bmButton_Circle);
			BUTTON_SetText(Editor.Encoder_Save[Display.layer],"Save");
			BUTTON_SetTextColor(Editor.Encoder_Save[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
			BUTTON_SetTextColor(Editor.Encoder_Save[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
//			BUTTON_SetSkin(Editor.Encoder_Save[Display.layer], _CustomSkin);

			Editor.Encoder_Move[Display.layer]=WM_GetDialogItem(pMsg->hWin, OPTION_MOVE);
			BUTTON_SetFont(Editor.Encoder_Move[Display.layer],&GUI_Font20_ASCII);
			BUTTON_SetBitmap(Editor.Encoder_Move[Display.layer], BUTTON_BI_PRESSED,& bmButton_Circle);
			BUTTON_SetBitmap(Editor.Encoder_Move[Display.layer], BUTTON_BI_UNPRESSED,& bmButton_Circle);
			BUTTON_SetText(Editor.Encoder_Move[Display.layer],"MOVE");
			BUTTON_SetTextColor(Editor.Encoder_Move[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
			BUTTON_SetTextColor(Editor.Encoder_Move[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
//			BUTTON_SetSkin(Editor.Encoder_Move[Display.layer], _CustomSkin);

			Editor.Hidden_Button[Display.layer]=WM_GetDialogItem(pMsg->hWin, BUTTON_HIDDEN);
			BUTTON_SetFont(Editor.Hidden_Button[Display.layer],&GUI_Font24B_ASCII);
			BUTTON_SetText(Editor.Hidden_Button[Display.layer],"");
			BUTTON_SetTextColor(Editor.Hidden_Button[Display.layer],BUTTON_BI_PRESSED,TEXT_PRESS_COLOR);
			BUTTON_SetTextColor(Editor.Hidden_Button[Display.layer],BUTTON_BI_UNPRESSED,TEXT_UNPRESS_COLOR);
			BUTTON_SetSkin(Editor.Hidden_Button[Display.layer], _CustomSkin);

			Editor.EDIT_DRAWER[Display.layer]=WM_GetDialogItem(pMsg->hWin, EDIT_DRAWER_NUM);
			EDIT_SetFont(Editor.EDIT_DRAWER[Display.layer],&GUI_Font32_ASCII);
			EDIT_SetTextAlign(Editor.EDIT_DRAWER[Display.layer],GUI_TA_RIGHT | GUI_TA_VCENTER);
			break;

		case WM_PAINT:
			//WM_DefaultProc(pMsg);
			switch(Display.step){
				case DISPLAY_INTRO:
//					GUI_SetBkColor(BACKGROUND_LOWER);
					GUI_Clear();
					WM_GetClientRect(&Rect);
					GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, BACKGROUND_UPPER, BACKGROUND_LOWER);
					GUI_DrawBitmap(&bmintro,123,33);
					Display.last_time=_tick_count;
					break;
				case DISPLAY_INIT:
					GUI_SetBkColor(GUI_WHITE);
					GUI_Clear();
					WM_GetClientRect(&Rect);
					GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, BACKGROUND_UPPER, BACKGROUND_LOWER);

					GUI_SetFont(&GUI_Font13_ASCII);
					GUI_SetColor(GUI_BLACK);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_DispStringHCenterAt("Touch the Init button",240,180);
					GUI_DispStringHCenterAt("You need to send the draw to the origin for use.",240,210);
					break;

				case DISPLAY_MAIN:
					GUI_SetBkColor(GUI_WHITE);
					GUI_Clear();
					WM_GetClientRect(&Rect);
					draw_order.order_list.bit.display_token = false;

					if(draw_status.status_list.bit.not_closed == false){
						GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, BACKGROUND_UPPER, BACKGROUND_LOWER);
					}else{
						GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, BACKGROUND_FAIL_UPPER, BACKGROUND_FAIL_LOWER);
						GUI_SetColor(GUI_WHITE);
						GUI_SetTextMode(GUI_TM_TRANS);
						GUI_SetFont(&GUI_Font32B_1);
						GUI_DispStringHCenterAt("NOT FULLY CLOSED!",240,90);
					}
					LCD_Number_Display();

					GUI_SetColor(GUI_WHITE);
					if(draw_order.order_list.bit.set_access_token){
						GUI_DrawBitmap(&bmunlock65,405,16);
					}
					if(draw_status.status_list.bit.close_limit){
						GUI_DrawBitmap(&bmclose65,345,16);
					}else{
						GUI_DrawBitmap(&bmopen65,345,16);
					}

					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font13_ASCII);


					break;
				case DISPLAY_MAIN_LOCK:

					GUI_SetBkColor(GUI_WHITE);

					GUI_Clear();
					WM_GetClientRect(&Rect);
					draw_order.order_list.bit.display_token = true;
					GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, BACKGROUND_LOCK_UPPER, BACKGROUND_LOCK_LOWER);
					LCD_Number_Display();

					GUI_SetColor(GUI_WHITE);
					if(draw_order.order_list.bit.set_access_token){
						GUI_DrawBitmap(&bmlock65,405,16);
					}

					if(draw_status.status_list.bit.close_limit){
						GUI_DrawBitmap(&bmclose65,345,16);
					}else{
						GUI_DrawBitmap(&bmopen65,345,16);
					}

					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font13_ASCII);
					break;

				case DISPLAY_SETTING:
					GUI_SetBkColor(BACKGROUND_SETTING);
					GUI_Clear();
					LCD_Number_Display();
					GUI_SetFont(&GUI_Font13_ASCII);
					GUI_SetColor(GUI_WHITE);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_DispStringAt("Enc",5,230);
					GUI_DispStringAt("Open",45,230);
					GUI_DispStringAt("Close",95,230);
					GUI_DispStringAt("CW",140,230);
					GUI_DispStringAt("CCW",180,230);
					GUI_DispStringAt("Elapsed Time",120,20);
					GUI_DispStringAt("(ms)",160,35);
					if(Display.set_speed == SET_IDLE){
						GUI_DispStringAt("Error List : ",20,50);
						if(draw_status.status_list.bit.encoder_error){
							GUI_SetColor(GUI_RED);
							GUI_SetFont(&GUI_Font13B_ASCII);
							GUI_DispStringAt("ENCODER",85,50);
						}else{
							GUI_SetColor(GUI_WHITE);
							GUI_SetFont(&GUI_Font13_ASCII);
							GUI_DispStringAt("ENCODER",85,50);
						}

						if(draw_status.status_list.bit.timeout){
							GUI_SetColor(GUI_RED);
							GUI_SetFont(&GUI_Font13B_ASCII);
							GUI_DispStringAt("TIMEOUT",150,50);
						}else{
							GUI_SetColor(GUI_WHITE);
							GUI_SetFont(&GUI_Font13_ASCII);
							GUI_DispStringAt("TIMEOUT",150,50);
						}
					}
					break;

				case DISPLAY_DISPENSE:
					GUI_SetBkColor(GUI_WHITE);
					GUI_Clear();

					WM_GetClientRect(&Rect);
					if(Display.status_toggle){
						GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, DISPENSE_UPPER, DISPENSE_LOWER);
					}else{
						GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, BACKGROUND_UPPER, BACKGROUND_LOWER);
					}

					GUI_DrawBitmap(&bmdispense,194,127);

					LCD_Number_Display();

					if(draw_order.order_list.bit.set_access_token){
						if(draw_order.order_list.bit.auth_access_token){
							GUI_DrawBitmap(&bmlock65,405,16);
						}else{
							GUI_DrawBitmap(&bmunlock65,405,16);
						}
					}

					if(draw_status.status_list.bit.close_limit){
						GUI_DrawBitmap(&bmclose65,345,16);
					}else{
						GUI_DrawBitmap(&bmopen65,345,16);
					}

					GUI_SetColor(GUI_WHITE);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font32B_ASCII);
					GUI_DispStringHCenterAt("DISPENSING",240,58);

					GUI_SetFont(&GUI_Font13_ASCII);
					//GUI_DispStringAt("Enc",5,230);
					break;
				case DISPLAY_REFILL:
					GUI_SetBkColor(GUI_WHITE);
					GUI_Clear();
					WM_GetClientRect(&Rect);
					if(Display.status_toggle){
						GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, REFILL_UPPER, REFILL_LOWER);
					}else{
						GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, BACKGROUND_UPPER, BACKGROUND_LOWER);
					}
					GUI_DrawBitmap(&bmrefill,191,101);

					LCD_Number_Display();

					if(draw_order.order_list.bit.set_access_token){
						if(draw_order.order_list.bit.auth_access_token){
							GUI_DrawBitmap(&bmlock65,405,16);
						}else{
							GUI_DrawBitmap(&bmunlock65,405,16);
						}
					}

					if(draw_status.status_list.bit.close_limit){
						GUI_DrawBitmap(&bmclose65,345,16);
					}else{
						GUI_DrawBitmap(&bmopen65,345,16);
					}

					GUI_SetColor(GUI_WHITE);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font24B_ASCII);
					GUI_DispStringHCenterAt("Would you like to open the drawer?",235,75);
					//GUI_DispStringHCenterAt("Would you like to",235,43);
					//GUI_DispStringHCenterAt("open the drawer?",235,63);
					GUI_SetFont(&GUI_Font13_ASCII);
					//GUI_DispStringAt("Enc",5,230);
					break;
				case DISPLAY_ERROR:
					GUI_SetBkColor(BACKGROUND_ERROR);
					GUI_Clear();

//					GUI_DrawBitmap(&bmerror,147,43);

					GUI_SetColor(GUI_WHITE);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font13_ASCII);
					//GUI_DispStringAt("Enc",5,230);

					GUI_SetFont(&GUI_Font20B_ASCII);
					GUI_SetColor(GUI_BLACK);
					GUI_DispStringHCenterAt("Errors has occurred in this drawer",240,180);
					GUI_DispStringHCenterAt("Would you like to initialize? ",240,200);
					break;

				case DISPLAY_LOCK:
					GUI_SetBkColor(BACKGROUND_LOCK);
					GUI_Clear();

					GUI_DrawBitmap(&bmlock,147,43);

					LCD_Number_Display();

					GUI_SetColor(GUI_WHITE);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font13_ASCII);
					//GUI_DispStringAt("Enc",5,230);

					break;
				case DISPLAY_OPEN:
					GUI_Clear();
					WM_GetClientRect(&Rect);
					GUI_DrawGradientV(Rect.x0, Rect.x1, Rect.x1, Rect.y1, BACKGROUND_UPPER, BACKGROUND_LOWER);

					GUI_SetColor(GUI_WHITE);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font13_ASCII);
					//GUI_DispStringAt("Enc",5,230);

					GUI_SetFont(&GUI_Font20B_ASCII);
					GUI_SetColor(GUI_BLACK);
					GUI_DispStringHCenterAt("Would you like to open the drawer?",240,100);
					break;
				case DISPLAY_CLOSE:
					GUI_Clear();
					WM_GetClientRect(&Rect);
					GUI_DrawGradientV(Rect.x0, Rect.x1, Rect.x1, Rect.y1, BACKGROUND_UPPER, BACKGROUND_LOWER);

					GUI_SetColor(GUI_WHITE);
					GUI_SetTextMode(GUI_TM_TRANS);
					GUI_SetFont(&GUI_Font13_ASCII);
					//GUI_DispStringAt("Enc",5,230);

					GUI_SetFont(&GUI_Font20B_ASCII);
					GUI_SetColor(GUI_BLACK);
					GUI_DispStringHCenterAt("Would you like to close the drawer?",240,100);
					break;
			}
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			GUI_TOUCH_GetState(&State);
#if 1
			if(State.Pressed && draw_order.direction &&
				(!Display.close_touch[0] && !Display.close_touch[1] && !Display.open_touch[0] && !Display.open_touch[1])){
				return;
			}
#endif
			if(NCode==WM_NOTIFICATION_RELEASED){
#ifdef DEBUG
#ifdef DEBUG_BUTTON
				printf("RELEASED: %d \n\r",Id);
#endif
#endif
				Recieved_Key_Main(Id);
				Recieved_Key_Option(Id);
			}
			if(NCode==WM_NOTIFICATION_CLICKED){
#ifdef DEBUG
#ifdef DEBUG_BUTTON
				printf("CLICKED: %d \n\r",Id);
#endif
#endif
				Recieved_Key_Clicked(Id);
				Recieved_Option_Clicked(Id);
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
  }
}

void Display_Sensor_InOut(void){

	if(Display.step != DISPLAY_SETTING)	return;

	if(draw_status.status_list.bit.open_limit)		WM_ShowWindow(Editor.TEXT_Open[Display.layer]);
	else											WM_HideWindow(Editor.TEXT_Open[Display.layer]);

	if(draw_status.status_list.bit.close_limit)		WM_ShowWindow(Editor.TEXT_Close[Display.layer]);
	else											WM_HideWindow(Editor.TEXT_Close[Display.layer]);

//	if(draw_status.status_list.bit.origin_limit)	WM_ShowWindow(Editor.TEXT_Origin[Display.layer]);
//	else											WM_HideWindow(Editor.TEXT_Origin[Display.layer]);
}

void Draw_Calibration(void){
	Calibration_Enter_Reset_Write();
	Delay_Ms(10);
	NVIC_SystemReset();
}

void Draw_Main(void){
	Display.step=DISPLAY_MAIN;
	LCD_Layer_Change_Set();
	Display.status=DRAWER_STATUS_STOP;
	Hide_ALL(Display.layer);
	Show_Main(Display.layer);
	WM_Paint(_hDialogKeypad[Display.layer]);
	LCD_Layer_Change();
}

void Draw_Mainlock(void){
	Display.step=DISPLAY_MAIN_LOCK;
	LCD_Layer_Change_Set();
	Display.status=DRAWER_STATUS_STOP;
	Hide_ALL(Display.layer);
	Show_Main(Display.layer);
	WM_Paint(_hDialogKeypad[Display.layer]);
	LCD_Layer_Change();
}


void Draw_Init(void){
	Display.step=DISPLAY_INIT;
	LCD_Layer_Change_Set();
	Hide_ALL(Display.layer);
	WM_ShowWindow(Editor.Init[Display.layer]);
	//WM_ShowWindow(Editor.TEXT_Version[Display.layer]);

#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
	WM_ShowWindow(Editor.Image_Cretem[Display.layer]);
#endif

	WM_Paint(_hDialogKeypad[Display.layer]);
	LCD_Layer_Change();
}

void Draw_Dispense(void){
	LCD_Layer_Change_Set();
	Hide_ALL(Display.layer);
	WM_ShowWindow(Editor.TEXT_Encoder[Display.layer]);
	//WM_ShowWindow(Editor.TEXT_Version[Display.layer]);

#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
	WM_ShowWindow(Editor.Image_Cretem[Display.layer]);
#endif

	WM_Paint(_hDialogKeypad[Display.layer]);
	LCD_Layer_Change();
}

void Draw_Refill(void){
	GUI_PID_STATE State;
	GUI_TOUCH_GetState(&State);

	LCD_Layer_Change_Set();

	Hide_ALL(Display.layer);

	if(State.Pressed == false){
		BUTTON_SetPressed(Editor.Yes[0],0);
		BUTTON_SetPressed(Editor.Yes[1],0);
		BUTTON_SetPressed(Editor.No[0],0);
		BUTTON_SetPressed(Editor.No[1],0);
	}else{
		if(BUTTON_IsPressed(Editor.Yes[0]) || BUTTON_IsPressed(Editor.Yes[1])){
			BUTTON_SetPressed(Editor.Yes[0],1);
			BUTTON_SetPressed(Editor.Yes[1],1);
		}

		if(BUTTON_IsPressed(Editor.No[0]) || BUTTON_IsPressed(Editor.No[1])){
			BUTTON_SetPressed(Editor.No[0],1);
			BUTTON_SetPressed(Editor.No[1],1);
		}
	}

	//WM_ShowWindow(Editor.TEXT_Version[Display.layer]);
	WM_ShowWindow(Editor.Yes[Display.layer]);
	WM_ShowWindow(Editor.No[Display.layer]);

	WM_Paint(_hDialogKeypad[Display.layer]);
#if 0
	WM_ShowWindow(Editor.TEXT_Version[Display.layer^1]);
	WM_ShowWindow(Editor.Yes[Display.layer^1]);
	WM_ShowWindow(Editor.No[Display.layer^1]);

	WM_Paint(_hDialogKeypad[Display.layer^1]);
#endif
	LCD_Layer_Change2();
}

void Draw_Order_Move(void){
	LCD_Layer_Change_Set();
	Hide_ALL(Display.layer);
	WM_ShowWindow(Editor.TEXT_Encoder[Display.layer]);
	//WM_ShowWindow(Editor.TEXT_Version[Display.layer]);

#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
	WM_ShowWindow(Editor.Image_Cretem[Display.layer]);
#endif

	WM_ShowWindow(Editor.Yes[Display.layer]);
	WM_ShowWindow(Editor.No[Display.layer]);
	WM_Paint(_hDialogKeypad[Display.layer]);
	LCD_Layer_Change();
}

void Draw_Error(void){
	LCD_Layer_Change_Set();
	Hide_ALL(Display.layer);
	WM_ShowWindow(Editor.Init[Display.layer]);
	//WM_ShowWindow(Editor.TEXT_Version[Display.layer]);

#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
	WM_ShowWindow(Editor.Image_Cretem[Display.layer]);
#endif

	WM_Paint(_hDialogKeypad[Display.layer]);
	LCD_Layer_Change();
	Hide_ALL(Display.layer^1);
	WM_ShowWindow(Editor.Init[Display.layer^1]);
	//WM_ShowWindow(Editor.TEXT_Version[Display.layer^1]);

#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
	WM_ShowWindow(Editor.Image_Cretem[Display.layer^1]);
#endif

	WM_Paint(_hDialogKeypad[Display.layer^1]);
}

void Draw_Lock(void){
	LCD_Layer_Change_Set();
	Hide_ALL(Display.layer);
	WM_ShowWindow(Editor.TEXT_Encoder[Display.layer]);
	//WM_ShowWindow(Editor.TEXT_Version[Display.layer]);

#ifdef _USE_SHOW_CRETEM_LOGO	//2019.06.18	nexus
	WM_ShowWindow(Editor.Image_Cretem[Display.layer]);
#endif

	WM_Paint(_hDialogKeypad[Display.layer]);
	LCD_Layer_Change();
}

void LCD_Number_Display(void){
	GUI_SetFont(&GUI_Font13B_ASCII);
//	GUI_SetColor(BACKGROUND_LOWER);
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_TRANS);
	if(Display.step == DISPLAY_SETTING){
		GUI_DispStringAt("Draw",25,20);
		GUI_DispStringAt("Num.",25,30);
		GUI_SetFont(&GUI_FontD24x32);
		GUI_DispDecAt (my_address.B.low&0x0f, 53,10,1);
	}else{
		GUI_SetFont(&GUI_FontD36x48);
		GUI_DispDecAt (my_address.B.low&0x0f, 45,22,1);
	}
}

void LCD_Display_Switch(void){
	//static BYTE s_bLast = 0x00;

	switch(Display.step){
		case DISPLAY_INTRO:
			if(GetElapsedTickCount(Display.last_time)>2000){
				Low_Calibration_Val_Read();

				if((_aSamX[4] == 0xffff) && (_aSamX[4] == 0xffff)){
					Draw_Calibration();
				}else{
					if(draw_order.order_list.bit.set_access_token){
						if(IS_AUTHORIZING_ACCESS_TOKEN()){
							draw_order.order_list.bit.auth_access_token = true;
							Draw_Mainlock();
						}else{
							Draw_Main();
						}
					}else{
						Draw_Main();
					}
				}
			}
			break;
		case DISPLAY_INIT:
			if(Display.pre_step==DISPLAY_INTRO){
				if(draw_status.status_list.bit.init_cmpl){
					Draw_Main();
				}
			}else{
				if(Display.pre_step==DISPLAY_INIT){
					if(draw_status.status_list.bit.init_cmpl){
						Draw_Main();
					}
				}else{
					Draw_Init();
				}
			}
			break;

		case DISPLAY_MAIN:
			if(Display.pre_step==DISPLAY_MAIN || Display.pre_step==DISPLAY_INTRO || Display.pre_step==DISPLAY_INIT)	return;
			Draw_Main();
			break;
		case DISPLAY_MAIN_LOCK:
			if(Display.pre_step==DISPLAY_MAIN_LOCK)	return;
			Draw_Mainlock();
			break;
		case DISPLAY_DISPENSE:
			if(GetElapsedTickCount(Display.last_time)>200){
				Display.status_toggle^=1;
				Draw_Dispense();
				Display.last_time=_tick_count;
			}
			break;
		case DISPLAY_REFILL:
			if(GetElapsedTickCount(Display.last_time)>300){
				Display.status_toggle^=1;
				if(Display.change_reserve){
					Display.change_reserve = false;
					Draw_Main();
				}else{
					Draw_Refill();
				}
				Display.last_time=_tick_count;
			}
			break;
		case DISPLAY_ERROR:
			if(Display.pre_step==DISPLAY_ERROR)	return;
			Draw_Error();
			break;
		case DISPLAY_LOCK:
			if(Display.pre_step==DISPLAY_LOCK)	return;
			Draw_Lock();
			break;
		case DISPLAY_OPEN:
			if(Display.pre_step==DISPLAY_OPEN)	return;
			Draw_Order_Move();
			break;
		case DISPLAY_CLOSE:
			if(Display.pre_step==DISPLAY_CLOSE)	return;
			Draw_Order_Move();
			break;
		case DISPLAY_SETTING:
			break;
	}
	Display.pre_step=Display.step;
}

void Enter_Setting_Mode(void){
	static BYTE step=0;
	static WORD last_time;

	Display.setting_touch[0]=BUTTON_IsPressed(Editor.Hidden_Button[0]);
	Display.setting_touch[1]=BUTTON_IsPressed(Editor.Hidden_Button[1]);

	switch(step){
		case 0:
			if(Display.setting_touch[0] || Display.setting_touch[1]){
				last_time=_tick_count;
				step=1;
			}
			break;
		case 1:
			if(Display.setting_touch[0] || Display.setting_touch[1]){
				if(GetElapsedTickCount(last_time)>1000){
					//printf("call setting\n\r");
					//Low_Calibration_Val_Read();
					Display.step=DISPLAY_SETTING;
					LCD_Layer_Change_Set();
					Hide_ALL(Display.layer);
					Show_Setting(Display.layer);
					Display.selected_Num=0;
					TextBox_Input(Display.Text_Encoder_arr,Display.selected_Num);
					EDIT_SetText(Editor.EDIT_DRAWER[Display.layer],(const char *)Display.Text_Encoder_arr);
					WM_Paint(_hDialogKeypad[Display.layer]);

					LCD_Layer_Change();
					step=2;
				}
			}else{
				step=0;
			}
			break;
		case 2:
			break;
	}
}

void LCD_Layer_Change_Set(void){
	Display.set=TRUE;
	Display.layer^=1;
	GUI_SelectLayer(Display.layer);
}

void LCD_Layer_Change(void){
	if(Display.layer){
		for(BYTE k=0xff;k>0x00;k--){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(10);
		}
	}else{
		for(BYTE k=0x00;k<0xff;k++){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(10);
		}
	}
	Display.set=FALSE;
}

void LCD_Layer_Change2(void){
	if(Display.layer){
		for(BYTE k=0xff;k>0x00;k--){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(3);
		}
	}else{
		for(BYTE k=0x00;k<0xff;k++){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(3);
		}
	}
	Display.set=FALSE;
}

void Low_Calibration_Val_Write(void){
	BYTE write_SamX[NUM_LOW_CAL_POINTS * 2];
	BYTE write_SamY[NUM_LOW_CAL_POINTS * 2];

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		write_SamX[i*2]=(_screen_sample[i].x>>8)&0xff;
		write_SamX[i*2+1]=_screen_sample[i].x&0xff;

		write_SamY[i*2]=(_screen_sample[i].y>>8)&0xff;
		write_SamY[i*2+1]=_screen_sample[i].y&0xff;
#ifdef DEBUG
#ifdef DEBUG_TOUCH
		printf("EEP WRITE[%d] : %d|%d\r\n",i,_screen_sample[i].x,_screen_sample[i].y);
#endif
#endif
	}

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		EEP_SPI_WriteBuffer(&write_SamX[i * 2],ADDR_TOUCH_CALIBRATION_X + (i * 2),2);
		Delay_Ms(10);
		EEP_SPI_WriteBuffer(&write_SamY[i * 2],ADDR_TOUCH_CALIBRATION_Y + (i * 2),2);
		Delay_Ms(10);
	}

}

void Low_Calibration_Backup_Val_Read(void){
	BYTE read_SamX[NUM_LOW_CAL_POINTS * 2];
	BYTE read_SamY[NUM_LOW_CAL_POINTS * 2];

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		EEP_SPI_ReadBuffer(&read_SamX[i * 2],ADDR_TOUCH_CALIBRATION_X + (i * 2),2);
		Delay_Ms(10);
		EEP_SPI_ReadBuffer(&read_SamY[i * 2],ADDR_TOUCH_CALIBRATION_Y + (i * 2),2);
		Delay_Ms(10);
	}

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		_screen_sample[i].x=read_SamX[i*2]<<8;
		_screen_sample[i].x|=read_SamX[i*2+1];

		_screen_sample[i].y=read_SamY[i*2]<<8;
		_screen_sample[i].y|=read_SamY[i*2+1];
#ifdef DEBUG
#ifdef DEBUG_TOUCH
		printf("EEP READ[%d] : %d|%d\r\n",i,_screen_sample[i].x,_screen_sample[i].y);
#endif
#endif
	}
	setCalibrationMatrix(&_display_sample[0],&_screen_sample[0],&_matrix);
}

void Low_Calibration_Backup_Val_Write(void){
	BYTE write_SamX[NUM_LOW_CAL_POINTS * 2];
	BYTE write_SamY[NUM_LOW_CAL_POINTS * 2];

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		write_SamX[i*2]=(_screen_sample[i].x>>8)&0xff;
		write_SamX[i*2+1]=_screen_sample[i].x&0xff;

		write_SamY[i*2]=(_screen_sample[i].y>>8)&0xff;
		write_SamY[i*2+1]=_screen_sample[i].y&0xff;
#ifdef DEBUG
#ifdef DEBUG_TOUCH
		printf("EEP WRITE[%d] : %d|%d\r\n",i,_screen_sample[i].x,_screen_sample[i].y);
#endif
#endif
	}

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		EEP_SPI_WriteBuffer(&write_SamX[i * 2],ADDR_TOUCH_CALIBRATION_X + (i * 2),2);
		Delay_Ms(10);
		EEP_SPI_WriteBuffer(&write_SamY[i * 2],ADDR_TOUCH_CALIBRATION_Y + (i * 2),2);
		Delay_Ms(10);
	}

}

void Low_Calibration_Val_Read(void){
	BYTE read_SamX[NUM_LOW_CAL_POINTS * 2];
	BYTE read_SamY[NUM_LOW_CAL_POINTS * 2];

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		EEP_SPI_ReadBuffer(&read_SamX[i * 2],ADDR_TOUCH_CALIBRATION_X + (i * 2),2);
		Delay_Ms(10);
		EEP_SPI_ReadBuffer(&read_SamY[i * 2],ADDR_TOUCH_CALIBRATION_Y + (i * 2),2);
		Delay_Ms(10);
	}

	for(BYTE i=0;i<NUM_LOW_CAL_POINTS;i++){
		_screen_sample[i].x=read_SamX[i*2]<<8;
		_screen_sample[i].x|=read_SamX[i*2+1];

		_screen_sample[i].y=read_SamY[i*2]<<8;
		_screen_sample[i].y|=read_SamY[i*2+1];
#ifdef DEBUG
#ifdef DEBUG_TOUCH
		printf("EEP READ[%d] : %d|%d\r\n",i,_screen_sample[i].x,_screen_sample[i].y);
#endif
#endif
	}
	setCalibrationMatrix(&_display_sample[0],&_screen_sample[0],&_matrix);
}

void ACC_Val_Write(WORD acc_speed){
	BYTE value[2];

	value[0]=(acc_freq_array[acc_speed]>>8)&0xff;
	value[1]=acc_freq_array[acc_speed]&0xff;

	switch(acc_speed){
		case SET_FREQ_MAX:
			EEP_SPI_WriteBuffer(value,ADDR_FREQ_MAX,2);
			break;
		case SET_FREQ_MIN:
			EEP_SPI_WriteBuffer(value,ADDR_FREQ_MIN,2);
			break;
		case SET_FREQ_SLOW_MAX:
			EEP_SPI_WriteBuffer(value,ADDR_FREQ_SLOW_MAX,2);
			break;
		case SET_FREQ_SLOW_MIN:
			EEP_SPI_WriteBuffer(value,ADDR_FREQ_SLOW_MIX,2);
			break;
		case SET_FREQ_MOVING_SPD:
			EEP_SPI_WriteBuffer(value,ADDR_FREQ_MOVING_SPD,2);
			break;
	}
}

void ACC_Val_Read(WORD acc_speed){
	BYTE value[2];

	switch(acc_speed){
		case SET_FREQ_MAX:
			EEP_SPI_ReadBuffer(value,ADDR_FREQ_MAX,2);
			break;
		case SET_FREQ_MIN:
			EEP_SPI_ReadBuffer(value,ADDR_FREQ_MIN,2);
			break;
		case SET_FREQ_SLOW_MAX:
			EEP_SPI_ReadBuffer(value,ADDR_FREQ_SLOW_MAX,2);
			break;
		case SET_FREQ_SLOW_MIN:
			EEP_SPI_ReadBuffer(value,ADDR_FREQ_SLOW_MIX,2);
			break;
		case SET_FREQ_MOVING_SPD:
			EEP_SPI_ReadBuffer(value,ADDR_FREQ_MOVING_SPD,2);
			break;
	}
	acc_freq_array[acc_speed]=value[0]<<8;
	acc_freq_array[acc_speed]|=value[1];

	if((acc_freq_array[acc_speed]==0xffff) || (acc_freq_array[acc_speed] > 1000) || (acc_freq_array[acc_speed] < 10)){
		switch(acc_speed){
			case SET_FREQ_MAX:
				acc_freq_array[acc_speed]=ACC_FREQ_MAX;
				ACC_Val_Write(acc_speed);
				break;
			case SET_FREQ_MIN:
				acc_freq_array[acc_speed]=ACC_FREQ_MIN;
				ACC_Val_Write(acc_speed);
				break;
			case SET_FREQ_SLOW_MAX:
				acc_freq_array[acc_speed]=ACC_FREQ_SLOW_MAX;
				ACC_Val_Write(acc_speed);
				break;
			case SET_FREQ_SLOW_MIN:
				acc_freq_array[acc_speed]=ACC_FREQ_SLOW_MIN;
				ACC_Val_Write(acc_speed);
				break;
			case SET_FREQ_MOVING_SPD:
				acc_freq_array[acc_speed]=_FREQ_MOVING_SPD;
				ACC_Val_Write(acc_speed);
				break;
		}
	}
}

void Calibration_Enter_Reset_Write(void){
	BYTE write_byte = EEP_TOUCH_CALIBRATION_nMAGIC_CODE;

	EEP_SPI_WriteBuffer(&write_byte,EEP_ADDR_TOUCH_CALIBRATION_EXEC,1);
}

void Calibration_Enter_Write(void){
	BYTE write_byte = EEP_TOUCH_CALIBRATION_MAGIC_CODE;

	EEP_SPI_WriteBuffer(&write_byte,EEP_ADDR_TOUCH_CALIBRATION_EXEC,1);
}

BYTE Calibration_Enter_Read(void){
	BYTE read_byte = 0x00;

	EEP_SPI_ReadBuffer(&read_byte,EEP_ADDR_TOUCH_CALIBRATION_EXEC,1);

	return read_byte;
}

void ACC_Text_Disp(void){
	switch(Display.set_speed){
		case SET_FREQ_MAX:
			TEXT_SetText(Editor.TEXT_Acc[Display.layer],"SPEED MAX (%)");
			break;
		case SET_FREQ_MIN:
			TEXT_SetText(Editor.TEXT_Acc[Display.layer],"SPEED MIN (%)");
			break;
		case SET_FREQ_SLOW_MAX:
			TEXT_SetText(Editor.TEXT_Acc[Display.layer],"SPEED SLOW MAX (%)");
			break;
		case SET_FREQ_SLOW_MIN:
			TEXT_SetText(Editor.TEXT_Acc[Display.layer],"SPEED SLOW MIN (%)");
			break;
		case SET_FREQ_MOVING_SPD:
			TEXT_SetText(Editor.TEXT_Acc[Display.layer],"MANUAL SPEED (%)");
			break;
		case SET_IDLE:
			TEXT_SetText(Editor.TEXT_Acc[Display.layer],"");
			break;
	}
}

#if 0
void Calibration_Proc(void){
	GUI_PID_STATE State;
	int xSize, ySize;
	static BYTE step=0;
	static WORD last_time;

	if(!Display.recalibration)	return;

	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();

	GUI_TOUCH_GetState(&State);

	switch(step){
		case 0:
			if(State.Pressed){
				step=1;
				last_time=_tick_count;
			}
			break;
		case 1:
			if(State.Pressed){
				if(GetElapsedTickCount(last_time)>250){
					_aSamX[Display.cal_cnt] = State.x;
					_aSamY[Display.cal_cnt] = State.y;
					Display.cal_cnt++;
					if(Display.cal_cnt!=NUM_CALIB_POINTS)
						WM_Paint(_hDialogKeypad[Display.layer]);
					step=2;
				}
			}else{
				step=1;
			}

			break;
		case 2:
			if(!State.Pressed){
				step=0;

				if(Display.cal_cnt==NUM_CALIB_POINTS){
					GUI_TOUCH_EnableCalibration(1);
					GUI_TOUCH_CalcCoefficients(NUM_CALIB_POINTS, _aRefX, _aRefY, _aSamX, _aSamY, xSize, ySize);
					Display.recalibration=FALSE;
					Low_Calibration_Val_Write();
					if(draw_status.status_list.bit.close_limit){
						Draw_Main();
					}else{
						Draw_Main();
					}
				}
			}
			break;
	}
}
#else
#define THRESHOLD 2

coordinate *Read_Ads7846(void){
	static coordinate screen;
	INT m0, m1, m2, temp[3];
	BYTE count = 0;

  	int buffer[2][9]={{0},{0}};
	int pre_buffer[2];
	int TP_X,TP_Y;
	BYTE retry = 0;

	TP_CS(0);

	do{

		SPI_DMA_WRITE();
		while(!((DMA_GetFlagStatus(DMA1_Stream3, DMA_FLAG_TCIF3) == SET) &&
			(DMA_GetFlagStatus(DMA1_Stream4, DMA_FLAG_TCIF4) == SET)));

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
		}else{
			count = 0;
		}
	}while(!TP_INT_IN && count < 9); /* TP_INT_IN */

	TP_CS(1);

	if(count == 9){ /* Average X Y */
		/* Average X */
		temp[0] = (buffer[0][0] + buffer[0][1] + buffer[0][2]) / 3;
		temp[1] = (buffer[0][3] + buffer[0][4] + buffer[0][5]) / 3;
		temp[2] = (buffer[0][6] + buffer[0][7] + buffer[0][8]) / 3;

		m0 = temp[0] - temp[1];
		m1 = temp[1] - temp[2];
		m2 = temp[2] - temp[0];

		m0 = m0>0 ? m0 : (-m0);
		m1 = m1>0 ? m1 : (-m1);
		m2 = m2>0 ? m2 : (-m2);

 		if (m0>THRESHOLD && m1>THRESHOLD && m2>THRESHOLD) return 0;

		if (m0<m1){
			if (m2<m0)
				screen.x = (temp[0] + temp[2]) / 2;
			else
				screen.x = (temp[0] + temp[1]) / 2;
		}else if (m2<m1){
			screen.x = (temp[0] + temp[2]) / 2;
		}else{
			screen.x = (temp[1] + temp[2]) / 2;
		}

		/* Average Y */
		temp[0] = (buffer[1][0] + buffer[1][1] + buffer[1][2]) / 3;
		temp[1] = (buffer[1][3] + buffer[1][4] + buffer[1][5]) / 3;
		temp[2] = (buffer[1][6] + buffer[1][7] + buffer[1][8]) / 3;

		m0 = temp[0] - temp[1];
		m1 = temp[1] - temp[2];
		m2 = temp[2] - temp[0];

		m0 = m0>0 ? m0 : (-m0);
		m1 = m1>0 ? m1 : (-m1);
		m2 = m2>0 ? m2 : (-m2);

		if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;

		if(m0<m1){
			if (m2<m0)
				screen.y = (temp[0] + temp[2]) / 2;
			else
				screen.y = (temp[0] + temp[1]) / 2;
		}else if (m2<m1){
			screen.y = (temp[0] + temp[2]) / 2;
		}else{
			screen.y = (temp[1] + temp[2]) / 2;
		}
		return &screen;
	}
	return 0;
}

#define LOW_CALIBRATION_MAX_COUNT	500

void TouchPanel_Low_Calibrate(void){
	BYTE i;
	BYTE calibration_progressing,calibration_step;
	WORD last_time;
	coordinate *Ptr;
	WORD screen_x,screen_y;
	USHORT read_count = 0;

	GUI_Exec();

	BACK_LIGHT_ON();

	GUI_SelectLayer(0);
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();

	Display.layer=1;
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
#ifdef DEBUG_CALIBRATION
	Myprintf("Factory Reset Calibration Enter\r\n");
#endif
	GUI_SetColor(GUI_BLUE);
	GUI_DispStringHCenterAt("Touch Screen Calibration !!!", LCD_GetXSize() / 2, LCD_GetYSize() / 2 - 50);
	for(i = 0;i < NUM_LOW_CAL_POINTS; i++){
		if(i)   Delay_Ms(1000);
		GUI_Exec();
		GUI_Clear();
		GUI_SetColor(GUI_BLUE);
		GUI_DispStringHCenterAt("Touch Screen Calibration !!!", LCD_GetXSize() / 2, LCD_GetYSize() / 2 - 50);
		GUI_DrawHLine(_display_sample[i].y,_display_sample[i].x - 5,_display_sample[i].x + 5);
		GUI_DrawVLine(_display_sample[i].x,_display_sample[i].y - 5,_display_sample[i].y + 5);
		calibration_progressing = TRUE;
		calibration_step = 0;

		while(calibration_progressing){
			switch(calibration_step){
				case 0:
					Ptr = Read_Ads7846();

					if(Ptr){
						read_count = 0;
						screen_x = 0;
						screen_y = 0;
						GUI_SetColor(GUI_RED);
						GUI_DrawHLine(_display_sample[i].y,_display_sample[i].x - 5,_display_sample[i].x + 5);
						GUI_DrawVLine(_display_sample[i].x,_display_sample[i].y - 5,_display_sample[i].y + 5);
						last_time = _tick_count;
						calibration_step = 1;
					}
					break;
				case 1:
					Ptr = Read_Ads7846();
					if(Ptr){
						screen_x += Ptr->x;
						screen_y += Ptr->y;
						read_count++;
						if(read_count >= LOW_CALIBRATION_MAX_COUNT){
							_screen_sample[i].x = (INT)(screen_x / LOW_CALIBRATION_MAX_COUNT);
							_screen_sample[i].y = (INT)(screen_y / LOW_CALIBRATION_MAX_COUNT);
							calibration_progressing = FALSE;
							GUI_DispStringHCenterAt("OK",_display_sample[i].x,_display_sample[i].y + 7);
							calibration_step = 0;
						}
					}

					if((calibration_progressing == TRUE) && (GetElapsedTickCount(last_time) > 750)){
						GUI_SetColor(GUI_BLUE);
						GUI_DrawHLine(_display_sample[i].y,_display_sample[i].x - 5,_display_sample[i].x + 5);
						GUI_DrawVLine(_display_sample[i].x,_display_sample[i].y - 5,_display_sample[i].y + 5);
						calibration_step = 0;
					}
					break;
			}
		}
#ifdef DEBUG_CALIBRATION
		Myprintf("_screen_sample[%d].X : %d\r\n",i,_screen_sample[i].x);
		Myprintf("_screen_sample[%d].Y : %d\r\n",i,_screen_sample[i].y);
		Usart1_Send();
#endif
	}
	Low_Calibration_Val_Write();
	Calibration_Enter_Write();
	Delay_Ms(10);
	NVIC_SystemReset();
}
#endif

void LCD_Draw_Init(void) {
	GUI_Exec();

	BACK_LIGHT_ON();

	Display.layer=0;
	GUI_SelectLayer(0);
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();

	Display.layer=1;
	GUI_SelectLayer(1);
	GUI_SetBkColor(GUI_WHITE);

	GUI_UC_SetEncodeUTF8();

	LCD_Layer_Change_Set();
	GUI_Clear();
	_hDialogKeypad[Display.layer]= GUI_CreateDialogBox(_aFrameWinKey, GUI_COUNTOF(_aFrameWinKey), _cbFrameWinKey, WM_HBKWIN, 0, 0);
	Hide_ALL(Display.layer);
	WM_ShowWindow(Editor.Hidden_Button[Display.layer]);
	WM_ShowWindow(Editor.Calibration[Display.layer]);
	//LCD_Layer_Change();
	if(Display.layer){
		for(BYTE k=0xff;k>0x00;k--){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(10);
		}
	}else{
		for(BYTE k=0x00;k<0xff;k++){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(10);
		}
	}
	Display.set=FALSE;

	LCD_Layer_Change_Set();
	GUI_Clear();
	_hDialogKeypad[Display.layer]= GUI_CreateDialogBox(_aFrameWinKey, GUI_COUNTOF(_aFrameWinKey), _cbFrameWinKey, WM_HBKWIN, 0, 0);
	Hide_ALL(Display.layer);
	WM_ShowWindow(Editor.Hidden_Button[Display.layer]);
	WM_ShowWindow(Editor.Calibration[Display.layer]);
	//LCD_Layer_Change();
	if(Display.layer){
		for(BYTE k=0xff;k>0x00;k--){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(10);
		}
	}else{
		for(BYTE k=0x00;k<0xff;k++){
			GUI_SetLayerAlphaEx(1,k);
			GUI_Exec();
			Delay_100us(10);
		}
	}
	Display.set=FALSE;
}

void ButtonTouchProc(void)
{
	//static BYTE s_bStep = 0xff;
	GUI_PID_STATE State;
	GUI_TOUCH_GetState(&State);

	Touch_Error_Clear();
#if 0
	if(s_bStep != button_status.step){
		printf("%d\r\n",button_status.step);
		s_bStep = button_status.step;
	}
#endif
	if(draw_order.order_list.bit.auth_access_token){
		if(button_status.step != CLICK_IDLE)	button_status.step = CLICK_IDLE;
		return;
	}

	if((State.Pressed == false) && (button_status.step != CLICK_IDLE)){
		switch(button_status.step){
			case CLICK_NORMALCLICK:
				button_status.last_time = _tick_count;
				button_status.step = CLICK_IDLE;
				draw_order.order_list.bit.stop_order = true;
				Display.open_touch[0] = false;
				Display.open_touch[1] = false;
				Display.close_touch[0] = false;
				Display.close_touch[1] = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
				printf("Not Pressed Off!\r\n");
#endif
#endif
				break;
		}
	}

	if(draw_status.status_list.bit.manual_lock == true){
		if((draw_order.order_list.bit.remote_order == true) || (draw_order.order_list.bit.manual_order == true)){
			if((draw_order.order_list.bit.fault_handling == false) && (draw_order.move_order == false)){
				if(draw_order.order_list.bit.stop_order == false)	draw_order.order_list.bit.stop_order = true;
			}
		}
		return;
	}

	if((button_status.step != CLICK_IDLE)&&(GetElapsedTickCount(button_status.last_time) >= DOUBLECLICK_TIMEOUT))
	{
		switch(button_status.step){
			case CLICK_1ST:
			case CLICK_DETACH:
			case CLICK_2ND:
				if((Display.open_touch[0] == false) && (Display.open_touch[1] == false)
					&& (Display.close_touch[0] == false) && (Display.close_touch[1] == false)){
					button_status.last_time = _tick_count;
					button_status.step = CLICK_IDLE;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Key reset!\r\n");
#endif
#endif
					break;
			}
		}
	}

	if(Display.open_touch[Display.layer] == true){
		button_status.button_id = BUTTON_OPEN;
		button_status.clicked = true;

		if(draw_status.status_list.bit.not_closed){
			draw_status.status_list.bit.not_closed = false;
			WM_Paint(_hDialogKeypad[Display.layer]);
		}

		if(button_status.last_button_id != button_status.button_id){
			switch(button_status.step){
				case CLICK_IDLE:
					break;
				case CLICK_DETACH:
				case CLICK_2ND:
					button_status.step = CLICK_IDLE;
					break;
			}
			button_status.last_button_id = button_status.button_id;
		}

		switch(button_status.step){
			case CLICK_IDLE:
				button_status.step = CLICK_1ST;
				button_status.last_time = _tick_count;
				break;
			case CLICK_DETACH:
				button_status.step = CLICK_2ND;
				button_status.last_time = _tick_count;
				break;
			case CLICK_DOUBLECLICK:
				button_status.step = CLICK_STOP_START;
				break;
		}

		if(((button_status.step == CLICK_1ST) || (button_status.step == CLICK_2ND)) && (GetElapsedTickCount(button_status.last_time) >= NORMALCLICK_TIME)){
			if(draw_status.status_list.bit.open_limit == false){
				if((draw_order.order_list.bit.manual_order == false) && (draw_order.order_list.bit.remote_order == false)){
					if(draw_order.order_list.bit.set_access_token){
						if(draw_order.order_list.bit.auth_access_token){
							button_status.step = CLICK_IDLE;
							return;
						}else{
							ACCESS_TOKEN_DISABLE();
						}
					}
					//printf("moving!\r\n");
					//if(IS_AUTHORIZING_ACCESS_TOKEN())			printf("authorizing token!\r\n");
					button_status.step = CLICK_NORMALCLICK;
					draw_order.order_list.bit.remote_order = false;
					draw_order.order_list.bit.manual_order = true;
					draw_status.status_list.bit.manual = true;
					draw_order.direction = DRAW_DIR_OPEN;
					AC_MOTOR_CW();
					pwm_status.pwm_list.bit.operation = true;
					pwm_status.pwm_list.bit.acceleration = false;
					pwm_status.pwm_list.bit.deceleration = false;
					pwm_status.pwm_list.bit.phase = true;
					pwm_status.pwm_list.bit.slow_section = false;
					TIM7_INT_ENABLE();
					draw_status.encoder_time = _tick_count;
					draw_status.timeout_time = _tick_count;
					draw_order.order_list.bit.watchdog = true;
					if(Display.step == DISPLAY_SETTING){
						draw_encoder.draw_tacho_cw = 0;
						draw_encoder.draw_tacho_ccw = 0;
					}
					//draw_encoder.keep_limit = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Manual open\r\n");
#endif
#endif
				}
			}
		}
	}

	if(Display.close_touch[Display.layer] == true){
		button_status.button_id = BUTTON_CLOSE;
		button_status.clicked = true;
		if(draw_status.status_list.bit.not_closed){
			draw_status.status_list.bit.not_closed = false;
			WM_Paint(_hDialogKeypad[Display.layer]);
		}

		if(button_status.last_button_id != button_status.button_id){
			switch(button_status.step){
				case CLICK_IDLE:
					break;
				case CLICK_DETACH:
				case CLICK_2ND:
					button_status.step = CLICK_IDLE;
					break;
			}
			button_status.last_button_id = button_status.button_id;
		}

		switch(button_status.step){
			case CLICK_IDLE:
				button_status.step = CLICK_1ST;
				button_status.last_time = _tick_count;
				break;
			case CLICK_DETACH:
				button_status.step = CLICK_2ND;
				button_status.last_time = _tick_count;
				break;
			case CLICK_DOUBLECLICK:
				button_status.step = CLICK_STOP_START;
				break;
		}

		if(((button_status.step == CLICK_1ST) || (button_status.step == CLICK_2ND)) && (GetElapsedTickCount(button_status.last_time) >= NORMALCLICK_TIME)){
			if(draw_status.status_list.bit.close_limit == false){
				if((draw_order.order_list.bit.manual_order == false) && (draw_order.order_list.bit.remote_order == false)){
					if(draw_order.order_list.bit.set_access_token){
						if(draw_order.order_list.bit.auth_access_token){
							button_status.step = CLICK_IDLE;
							return;
						}else{
							ACCESS_TOKEN_DISABLE();
						}
					}
					//printf("moving!\r\n");
					button_status.step = CLICK_NORMALCLICK;
					draw_order.order_list.bit.remote_order = false;
					draw_order.order_list.bit.manual_order = true;
					draw_status.status_list.bit.manual = true;
					draw_order.direction = DRAW_DIR_CLOSE;
					AC_MOTOR_CCW();
					pwm_status.pwm_list.bit.operation = true;
					pwm_status.pwm_list.bit.acceleration = false;
					pwm_status.pwm_list.bit.deceleration = false;
					pwm_status.pwm_list.bit.phase = true;
					pwm_status.pwm_list.bit.slow_section = false;
					TIM7_INT_ENABLE();
					draw_status.encoder_time = _tick_count;
					draw_status.timeout_time = _tick_count;
					draw_order.order_list.bit.watchdog = true;
					if(Display.step == DISPLAY_SETTING){
						draw_encoder.draw_tacho_cw = 0;
						draw_encoder.draw_tacho_ccw = 0;
					}
					//draw_encoder.keep_limit = false;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Manual close\r\n");
#endif
#endif
				}
			}
		}
	}

	if((Display.open_touch[Display.layer] == false) && (Display.close_touch[Display.layer] == false) && (button_status.clicked == true)){
		button_status.clicked = false;
		switch(button_status.step){
			case CLICK_1ST:
				if(draw_status.status_list.bit.init_cmpl == true){
					if(draw_order.order_list.bit.remote_order == true){
						draw_encoder.acc_dec_section = INTERMEDIATE_STOP_VOLUME;
						//SineAccelerationTable(INTERMEDIATE_STOP_VOLUME, ACC_FREQ_MIN + 100, sine_acc_32[pwm_status.reload]);
						SineAccelerationTable(INTERMEDIATE_STOP_VOLUME, acc_freq_array[ACC_MIN] + 100, sine_acc_32[pwm_status.reload]);
						pwm_status.reload = INTERMEDIATE_STOP_VOLUME;
						pwm_status.pwm_list.bit.acceleration = false;
						pwm_status.pwm_list.bit.deceleration = true;
						pwm_status.pwm_list.bit.phase = false;
						TIM7_INT_ENABLE();
						draw_order.order_list.bit.intermediate_stop = true;
						button_status.step = CLICK_STOP_MOVING;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
						printf("Stop Moving!\r\n");
#endif
#endif
					}
					button_status.step = CLICK_DETACH;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
					printf("Detach!\r\n");
#endif
#endif
				}else{
#if 0
					if(button_status.button_id == BUTTON_CLOSE)		button_status.step = CLICK_DETACH;
					else 											button_status.step = CLICK_IDLE;
#else
					button_status.step = CLICK_DETACH;
#endif
				}
				break;
			case CLICK_2ND:
				button_status.step = CLICK_DOUBLECLICK;
				if(draw_status.status_list.bit.init_cmpl == true){
					if(draw_order.order_list.bit.remote_order == false){
						//printf("moving!\r\n");
						if((button_status.button_id == BUTTON_OPEN) && (draw_status.status_list.bit.open_limit == false)){
							if(draw_order.order_list.bit.set_access_token){
								if(draw_order.order_list.bit.auth_access_token){
									button_status.step = CLICK_IDLE;
									return;
								}else{
									ACCESS_TOKEN_DISABLE();
								}
							}

							draw_order.order_location = DRAW_PARAM_OPEN;
							DrawerAccRatioProc();
							draw_order.direction = DRAW_DIR_OPEN;
							draw_order.order_list.bit.remote_order = true;
							draw_status.status_list.bit.manual = true;
							draw_status.encoder_time = _tick_count;
							draw_status.timeout_time = _tick_count;
							draw_order.order_list.bit.watchdog = true;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
						printf("Fully Open!\r\n");
#endif
#endif
						}else if((button_status.button_id == BUTTON_CLOSE) && (draw_status.status_list.bit.close_limit == false)){
							if(draw_order.order_list.bit.set_access_token){
								if(draw_order.order_list.bit.auth_access_token){
									button_status.step = CLICK_IDLE;
									return;
								}else{
									ACCESS_TOKEN_DISABLE();
								}
							}
							draw_order.order_location = DRAW_PARAM_CLOSE;
							DrawerAccRatioProc();
							draw_order.direction = DRAW_DIR_CLOSE;
							draw_order.order_list.bit.remote_order = true;
							draw_status.status_list.bit.manual = true;
							draw_status.encoder_time = _tick_count;
							draw_status.timeout_time = _tick_count;
							draw_order.order_list.bit.watchdog = true;
#ifdef DEBUG
#ifdef DEBUG_BUTTON
						printf("Fully Close!\r\n");
#endif
#endif
						}else{
							button_status.step = CLICK_IDLE;
						}
		 		}
			}else{
				if(draw_order.order_list.bit.remote_order == false){
					if((button_status.button_id == BUTTON_CLOSE) && (draw_status.status_list.bit.close_limit == false)){
						if(draw_order.order_list.bit.set_access_token){
							if(draw_order.order_list.bit.auth_access_token){
								button_status.step = CLICK_IDLE;
								return;
							}else{
								ACCESS_TOKEN_DISABLE();
							}
						}
						//printf("moving!\r\n");
						draw_order.my_location = DRAW_PARAM_UNKNOWN;
						draw_order.order_location = DRAW_PARAM_CLOSE;
						DrawerAccRatioProc();
						draw_order.direction = DRAW_DIR_CLOSE;
						draw_order.order_list.bit.remote_order = true;
						draw_status.status_list.bit.manual = true;
						draw_status.encoder_time = _tick_count;
						draw_status.timeout_time = _tick_count;
						draw_order.order_list.bit.watchdog = true;
					}else if((button_status.button_id == BUTTON_OPEN) && (draw_status.status_list.bit.open_limit == false)){
						if(draw_order.order_list.bit.set_access_token){
							if(draw_order.order_list.bit.auth_access_token){
								button_status.step = CLICK_IDLE;
								return;
							}else{
								ACCESS_TOKEN_DISABLE();
							}
						}
						//printf("moving!\r\n");
						draw_order.order_location = DRAW_PARAM_OPEN;
						DrawerAccRatioProc();
						draw_order.direction = DRAW_DIR_OPEN;
						draw_order.order_list.bit.remote_order = true;
						draw_status.status_list.bit.manual = true;
						draw_status.encoder_time = _tick_count;
						draw_status.timeout_time = _tick_count;
						draw_order.order_list.bit.watchdog = true;
					}else{
						button_status.step = CLICK_IDLE;
					}
		 		}
			}
			break;
		}
	}
}

void TextBox_Input(BYTE* Text,WORD inputData){		//2018.11.08   seo
	if(inputData>9999){
		Text[0] = (BYTE)((inputData / 10000) + 0x30);
	}else{
		Text[0] = (BYTE)(0x20);
	}
	if(inputData>999){
		Text[1] = (BYTE)((inputData % 10000) / 1000 + 0x30);
	}else{
		Text[1] = (BYTE)(0x20);
	}
	if(inputData>99){
		Text[2] = (BYTE)((inputData % 1000) / 100 + 0x30);
	}else{
		Text[2] = (BYTE)(0x20);
	}
	if(inputData>9){
		Text[3] = (BYTE)(((inputData % 100) / 10) + 0x30);
	}else{
		Text[3] = (BYTE)(0x20);
	}
	Text[4] = (BYTE)((inputData % 10) + 0x30);
}


void Display_Encoder(void){
	static WORD lastEnc = 0xffff, last_cw = 0xffff, last_ccw = 0xffff;
	static BYTE last_alarm = 0xff, last_setspeed;

	switch(Display.step){
		case DISPLAY_SETTING:
			if(lastEnc != draw_encoder.draw_my_encoder){
				TextBox_Input(Display.Text_arr,draw_encoder.draw_my_encoder);
				TEXT_SetText(Editor.TEXT_Encoder[Display.layer],(const char *)Display.Text_arr);
				TEXT_SetText(Editor.TEXT_Encoder[Display.layer^1],(const char *)Display.Text_arr);
				lastEnc = draw_encoder.draw_my_encoder;
			}
			if(last_cw != draw_encoder.draw_tacho_cw){
				TextBox_Input(Display.Text_cw,draw_encoder.draw_tacho_cw);
				TEXT_SetText(Editor.display_cw[Display.layer],(const char *)Display.Text_cw);
				last_cw = draw_encoder.draw_tacho_cw;
			}

			if(last_ccw != draw_encoder.draw_tacho_ccw){
				TextBox_Input(Display.Text_ccw,draw_encoder.draw_tacho_ccw);
				TEXT_SetText(Editor.display_ccw[Display.layer],(const char *)Display.Text_ccw);
				last_ccw = draw_encoder.draw_tacho_ccw;
			}

			if(last_alarm != draw_status.status_list.byte[1]){
				last_alarm = draw_status.status_list.byte[1];
				WM_Paint(_hDialogKeypad[Display.layer]);
			}

			if(last_setspeed != Display.set_speed){
				last_setspeed = Display.set_speed;
				WM_Paint(_hDialogKeypad[Display.layer]);
			}
			break;
		default:
			break;
	}
}

void Disp_ElapsedTime(void)
{
	TextBox_Input(Display.Text_Elapsed_Time,draw_encoder.elapsed_time);
	TEXT_SetText(Editor.TEXT_ElapsedTime[Display.layer],(const char *)Display.Text_Elapsed_Time);
}

