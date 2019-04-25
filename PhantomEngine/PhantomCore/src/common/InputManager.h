#pragma once
#include "IRuntimeModule.h"
#include "PhMaths.h"


#define PHANTOM_MOUSE_LEFT	  0x00
#define PHANTOM_MOUSE_MIDDLE	  0x01
#define PHANTOM_MOUSE_RIGHT    0x02

#define PHANTOM_NO_CURSOR	  NULL

#define PHANTOM_MODIFIER_LEFT_CONTROL	BIT(0)
#define PHANTOM_MODIFIER_LEFT_ALT		BIT(1)
#define PHANTOM_MODIFIER_LEFT_SHIFT		BIT(2)
#define PHANTOM_MODIFIER_RIGHT_CONTROL	BIT(3)
#define PHANTOM_MODIFIER_RIGHT_ALT		BIT(4)
#define PHANTOM_MODIFIER_RIGHT_SHIFT		BIT(5)

#define PHANTOM_KEY_TAB			  0x09

#define PHANTOM_KEY_0			  0x30
#define PHANTOM_KEY_1			  0x31
#define PHANTOM_KEY_2			  0x32
#define PHANTOM_KEY_3			  0x33
#define PHANTOM_KEY_4			  0x34
#define PHANTOM_KEY_5			  0x35
#define PHANTOM_KEY_6			  0x36
#define PHANTOM_KEY_7			  0x37
#define PHANTOM_KEY_8			  0x38
#define PHANTOM_KEY_9			  0x39

#define PHANTOM_KEY_A			  0x41
#define PHANTOM_KEY_B			  0x42
#define PHANTOM_KEY_C			  0x43
#define PHANTOM_KEY_D			  0x44
#define PHANTOM_KEY_E			  0x45
#define PHANTOM_KEY_F			  0x46
#define PHANTOM_KEY_G			  0x47
#define PHANTOM_KEY_H			  0x48
#define PHANTOM_KEY_I			  0x49
#define PHANTOM_KEY_J			  0x4A
#define PHANTOM_KEY_K			  0x4B
#define PHANTOM_KEY_L			  0x4C
#define PHANTOM_KEY_M			  0x4D
#define PHANTOM_KEY_N			  0x4E
#define PHANTOM_KEY_O			  0x4F
#define PHANTOM_KEY_P			  0x50
#define PHANTOM_KEY_Q			  0x51
#define PHANTOM_KEY_R			  0x52
#define PHANTOM_KEY_S			  0x53
#define PHANTOM_KEY_T			  0x54
#define PHANTOM_KEY_U			  0x55
#define PHANTOM_KEY_V			  0x56
#define PHANTOM_KEY_W			  0x57
#define PHANTOM_KEY_X			  0x58
#define PHANTOM_KEY_Y			  0x59
#define PHANTOM_KEY_Z			  0x5A

#define PHANTOM_KEY_LBUTTON        0x01
#define PHANTOM_KEY_RBUTTON        0x02
#define PHANTOM_KEY_CANCEL         0x03
#define PHANTOM_KEY_MBUTTON        0x04

#define PHANTOM_KEY_ESCAPE         0x1B
#define PHANTOM_KEY_SHIFT          0x10
#define PHANTOM_KEY_CONTROL        0x11
#define PHANTOM_KEY_MENU           0x12
#define PHANTOM_KEY_ALT	          SP_KEY_MENU
#define PHANTOM_KEY_PAUSE          0x13
#define PHANTOM_KEY_CAPITAL        0x14

#define PHANTOM_KEY_SPACE          0x20
#define PHANTOM_KEY_PRIOR          0x21
#define PHANTOM_KEY_NEXT           0x22
#define PHANTOM_KEY_END            0x23
#define PHANTOM_KEY_HOME           0x24
#define PHANTOM_KEY_LEFT           0x25
#define PHANTOM_KEY_UP             0x26
#define PHANTOM_KEY_RIGHT          0x27
#define PHANTOM_KEY_DOWN           0x28
#define PHANTOM_KEY_SELECT         0x29
#define PHANTOM_KEY_PRINT          0x2A
#define PHANTOM_KEY_EXECUTE        0x2B
#define PHANTOM_KEY_SNAPSHOT       0x2C
#define PHANTOM_KEY_INSERT         0x2D
#define PHANTOM_KEY_DELETE         0x2E
#define PHANTOM_KEY_HELP           0x2F

#define PHANTOM_KEY_NUMPAD0        0x60
#define PHANTOM_KEY_NUMPAD1        0x61
#define PHANTOM_KEY_NUMPAD2        0x62
#define PHANTOM_KEY_NUMPAD3        0x63
#define PHANTOM_KEY_NUMPAD4        0x64
#define PHANTOM_KEY_NUMPAD5        0x65
#define PHANTOM_KEY_NUMPAD6        0x66
#define PHANTOM_KEY_NUMPAD7        0x67
#define PHANTOM_KEY_NUMPAD8        0x68
#define PHANTOM_KEY_NUMPAD9        0x69
#define PHANTOM_KEY_MULTIPLY       0x6A
#define PHANTOM_KEY_ADD            0x6B
#define PHANTOM_KEY_SEPARATOR      0x6C
#define PHANTOM_KEY_SUBTRACT       0x6D
#define PHANTOM_KEY_DECIMAL        0x6E
#define PHANTOM_KEY_DIVIDE         0x6F
#define PHANTOM_KEY_F1             0x70
#define PHANTOM_KEY_F2             0x71
#define PHANTOM_KEY_F3             0x72
#define PHANTOM_KEY_F4             0x73
#define PHANTOM_KEY_F5             0x74
#define PHANTOM_KEY_F6             0x75
#define PHANTOM_KEY_F7             0x76
#define PHANTOM_KEY_F8             0x77
#define PHANTOM_KEY_F9             0x78
#define PHANTOM_KEY_F10            0x79
#define PHANTOM_KEY_F11            0x7A
#define PHANTOM_KEY_F12            0x7B
#define PHANTOM_KEY_F13            0x7C
#define PHANTOM_KEY_F14            0x7D
#define PHANTOM_KEY_F15            0x7E
#define PHANTOM_KEY_F16            0x7F
#define PHANTOM_KEY_F17            0x80
#define PHANTOM_KEY_F18            0x81
#define PHANTOM_KEY_F19            0x82
#define PHANTOM_KEY_F20            0x83
#define PHANTOM_KEY_F21            0x84
#define PHANTOM_KEY_F22            0x85
#define PHANTOM_KEY_F23            0x86
#define PHANTOM_KEY_F24            0x87

#define PHANTOM_KEY_NUMLOCK        0x90
#define PHANTOM_KEY_SCROLL         0x91

#define PHANTOM_KEY_LSHIFT         0xA0
#define PHANTOM_KEY_RSHIFT         0xA1
#define PHANTOM_KEY_LCONTROL       0xA2
#define PHANTOM_KEY_RCONTROL       0xA3
#define PHANTOM_KEY_LMENU          0xA4
#define PHANTOM_KEY_RMENU          0xA5

namespace Phantom {

#define MAX_KEYS 1024

	class InputManager : implements IRuntimeModule
	{
	private:
		bool m_keyState[MAX_KEYS];
		maths::vec2 m_mousePosition;
	public:
		virtual int Init();
		virtual void Shutdown();
		virtual void Tick();

		void AsciiKeyDown(char keycode);
		void AsciiKeyUp(char keycode);

		bool IsKeyPressed(int keycode) const;

		// mouse handling
		void LeftMouseButtonDown(float x,float y);
		void LeftMouseButtonUp();
		void LeftMouseDrag(int newX, int newY);

		bool GetUpKeyPressed() { return m_keyState[PHANTOM_KEY_UP]; }
		bool GetDownKeyPressed() { return m_keyState[PHANTOM_KEY_DOWN]; }
		bool GetLeftKKeyPressed() { return m_keyState[PHANTOM_KEY_LEFT]; }
		bool GetRightKeyPressed() { return m_keyState[PHANTOM_KEY_RIGHT]; }



		//Deprecated
		void UpArrowKeyDown();
		void UpArrowKeyUp();
		void DownArrowKeyDown();
		void DownArrowKeyUp();
		void LeftArrowKeyDown();
		void LeftArrowKeyUp();
		void RightArrowKeyDown();
		void RightArrowKeyUp();
	protected:
	private:
		friend void KeyCallback(InputManager* inputManager, int flags, int key, uint32_t message);
	};

	extern InputManager* g_pInputManager;
}
