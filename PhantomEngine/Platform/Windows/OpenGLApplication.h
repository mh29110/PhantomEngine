#pragma once
#include "WindowsApplication.h"

namespace Phantom {
    class OpenGLApplication : public WindowsApplication {
    public:
        using WindowsApplication::WindowsApplication;

        int Init() override;
        void Shutdown() override;
        void Tick() override;

        void CreateMainWindow() override;

    private:
        HDC   m_hDC;
        HGLRC m_RenderContext;
        int   m_nPixelFormat;
	    PIXELFORMATDESCRIPTOR m_pfd;
    };
}
