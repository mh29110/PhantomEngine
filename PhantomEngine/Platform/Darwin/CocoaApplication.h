#pragma once 
#include "common/Portable.h"
#include "common/BaseApplication.h"

OBJC_CLASS(NSWindow);

namespace Phantom {
    class CocoaApplication : public BaseApplication
    {
    public:
        using BaseApplication::BaseApplication;

        void Shutdown() override;
        // One cycle of the main loop
        void Tick() override;

        void* GetMainWindowHandler() override;
        void CreateMainWindow() override;

    protected:
        NSWindow* m_pWindow;
    };
}

