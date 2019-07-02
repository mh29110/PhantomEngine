#include "WindowsApplication.h"
#include <tchar.h>
#include "common/InputManager.h"
#include "common/GraphicsManager.h"

using namespace Phantom;
void Phantom::KeyCallback(InputManager * inputManager, int flags, int key, uint32_t message)
{
	bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
	inputManager->m_keyState[key] = pressed;

}
void  Phantom::WindowsApplication::CreateMainWindow()
{
	// get the HINSTANCE of the Console Program
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	const char g_szClassName[] = "myWindowClass";
	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _T(g_szClassName);

	// register the window class
	RegisterClassEx(&wc);
	//https://github.com/365082218/W4D/blob/master/W4d/W4d.cpp È«ÆÁÊ¾Àý
	int height_adjust = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));
	int width_adjust = (GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER));

	// create the window and use the result as the handle
	m_hWnd = CreateWindowEx(0,
		_T(g_szClassName),      // name of the window class
		m_Config.appName,                 // title of the window
		WS_OVERLAPPEDWINDOW,              // window style
		CW_USEDEFAULT,                    // x-position of the window
		CW_USEDEFAULT,                    // y-position of the window
		m_Config.screenWidth + width_adjust,              // width of the window
		m_Config.screenHeight + height_adjust,            // height of the window
		NULL,                             // we have no parent window, NULL
		NULL,                             // we aren't using menus, NULL
		hInstance,                        // application handle
		this);                            // pass pointer to current object

	m_hDc = GetDC(m_hWnd);

	// display the window on the screen
	ShowWindow(m_hWnd, SW_SHOW);
}

void Phantom::WindowsApplication::Shutdown()
{
	ReleaseDC(m_hWnd, m_hDc);

	BaseApplication::Shutdown();
}

void Phantom::WindowsApplication::Tick()
{
	BaseApplication::Tick();
    // this struct holds Windows event messages
    MSG msg;

    // we use PeekMessage instead of GetMessage here
    // because we should not block the thread at anywhere
    // except the engine execution driver module 
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg); 
    }
}

// this is the main message handler for the program
LRESULT CALLBACK Phantom::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	WindowsApplication* pThis;
	if (message == WM_NCCREATE)
	{
		pThis = static_cast<WindowsApplication*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	}
	else
	{
		pThis = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	// sort through and find what code to run for the message given
	switch (message)
	{
		/*case WM_CHAR:
		{
			g_pInputManager->AsciiKeyDown(static_cast<char>(wParam));
		}
		break;*/
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	{
		KeyCallback(g_pInputManager,lParam, wParam, message);
		break;
	}
		
	case WM_SIZE: 
	{
		//MoveWindow(hwndEdit, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
		int32_t w = LOWORD(lParam);
		int32_t h = HIWORD(lParam);
		if (g_pGraphicsManager->Inited)
		{
			g_pGraphicsManager->resize(w, h);
		}
	}
	break;
	
	case WM_LBUTTONDOWN:
	{
		pThis->m_bInDrag = true;
		pThis->m_iPreviousX = GET_X_LPARAM(lParam);
		pThis->m_iPreviousY = GET_Y_LPARAM(lParam);
		g_pInputManager->LeftMouseButtonDown(pThis->m_iPreviousX,pThis->m_iPreviousY);
	}
	break;
	case WM_LBUTTONUP:
	{
		g_pInputManager->LeftMouseButtonUp();
		pThis->m_bInDrag = false;
	}
	break;
	case WM_PAINT:
	{
		pThis->OnDraw();
	}
	break;
	case WM_MOUSEMOVE:
		if (pThis->m_bInDrag) {
			int pos_x = GET_X_LPARAM(lParam);
			int pos_y = GET_Y_LPARAM(lParam);
			//delta    g_pInputManager->LeftMouseDrag(pos_x - pThis->m_iPreviousX, pos_y - pThis->m_iPreviousY);
			g_pInputManager->LeftMouseDrag(pos_x, pos_y);
		}
		break;
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		m_bQuit = true;
	}
	break;
	default:
		// Handle any messages the switch statement didn't
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}
	return result;

}

void Phantom::WindowsApplication::OnDraw()
{
	//cpu draw
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hWnd, &ps);
	RECT rec = { 20, 20, 60, 80 };
	HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);

	FillRect(hdc, &rec, brush);

	EndPaint(m_hWnd, &ps);
}


