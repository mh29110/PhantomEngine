#include <iostream>
#include "InputManager.h"
#include "GraphicsManager.h"
#include "BehaviourManager.h"

using namespace Phantom;
using namespace std;

int InputManager::Init()
{
	for (int i = 0; i < MAX_KEYS; i++)
	{
		m_keyState[i] = false;
	}
    return 0;
}

bool InputManager::IsKeyPressed(int keycode) const
{
	if (keycode >= MAX_KEYS)
		return false;//todo assert

	return m_keyState[keycode];
}

void InputManager::Shutdown()
{
}

void InputManager::Tick()
{
	for (int i = 0; i < MAX_KEYS; i++)
	{
	
	}
}


void InputManager::AsciiKeyDown(char keycode)
{

}

void InputManager::AsciiKeyUp(char keycode)
{
#
}

void InputManager::LeftMouseButtonDown()
{
#ifdef _DEBUG
    cerr << "[InputManager] Left Mouse Button Down!" << endl;
#endif
}

void InputManager::LeftMouseButtonUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Left Mouse Button Up!" << endl;
#endif
}

void InputManager::LeftMouseDrag(int deltaX, int deltaY)
{
#ifdef _DEBUG
    cerr << "[InputManager] Left Mouse Dragged! (" 
        << deltaX << ","
        << deltaY << ")"
        << endl;
#endif
	g_pBehaviourManager->LeftMouseDrag( deltaX, deltaY);
}



//deprecated -------------------------------------------------------------------------
void InputManager::UpArrowKeyDown()
{
	if (!m_keyState[PHANTOM_KEY_UP])
	{
		m_keyState[PHANTOM_KEY_UP] = true;
	}
	//g_pBehaviourManager->OnUpKeyDown();
}

void InputManager::UpArrowKeyUp()
{
	m_keyState[PHANTOM_KEY_UP] = false;
	//g_pBehaviourManager->OnUpKeyUp();
}

void InputManager::DownArrowKeyDown()
{
	if (!m_keyState[PHANTOM_KEY_DOWN])
	{
		m_keyState[PHANTOM_KEY_DOWN] = true;
	}
	//g_pBehaviourManager->OnDownKeyDown();
}

void InputManager::DownArrowKeyUp()
{
	m_keyState[PHANTOM_KEY_DOWN] = false;
	//g_pBehaviourManager->OnDownKeyUp();
}

void InputManager::LeftArrowKeyDown()
{
	if (!m_keyState[PHANTOM_KEY_LEFT])
	{
		m_keyState[PHANTOM_KEY_LEFT] = true;
	}
	//g_pBehaviourManager->OnLeftKeyDown();
}

void InputManager::LeftArrowKeyUp()
{
	m_keyState[PHANTOM_KEY_LEFT] = false;
	//g_pBehaviourManager->OnLeftKeyUp();
}

void InputManager::RightArrowKeyDown()
{
	if (!m_keyState[PHANTOM_KEY_RIGHT])
	{
		m_keyState[PHANTOM_KEY_RIGHT] = true;
	}
	//g_pBehaviourManager->OnRightKeyDown();
}

void InputManager::RightArrowKeyUp()
{
	m_keyState[PHANTOM_KEY_RIGHT] = false;
	//g_pBehaviourManager->OnRightKeyUp();
}