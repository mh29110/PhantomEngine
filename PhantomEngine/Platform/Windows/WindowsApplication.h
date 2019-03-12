#pragma once
// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include "BaseApplication.h"
namespace Phantom {
    class WindowsApplication : public BaseApplication
    {
    public:
		using BaseApplication::BaseApplication;

		void Finalize() override;
		// One cycle of the main loop
		void Tick() override;

		void* GetMainWindowHandler() override { return m_hWnd; };
		void CreateMainWindow() override;
    private:
        // the WindowProc function prototype
        static LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);
	protected:
		virtual void OnDraw() ;

    protected:
		HWND m_hWnd;//´°¿Ú¾ä±ú
		HDC  m_hDc;//´°¿ÚÖÐµÄ»­°å»­²¼¾ä±ú
		bool m_bInDrag = false;
		int  m_iPreviousX = 0;
		int  m_iPreviousY = 0;
    };
}

