/**
  ******************************************************************************
  * @vendor		CRETEM
  * @project	Automatic_Drawer
  * @file    	LCD_Draw.h
  * @author  	Firmware Team
  ******************************************************************************/
#ifndef LCD_Draw_H
#define LCD_Draw_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/* Exported types ------------------------------------------------------------*/
typedef struct _Editor{
	WM_HWIN Close[2];
	WM_HWIN Open[2];
	WM_HWIN Yes[2];
	WM_HWIN No[2];
	WM_HWIN Option_Open[2];
	WM_HWIN Option_Close[2];
	WM_HWIN Calibration[2];

	WM_HWIN Init[2];
	WM_HWIN Option_Init[2];
	WM_HWIN EDIT_DRAWER[2];		//2018.11.08   seo
	WM_HWIN Encoder_Save[2];
	WM_HWIN Encoder_Move[2];		//2018.11.08   seo
	WM_HWIN TEXT_Encoder[2];		//2018.11.08   seo
	WM_HWIN TEXT_Version[2];
	WM_HWIN TEXT_Acc[2];
	WM_HWIN Image_Draw_num[2];
	WM_HWIN Image_Cretem[2];

	WM_HWIN Keypad[2][10];
	WM_HWIN Key_CLR[2];
	WM_HWIN Key_DEL[2];
	WM_HWIN Key_EXIT[2];

	WM_HWIN TEXT_Open[2];		//2018.11.08   seo
	WM_HWIN TEXT_Close[2];		//2018.11.08   seo
	WM_HWIN TEXT_Origin[2];		//2018.11.08   seo

	WM_HWIN Hidden_Button[2];

	WM_HWIN TEXT_ElapsedTime[2];		//2019-10-25 -LMI-
	WM_HWIN	display_cw[2];
	WM_HWIN display_ccw[2];

	GUI_COLOR R_circle_color;
	WORD R_circle_xposition;
	WORD R_circle_yposition;
	WORD R_circle_size;

	GUI_COLOR L_circle_color;
	WORD L_circle_xposition;
	WORD L_circle_yposition;
	WORD L_circle_size;


	BYTE color_receive;
	GUI_COLOR R_rec_on_color;
	GUI_COLOR R_rec_off_color;
	GUI_COLOR L_rec_on_color;
	GUI_COLOR L_rec_off_color;
	WORD R_rec_toggle_time;
	WORD L_rec_toggle_time;
}Editor_module;

typedef struct _Display{
	BYTE layer;
	BYTE set;
	WORD selected_Num;
	BYTE step;
	BYTE pre_step;
	BYTE init;
	BYTE status;
	BYTE cal_cnt;
	BYTE recalibration;
	BYTE retry;
	BYTE retry_key;
	BYTE open_touch[2];
	BYTE close_touch[2];
	BYTE Text_arr[6];		//2018.11.12   seo
	BYTE Text_Encoder_arr[6];
	BYTE Text_Elapsed_Time[6];		//2019.10.25 -LMI-
	BYTE Text_cw[6];
	BYTE Text_ccw[6];
	BYTE setting_touch[2];
	WORD last_time;
	BYTE status_toggle;
	BYTE set_speed;
	BYTE overlapping;
	BYTE dissolve;
	WORD dissolve_time;
	BOOL change_reserve;
	BYTE change_disp;
}Display_module;

typedef enum{
	LEFT_CIRCLE=0,
	RIGHT_CIRCLE
}CHOOSE_SET;

typedef enum{
	CLICK_IDLE = 0,
	CLICK_1ST,
	CLICK_DETACH,
	CLICK_2ND,
	CLICK_DOUBLECLICK,
	CLICK_NORMALCLICK,
	CLICK_STOP_START,
	CLICK_STOP_MOVING,
}Button_Enum;

typedef struct{
	unsigned click_idle:1;
	unsigned click_start:1;
	unsigned click_detach:1;
	unsigned double_clicked:1;
	unsigned normal_clicked:1;
	unsigned clicked:1;
	unsigned dummy_04:1;
	unsigned dummy_05:1;

	BYTE click_count;
	BYTE button_id;
	BYTE last_button_id;
	//WORD open_time;
	//WORD close_time;
	//BYTE open_step;
	//BYTE close_step;
	BYTE step;
	WORD last_time;
}Button_Module;

#define DOUBLECLICK_TIMEOUT			400
#define NORMALCLICK_TIME			175


/* Exported define -----------------------------------------------------------*/
#define Keypad_NUM_1			1
#define Keypad_NUM_2			2
#define Keypad_NUM_3			3
#define Keypad_NUM_4			4
#define Keypad_NUM_5			5
#define Keypad_NUM_6			6
#define Keypad_NUM_7			7
#define Keypad_NUM_8			8
#define Keypad_NUM_9			9
#define Keypad_NUM_0			10

#define Keypad_CLR				11
#define Keypad_DEL				12
#define OPTION_SAVE				13
#define OPTION_MOVE				14
#define OPTION_EXIT				15
#define OPTION_OPEN            	16
#define OPTION_CLOSE         	17
#define OPTION_INIT         	18

#define BUTTON_OPEN				19
#define BUTTON_CLOSE			20
#define BUTTON_YES				21
#define BUTTON_NO				22
#define BUTTON_INIT				23

#define TEXT_OPEN				24
#define TEXT_CLOSE				25
#define TEXT_ORIGIN				26
#define Text_Encoder			27		//2018.11.08   seo
#define EDIT_DRAWER_NUM			28
#define BUTTON_CALIBRATION		29
#define TEXT_VERSION			30
#define IMAGE_CRETEM_LOGO		31
#define TEXT_ACC				32
#define Text_ElapsedTime		33		//2019-10-25 -LMI-
#define TEXT_CW					34
#define TEXT_CCW				35

#define BUTTON_HIDDEN			99

#define KEYPAD_XSIZE		61
#define KEYPAD_YSIZE		61
#define BUTTON_INTERVAL		2
#define KEYPAD_START_X_POINT	221
#define KEYPAD_START_Y_POINT	11

#define FUNCTION_BUTTON_XSIZE	79
#define FUNCTION_BUTTON_YSIZE	78

#define Main_window			201

#define DISPLAY_MAIN		0
#define DISPLAY_DISPENSE	1
#define DISPLAY_REFILL		2
#define DISPLAY_LOCK		3
#define DISPLAY_INTRO		4
#define DISPLAY_INIT		5
#define DISPLAY_ERROR		6
#define DISPLAY_OPEN		7
#define DISPLAY_CLOSE		8
#define DISPLAY_SETTING		9
#define DISPLAY_MAIN_LOCK	10
//#define DISPLAY_CALIBRATION	10

#define NUM_CALIB_POINTS  5  // Number of points for calibration

#define TEXT_PRESS_COLOR	GUI_WHITE
#define TEXT_UNPRESS_COLOR	GUI_WHITE
#define Lock_Keypad_COLOR	GUI_GRAY

#define DRAWER_STATUS_STOP			0
#define DRAWER_STATUS_OPEN			1
#define DRAWER_STATUS_CLOSE			2

#define LEFT_CIRCLE_DEFAULT_COLOR	0x0000CBCB
#define LEFT_OUTLINE_COLOR			0x0000AAAA
#define LEFT_CIRCLE_XPOSITION		120
#define LEFT_CIRCLE_YPOSITION		60
#define LEFT_CIRCLE_SIZE			40
#define LEFT_CIRCLR_ON_COLOR		0x0020FFFF

#define RIGHT_CIRCLE_DEFAULT_COLOR	0x000000CB
#define RIGHT_OUTLINE_COLOR			0x000000AA
#define RIGHT_CIRCLE_XPOSITION		360
#define RIGHT_CIRCLE_YPOSITION		60
#define RIGHT_CIRCLE_SIZE			40
#define RIGHT_CIRCLR_ON_COLOR		0x002020FF

#define POSITION_BUFFER			2
#define SIZE_BUFFER				2
#define COLOR_BUFFER			2

#define OUTLINE_THICKNESS		3

#define KEYPAD_NUM_UPPER_UPPER		0x00141414
#define KEYPAD_NUM_UPPER_LOWER		0x00141414

#define KEYPAD_NUM_LOWER_UPPER		0x00141414
#define KEYPAD_NUM_LOWER_LOWER		0x00141414

#define KEYPAD_NUM_OUTLINE1			0x00141414
#define KEYPAD_NUM_OUTLINE2			0x00141414
#define KEYPAD_NUM_OUTLINE3			0x00141414
#define KEYPAD_NUM_RADIOUS			3

#define KEYPAD_OPTION_UPPER_UPPER		0x00F7D155
#define KEYPAD_OPTION_UPPER_LOWER		0x00F7D155

#define KEYPAD_OPTION_LOWER_UPPER		0x00F7D155
#define KEYPAD_OPTION_LOWER_LOWER		0x00F7D155

#define KEYPAD_OPTION_OUTLINE1			0x00F7D155
#define KEYPAD_OPTION_OUTLINE2			0x00F7D155
#define KEYPAD_OPTION_OUTLINE3			0x00F7D155
#define KEYPAD_OPTION_RADIOUS			3


#define BACKGROUND_SETTING		0x00282828

//#define BACKGROUND_UPPER		0x00FFFFFF
#define BACKGROUND_UPPER		0x00F5E4BA
#define BACKGROUND_LOWER		0x00EAAB42
#define BACKGROUND_LOCK_UPPER	0x008080F0
#define BACKGROUND_LOCK_LOWER	0x007AA0FF
#define BACKGROUND_FAIL_UPPER	0x00959595
#define BACKGROUND_FAIL_LOWER	0x00353331

//#define DISPENSE_UPPER			0x005DCF03
//#define DISPENSE_LOWER			0x0086DF40
#define DISPENSE_UPPER			0x005AC804
#define DISPENSE_LOWER			0x007BD237

//#define REFILL_UPPER			0x007373FA
//#define REFILL_LOWER			0x009696FF
#define REFILL_UPPER			0x008080F0
#define REFILL_LOWER			0x007AA0FF

#define BACKGROUND_LOCK			0x003BB0FB
#define BACKGROUND_ERROR		0x003BB0FB

#define LEFT_BUTTON_TEXT_UNPRESS	0x0079CCAA
#define LEFT_BUTTON_TEXT_PRESS		0x0079CCAA
#define RIGHT_BUTTON_TEXT_UNPRESS	0x007979E2
#define RIGHT_BUTTON_TEXT_PRESS		0x007979E2

#define STATUS_STOP_LEFT	0x002DB6F8
#define STATUS_STOP_RIGHT	0x000098F3

#define STATUS_OPEN_LEFT	0x00E5C210
#define STATUS_OPEN_RIGHT	0x00812400

#define STATUS_CLOSE_LEFT	0x001FC38F
#define STATUS_CLOSE_RIGHT	0x00346900

#define EEP_ADDR_TOUCH_CALIBRATION_EXEC	0x20F

#define ADDR_TOUCH_CALIBRATION_X		0x210
#define ADDR_TOUCH_CALIBRATION_Y		0x220

#define ADDR_FREQ_MAX					0x130
#define ADDR_FREQ_MIN					0x132
#define ADDR_FREQ_SLOW_MAX				0x134
#define ADDR_FREQ_SLOW_MIX				0x136
#define ADDR_FREQ_MOVING_SPD			0x138

#define SET_FREQ_MAX		0
#define SET_FREQ_MIN		1
#define SET_FREQ_SLOW_MAX	2
#define SET_FREQ_SLOW_MIN	3
#define SET_FREQ_MOVING_SPD	4
#define SET_LOOP_TEST		5
#define SET_IDLE			6

//2018.11.08   seo
#define SELECTED_NUM_1			1
#define SELECTED_NUM_2			2
#define SELECTED_NUM_3			3
#define SELECTED_NUM_4			4
#define SELECTED_NUM_5			5
#define SELECTED_NUM_6			6
#define SELECTED_NUM_7			7
#define SELECTED_NUM_8			8
#define SELECTED_NUM_9			9
#define SELECTED_NUM_10			10
#define SELECTED_NUM_11			11
#define SELECTED_NUM_12			12

/* Exported constants --------------------------------------------------------*/
extern Editor_module Editor;
extern Display_module Display;
extern Button_Module button_status;

extern WM_HWIN _hDialogKeypad[];

extern const GUI_WIDGET_CREATE_INFO _aFrameWinKey[];		//2018.11.08   seo
extern const GUI_WIDGET_CREATE_INFO _aCircleDraw[];			//2018.11.08   seo
extern const GUI_WIDGET_CREATE_INFO _aOptionDraw[];			//2018.11.08   seo

extern int _aRefX[NUM_CALIB_POINTS];
extern int _aRefY[NUM_CALIB_POINTS];
extern int _aSamX[NUM_CALIB_POINTS];
extern int _aSamY[NUM_CALIB_POINTS];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void _cbCircleDraw(WM_MESSAGE * pMsg);		//2018.11.08   seo
extern void _cbOptionDraw(WM_MESSAGE * pMsg);		//2018.11.08   seo
extern void _cbFrameWinKey(WM_MESSAGE * pMsg);		//2018.11.08   seo
extern void Init_variables(void);
extern void Recieved_Key(WORD key);
extern void Recieved_Option_Clicked(WORD key);
extern void Recieved_Key_Clicked(WORD key);
extern void Edit_Key(WORD key);
extern void LCD_Draw_Init(void);
extern void LCD_Layer_Change(void);
extern void LCD_Layer_Change_Set(void);
extern void Open_Touch_Proc(void);
extern void Close_Touch_Proc(void);
extern void _cbOptionDraw(WM_MESSAGE * pMsg);
extern void Display_Encoder(void);				//2018.11.08   seo
extern void Circle_Draw(void);			//2018.11.08   seo
extern void LCD_Display_Switch(void);
extern void Enter_Setting_Mode(void);
extern void TextBox_Input(BYTE* Text,WORD inputData);
extern void Display_Sensor_InOut(void);
extern void Calibration_Proc(void);
extern void Low_Calibration_Val_Write(void);
extern void Low_Calibration_Val_Read(void);
extern void Touch_Drag_Proc(void);
extern void Released_key_Retry(void);
extern void LCD_Number_Display(void);
extern void ButtonTouchProc(void);
extern void Touch_Error_Clear(void);
extern void Draw_Calibration(void);
extern void Low_Calibration_Val_Write(void);
extern void Low_Calibration_Val_Read(void);
extern void Calibration_Enter_Reset_Write(void);
extern void Calibration_Enter_Write(void);
extern BYTE Calibration_Enter_Read(void);
extern void ACC_Val_Write(WORD acc_speed);
extern void ACC_Val_Read(WORD acc_speed);
extern void ACC_Text_Disp(void);
extern void Disp_ElapsedTime(void);
extern void LayerFuncDissolve(void);
extern void Draw_Main(void);
extern void Draw_Dispense(void);
extern void Draw_Refill(void);
extern void TouchPanel_Low_Calibrate(void);
extern void Draw_Mainlock(void);
extern void LCD_Layer_Change2(void);
extern void DispRefillButton(void);

#if defined(__cplusplus)
  }
#endif

#endif // Avoid multiple inclusion
