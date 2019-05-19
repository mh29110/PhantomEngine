#pragma once
#include "CocoaApplication.h"
#ifdef __OBJC__
#include "GLView.h"
#endif

namespace Phantom {
    class CocoaOpenGLApplication : public CocoaApplication {
    public:
        CocoaOpenGLApplication(GfxConfiguration& config)
            : CocoaApplication(config) {};

        virtual int Init();
        virtual void Shutdown();
        virtual void Tick();

    protected:
        virtual void OnDraw();

    private:
#ifdef __OBJC__
        //GLView* m_pGlView;
#endif
    };
}

