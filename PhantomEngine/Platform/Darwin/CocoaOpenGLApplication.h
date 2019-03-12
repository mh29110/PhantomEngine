#pragma once
#include "CocoaApplication.h"

namespace Phantom {
    class CocoaOpenGLApplication : public CocoaApplication {
    public:
        CocoaOpenGLApplication(GfxConfiguration& config)
            : CocoaApplication(config) {};

        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();
    };
}

