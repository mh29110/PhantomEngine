#pragma once
// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include "BaseApplication.h"
#include "GraphicsManager.h"
namespace Phantom {
    class WindowsApplication : public BaseApplication
    {
    public:
        WindowsApplication(GfxConfiguration& config)
            : BaseApplication(config) {};

        virtual int Initialize();
        virtual void Finalize();
        // One cycle of the main loop
        virtual void Tick();

        inline HWND GetMainWindow() const { return m_hWnd; };

    private:
        // the WindowProc function prototype
        static LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

    private:
        HWND m_hWnd;
    };
}

namespace Phantom {
	GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, ("Game Engine From Scratch (Windows)"));
	IApplication* g_pApp = static_cast<IApplication*>(new WindowsApplication(config));
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new GraphicsManager);
	// MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);

}