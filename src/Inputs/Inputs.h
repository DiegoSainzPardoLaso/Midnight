// Both Valid ways of asking for inputs
// 
// if (Input::Key(KEY_A)) { }
// if (Input::Key_A)      { }
// 
#pragma once

#include <iostream>

#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include "../Utilities/Definitions.h"

#define  KEY_COUNT           256
						     
#define  KEY_BACKSPACE		  8
#define  KEY_TAB		      9
#define  KEY_ENTER           13						 
#define  KEY_MAYUS		     20
#define  KEY_ESCAPE		     27	
#define  KEY_SPACE		     32
						     						 
#define  KEY_LEFT		     37
#define  KEY_UP			     38
#define  KEY_RIGHT		     39
#define  KEY_DOWN		     40
						     
#define  KEY_0			     48
#define  KEY_1			     49
#define  KEY_2			     50
#define  KEY_3			     51
#define  KEY_4			     52
#define  KEY_5			     53
#define  KEY_6			     54
#define  KEY_7			     55
#define  KEY_8			     56
#define  KEY_9			     57
						     
#define  KEY_A			     65
#define  KEY_B			     66
#define  KEY_C			     67
#define  KEY_D			     68
#define  KEY_E			     69
#define  KEY_F			     70
#define  KEY_G			     71
#define  KEY_H			     72
#define  KEY_I			     73
#define  KEY_J			     74
#define  KEY_K			     75
#define  KEY_L			     76
#define  KEY_M			     77
#define  KEY_N			     78
#define  KEY_O			     79
#define  KEY_P			     80
#define  KEY_Q			     81
#define  KEY_R			     82
#define  KEY_S			     83
#define  KEY_T			     84
#define  KEY_U			     85
#define  KEY_V			     86
#define  KEY_W			     87
#define  KEY_X			     88
#define  KEY_Y			     89
#define  KEY_Z			     90
						     
#define  KEY_NUMPAD_0        96
#define  KEY_NUMPAD_1        97
#define  KEY_NUMPAD_2        98
#define  KEY_NUMPAD_3        99
#define  KEY_NUMPAD_4        100
#define  KEY_NUMPAD_5        101
#define  KEY_NUMPAD_6        102
#define  KEY_NUMPAD_7        103
#define  KEY_NUMPAD_8        104
#define  KEY_NUMPAD_9        105
#define  KEY_NUMPAD_TIMES    106
#define  KEY_NUMPAD_PLUS     107
#define  KEY_NUMPAD_MINUS    109
#define  KEY_NUMPAD_DOT		 110
#define  KEY_NUMPAD_DIVISION 111

#define  KEY_F1              112
#define  KEY_F2              113
#define  KEY_F3              114
#define  KEY_F4              115
#define  KEY_F5              116
#define  KEY_F6              117
#define  KEY_F7              118
#define  KEY_F8              119
#define  KEY_F9              120
#define  KEY_F10             121
#define  KEY_F11             122
#define  KEY_F12             123
						     
#define  KEY_ALT_R		     124		// Alt R - 19 - I add 105 to 19 so the inputs don't clash together
#define  KEY_ALT_A		     135		// Alt A - 30 - I add 105 to 19 so the inputs don't clash together
#define  KEY_ALT_S		     136		// Alt S - 31 - I add 105 to 19 so the inputs don't clash together
#define  KEY_ALT_G		     139		// Alt G - 34 - I add 105 to 19 so the inputs don't clash together
#define  KEY_ALT_X		     150		// Alt X - 45 - I add 105 to 19 so the inputs don't clash together
#define  KEY_ALT_C		     151		// Alt C - 46 - I add 105 to 19 so the inputs don't clash together
						     
#define  KEY_LEFT_SHIFT	     160
#define  KEY_RIGHT_SHIFT     161
#define  KEY_LEFT_CTRL	     162
#define  KEY_RIGHT_CTRL	     163
#define  KEY_LEFT_ALT        164
#define  KEY_RIGHT_ALT       165
						     
#define  KEY_MINUS		     189
#define  KEY_DOT			 190
#define  KEY_TILDE		     192


enum I_STATE 
{
	RELEASED,
	PRESSED,
};

enum MDF_KEY
{
	NO_MDF_KEY,
	MDF_SHIFT,
	MDF_CTRL,
	MDF_CTRL_SHIFT
};

enum MOUSE_BUTTONS
{
	LEFT_BUTTON,
	RIGHT_BUTTON,
	SCROLL_WHEEL_BUTTON
};

namespace Input
{	
	extern U16 Key_Backspace;
	extern U16 Key_Tab;
	extern U16 Key_Enter;
	extern U16 Key_Mayus;
	extern U16 Key_Escape;
	extern U16 Key_Space;	
			
	extern U16 Key_Left;
	extern U16 Key_Up;
	extern U16 Key_Right;
	extern U16 Key_Down;
						
	extern U16 Key_A; 
	extern U16 Key_B; 
	extern U16 Key_C; 
	extern U16 Key_D; 
	extern U16 Key_E; 
	extern U16 Key_F; 
	extern U16 Key_G; 
	extern U16 Key_H; 
	extern U16 Key_I; 
	extern U16 Key_J; 
	extern U16 Key_K; 
	extern U16 Key_L; 
	extern U16 Key_M; 
	extern U16 Key_N; 
	extern U16 Key_O; 
	extern U16 Key_P; 
	extern U16 Key_Q; 
	extern U16 Key_R; 
	extern U16 Key_S; 
	extern U16 Key_T; 
	extern U16 Key_U; 
	extern U16 Key_V; 
	extern U16 Key_W; 
	extern U16 Key_X; 
	extern U16 Key_Y; 
	extern U16 Key_Z;
			
	extern U16 Key_0;
	extern U16 Key_1;
	extern U16 Key_2;
	extern U16 Key_3;
	extern U16 Key_4;
	extern U16 Key_5;
	extern U16 Key_6;
	extern U16 Key_7;
	extern U16 Key_8;
	extern U16 Key_9;
			
	extern U16 Key_Numpad_0;
	extern U16 Key_Numpad_1;
	extern U16 Key_Numpad_2;
	extern U16 Key_Numpad_3;
	extern U16 Key_Numpad_4;
	extern U16 Key_Numpad_5;
	extern U16 Key_Numpad_6;
	extern U16 Key_Numpad_7;
	extern U16 Key_Numpad_8;
	extern U16 Key_Numpad_9;

	extern U16 Key_Numpad_Times;
	extern U16 Key_Numpad_Plus;
	extern U16 Key_Numpad_Minus;
	extern U16 Key_Numpad_Dot;
	extern U16 Key_Numpad_Division;	

	extern U16 Key_F1;
	extern U16 Key_F2;
	extern U16 Key_F3;
	extern U16 Key_F4;
	extern U16 Key_F5;
	extern U16 Key_F6;
	extern U16 Key_F7;
	extern U16 Key_F8;
	extern U16 Key_F9;
	extern U16 Key_F10;
	extern U16 Key_F11;
	extern U16 Key_F12;

	extern U16 Key_Alt_R;
	extern U16 Key_Alt_A;
	extern U16 Key_Alt_S;
	extern U16 Key_Alt_G;
	extern U16 Key_Alt_X;
	extern U16 Key_Alt_C;

	extern U16 Key_Left_Shift;
	extern U16 Key_Right_Shift;
	extern U16 Key_Left_Ctrl;
	extern U16 Key_Right_Ctrl;

	extern U16 Key_Minus;
	extern U16 Key_Dot;
	extern U16 Key_Tilde;

	// ==============================
	// Alt Key Combinations
	// ==============================
	extern U16 Key_Alt_S;


	namespace Internal
	{
		extern U16 keys[KEY_COUNT];
		extern B8  firstKeyPress[KEY_COUNT];
	}	
}

namespace Mouse
{	
	extern float  SENSITIVITY_X;
	extern float  SENSITIVITY_Y;
	extern float  PAN_SENSITIVITY;
	extern float  ScrollWheelOffset;
		
	extern float  GLOBAL_X;			// Global for multiple screens [ Virtual Space ]
	extern float  GLOBAL_Y;			// Global for multiple screens [ Virtual Space ]	
		
	extern float  X;				// Relative to the window
	extern float  Y;				// Relative to the window
			
	extern U8     BUTTON_LEFT;
	extern U8     BUTTON_RIGHT;
	extern U8     BUTTON_SCROLL_WHEEL;

	namespace Internal
	{
		extern B8 BUTTON_LEFT_FIRST_PRESS;
		extern B8 BUTTON_RIGHT_FIRST_PRESS;
		extern B8 BUTTON_SCROLL_WHEEL_FIRST_PRESS;

		// extern bool SHOW_CURSOR;	// @note The ShowCursor Function toggles this boolean and I hide or show the cursor from the fOSM translation unit
	}
}


namespace Controller
{	
	extern U8	 CONNECTED;
	extern float LEFT_JOYSTICK_DEAD_ZONE;
	extern float RIGHT_JOYSTICK_DEAD_ZONE;
	extern float RIGHT_JOYSTICK_SENSITIVITY;

	extern Vec2	 JOYSTICK_LEFT;
	extern Vec2	 JOYSTICK_RIGHT;
		
	extern U8	 BUTTON_L1;
	extern U8	 BUTTON_R1;					    					    

	extern U8	 BUTTON_L2;
	extern U8	 BUTTON_R2;

	extern float RANGE_L2;
	extern float RANGE_R2;

	extern U8    BUTTON_L3;
	extern U8    BUTTON_R3;
					    
	extern U8	 DPAD_UP;
	extern U8	 DPAD_DOWN;
	extern U8	 DPAD_LEFT;
	extern U8	 DPAD_RIGHT;

	extern U8	 BUTTON_SQUARE;
	extern U8	 BUTTON_EX;
	extern U8	 BUTTON_CIRCLE;
	extern U8	 BUTTON_TRIANGLE;
					 					 
	extern U8    BUTTON_SELECT;
	extern U8    BUTTON_START;

	extern U8    BUTTON_PS_HOME;
	extern U8    BUTTON_TOUCHPAD;
	extern U8    BUTTON_MICROPHONE;
}

namespace fInput
{				
	// void ShowCursor(bool show);
	MDF_KEY GetCurrentModKey();
	Vec3	GetMouseNormalizedDeviceCoords(Vec2 &windowDimensions);			
	Vec3	GetMouseNormalizedDeviceCoords(Vec2 &windowDimensions, bool invertY);
	void	ClearAllInputState();
	bool	Key(int key);
	bool	FirstPress(U16 key);
}

namespace fMouse
{
	bool FirstPress(MOUSE_BUTTONS button);
}