#include "Inputs.h"

// ================================================
// Keys
// ================================================
U16 Input::Internal::keys[KEY_COUNT];
B8  Input::Internal::firstKeyPress[KEY_COUNT];	// This array registers the key first presses. It turns to false after each frame, so If I press A it will only be tru for that frame
    
U16 Input::Key_Backspace;
U16 Input::Key_Tab;
U16 Input::Key_Enter;
U16 Input::Key_Mayus;
U16 Input::Key_Escape;
U16 Input::Key_Space;
    
U16 Input::Key_Left;
U16 Input::Key_Up;
U16 Input::Key_Right;
U16 Input::Key_Down;	 
    
U16 Input::Key_A;
U16 Input::Key_B;
U16 Input::Key_C;
U16 Input::Key_D;
U16 Input::Key_E;
U16 Input::Key_F;
U16 Input::Key_G;
U16 Input::Key_H;
U16 Input::Key_I;
U16 Input::Key_J;
U16 Input::Key_K;
U16 Input::Key_L;
U16 Input::Key_M;
U16 Input::Key_N;
U16 Input::Key_O;
U16 Input::Key_P;
U16 Input::Key_Q;
U16 Input::Key_R;
U16 Input::Key_S;
U16 Input::Key_T;
U16 Input::Key_U;
U16 Input::Key_V;
U16 Input::Key_W;
U16 Input::Key_X;
U16 Input::Key_Y;
U16 Input::Key_Z;
	
U16 Input::Key_0;
U16 Input::Key_1;
U16 Input::Key_2;
U16 Input::Key_3;
U16 Input::Key_4;
U16 Input::Key_5;
U16 Input::Key_6;
U16 Input::Key_7;
U16 Input::Key_8;
U16 Input::Key_9;
	
U16 Input::Key_Numpad_0;
U16 Input::Key_Numpad_1;
U16 Input::Key_Numpad_2;
U16 Input::Key_Numpad_3;
U16 Input::Key_Numpad_4;
U16 Input::Key_Numpad_5;
U16 Input::Key_Numpad_6;
U16 Input::Key_Numpad_7;
U16 Input::Key_Numpad_8;
U16 Input::Key_Numpad_9;

U16 Input::Key_Numpad_Times;
U16 Input::Key_Numpad_Plus;
U16 Input::Key_Numpad_Minus;
U16 Input::Key_Numpad_Dot;
U16 Input::Key_Numpad_Division;

U16 Input::Key_F1;
U16 Input::Key_F2;
U16 Input::Key_F3;
U16 Input::Key_F4;
U16 Input::Key_F5;
U16 Input::Key_F6;
U16 Input::Key_F7;
U16 Input::Key_F8;
U16 Input::Key_F9;
U16 Input::Key_F10;
U16 Input::Key_F11;
U16 Input::Key_F12;

U16 Input::Key_Alt_R;
U16 Input::Key_Alt_A;
U16 Input::Key_Alt_S;
U16 Input::Key_Alt_G;
U16 Input::Key_Alt_X;
U16 Input::Key_Alt_C;

U16 Input::Key_Left_Shift;
U16 Input::Key_Right_Shift;
U16 Input::Key_Left_Ctrl;
U16 Input::Key_Right_Ctrl;

U16 Input::Key_Minus;
U16 Input::Key_Dot;
U16 Input::Key_Tilde;


// ================================================
// Mouse
// ================================================
float Mouse::SENSITIVITY_X     = 0.1f;
float Mouse::SENSITIVITY_Y     = 0.1f;
float Mouse::PAN_SENSITIVITY   = 0.001f;
float Mouse::ScrollWheelOffset = 0.0f; 

float Mouse::GLOBAL_X;			
float Mouse::GLOBAL_Y;			

float Mouse::X;				
float Mouse::Y;				

U8    Mouse::BUTTON_LEFT;
U8    Mouse::BUTTON_RIGHT;
U8    Mouse::BUTTON_SCROLL_WHEEL;

B8    Mouse::Internal::BUTTON_LEFT_FIRST_PRESS;
B8    Mouse::Internal::BUTTON_RIGHT_FIRST_PRESS;
B8    Mouse::Internal::BUTTON_SCROLL_WHEEL_FIRST_PRESS;

// bool  Mouse::Internal::SHOW_CURSOR = true;


// ================================================
// Controller
// ================================================
U8	  Controller::CONNECTED                  = 0;
float Controller::LEFT_JOYSTICK_DEAD_ZONE    = 0.1f;
float Controller::RIGHT_JOYSTICK_DEAD_ZONE   = 0.1f;
float Controller::RIGHT_JOYSTICK_SENSITIVITY = 4.0f;

Vec2  Controller::JOYSTICK_LEFT;
Vec2  Controller::JOYSTICK_RIGHT;

U8	  Controller::BUTTON_L1;
U8	  Controller::BUTTON_R1;

U8	  Controller::BUTTON_L2;
U8	  Controller::BUTTON_R2;

float Controller::RANGE_L2;
float Controller::RANGE_R2;

U8    Controller::BUTTON_L3;
U8    Controller::BUTTON_R3;

U8	  Controller::DPAD_UP;
U8	  Controller::DPAD_DOWN;
U8	  Controller::DPAD_LEFT;
U8	  Controller::DPAD_RIGHT;

U8	  Controller::BUTTON_SQUARE;
U8	  Controller::BUTTON_EX;
U8	  Controller::BUTTON_CIRCLE;
U8	  Controller::BUTTON_TRIANGLE;

U8    Controller::BUTTON_SELECT;
U8    Controller::BUTTON_START;

U8    Controller::BUTTON_PS_HOME;
U8    Controller::BUTTON_TOUCHPAD;
U8    Controller::BUTTON_MICROPHONE;



bool fInput::Key(int key)
{
	return Input::Internal::keys[key];	
}

bool fInput::FirstPress(U16 key)
{
	return Input::Internal::keys[key] && !Input::Internal::firstKeyPress[key];
}



MDF_KEY fInput::GetCurrentModKey()
{
	if		(Input::Key_Left_Ctrl && Input::Key_Left_Shift) { return MDF_CTRL_SHIFT; }
	else if (Input::Key_Left_Shift)						    { return MDF_SHIFT;		 }
	else if (Input::Key_Left_Ctrl)							{ return MDF_CTRL;		 }

	return NO_MDF_KEY;
}

Vec3 fInput::GetMouseNormalizedDeviceCoords(Vec2 &windowDimensions)
{
	float ndcX =     Mouse::X / windowDimensions.width  * 2 - 1;
	float ndcY = 1 - Mouse::Y / windowDimensions.height * 2;
	
	return { ndcX, ndcY, 1.0f };
}

Vec3 fInput::GetMouseNormalizedDeviceCoords(Vec2 &windowDimensions, bool invertY)
{
	float ndcX = Mouse::X / windowDimensions.width * 2 - 1;
	float ndcY = invertY ? Mouse::Y / windowDimensions.height * 2 - 1.0f : 1 - Mouse::Y / windowDimensions.height * 2;

	return { ndcX, ndcY, 1.0f };
}

void fInput::ClearAllInputState()
{
	//Mouse::BUTTON_LEFT         = 0;
	//Mouse::BUTTON_RIGHT        = 0;
	//Mouse::BUTTON_SCROLL_WHEEL = 0;

	for (unsigned int i = 0; i < KEY_COUNT; i++)
	{
		Input::Internal::keys[i] = 0;
	}
}

bool fMouse::FirstPress(MOUSE_BUTTONS button)
{
	switch (button)
	{
		case MOUSE_BUTTONS::LEFT_BUTTON:		 { return Mouse::BUTTON_LEFT		 && !Mouse::Internal::BUTTON_LEFT_FIRST_PRESS;		   } break;
		case MOUSE_BUTTONS::RIGHT_BUTTON:		 { return Mouse::BUTTON_RIGHT		 && !Mouse::Internal::BUTTON_RIGHT_FIRST_PRESS;		   } break;
		case MOUSE_BUTTONS::SCROLL_WHEEL_BUTTON: { return Mouse::BUTTON_SCROLL_WHEEL && !Mouse::Internal::BUTTON_SCROLL_WHEEL_FIRST_PRESS; } break;
	}
	
	return false;
}
