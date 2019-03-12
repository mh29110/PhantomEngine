#include <iostream>
#include "InputManager.h"
#include "GraphicsManager.h"

using namespace Phantom;
using namespace std;

int InputManager::Initialize()
{
    return 0;
}

void InputManager::Finalize()
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
}

void InputManager::UpArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Up Arrow Key Up!" << endl;
#endif
    m_bUpKeyPressed = false;
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
}

void InputManager::DownArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Down Arrow Key Up!" << endl;
#endif
    m_bDownKeyPressed = false;
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
}

void InputManager::LeftArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Left Arrow Key Up!" << endl;
#endif
    m_bLeftKeyPressed = false;
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
}

void InputManager::RightArrowKeyUp()
{
#ifdef _DEBUG
    cerr << "[InputManager] Right Arrow Key Up!" << endl;
#endif
    m_bRightKeyPressed = false;
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
}
