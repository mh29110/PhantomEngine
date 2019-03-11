#include "WindowsApplication.h"
#include <tchar.h>

using namespace Phantom;
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

void Phantom::WindowsApplication::Finalize()
{
	ReleaseDC(m_hWnd, m_hDc);

	BaseApplication::Finalize();
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
    switch(message)
    {
	case WM_PAINT:
	    {
            pThis->OnDraw();
	    } 
        break;

    case WM_KEYDOWN:
        {
            // we will replace this with input manager
            m_bQuit = true;
        } 
        break;

        // this message is read when the window is closed
    case WM_DESTROY:
        {
            // close the application entirely
            PostQuitMessage(0);
            m_bQuit = true;
            return 0;
        }
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}

void Phantom::WindowsApplication::OnDraw()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hWnd, &ps);
	RECT rec = { 20, 20, 60, 80 };
	HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);

	FillRect(hdc, &rec, brush);

	EndPaint(m_hWnd, &ps);
}


