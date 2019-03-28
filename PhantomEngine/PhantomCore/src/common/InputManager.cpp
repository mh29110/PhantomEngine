#include <iostream>
#include "InputManager.h"
#include "GraphicsManager.h"
#include "BehaviourManager.h"

using namespace Phantom;
using namespace std;

int InputManager::Init()
{
    return 0;
}

void InputManager::Shutdown()
{
}

void InputManager::Tick()
{
}

void InputManager::UpArrowKeyDown()
{
#ifdef _DEBUG
    cerr << "[InputManager] Up Arrow Key Down!" << endl;
#endif
    if (!m_bUpKeyPressed)
    {
        m_bUpKeyPressed = true;
    }
	g_pBehaviourManager->OnUpKeyDown();
}

void InputManager::UpArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Up Arrow Key Up!" << endl;
#endif
    m_bUpKeyPressed = false;
	g_pBehaviourManager->OnUpKeyUp();
}

void InputManager::DownArrowKeyDown()
{
#ifdef _DEBUG
    cerr << "[InputManager] Down Arrow Key Down!" << endl;
#endif
    if (!m_bDownKeyPressed)
    {
        m_bDownKeyPressed = true;
    }
	g_pBehaviourManager->OnDownKeyDown();
}

void InputManager::DownArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Down Arrow Key Up!" << endl;
#endif
    m_bDownKeyPressed = false;
	g_pBehaviourManager->OnDownKeyUp();
}

void InputManager::LeftArrowKeyDown()
{
#ifdef _DEBUG
    cerr << "[InputManager] Left Arrow Key Down!" << endl;
#endif
    if (!m_bLeftKeyPressed)
    {
        m_bLeftKeyPressed = true;
    }
	g_pBehaviourManager->OnLeftKeyDown();
}

void InputManager::LeftArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Left Arrow Key Up!" << endl;
#endif
    m_bLeftKeyPressed = false;
	g_pBehaviourManager->OnLeftKeyUp();
}

void InputManager::RightArrowKeyDown()
{
#ifdef _DEBUG
    cerr << "[InputManager] Right Arrow Key Down!" << endl;
#endif
    if(!m_bRightKeyPressed)
    {
        m_bRightKeyPressed = true;
    }
	g_pBehaviourManager->OnRightKeyDown();
}

void InputManager::RightArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Right Arrow Key Up!" << endl;
#endif
    m_bRightKeyPressed = false;
	g_pBehaviourManager->OnRightKeyUp();
}

void InputManager::AsciiKeyDown(char keycode)
{
#ifdef _DEBUG
    cerr << "[InputManager] ASCII Key Down! (" << keycode << ")" << endl;
#endif
    switch (keycode)
    {
        case 'd':
            break;
        case 'r':
            break;
        case 'u':
            break;
        default:
            cerr << "[InputManager] unhandled key." << endl;
    }
}

void InputManager::AsciiKeyUp(char keycode)
{
#ifdef _DEBUG
    cerr << "[InputManager] ASCII Key Up! (" << keycode << ")" << endl;
#endif
    switch (keycode)
    {
        case 'd':
            break;
        case 'r':
            break;
        case 'u':
            break;
        default:
            cerr << "[InputManager] unhandled key." << endl;
    }
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
