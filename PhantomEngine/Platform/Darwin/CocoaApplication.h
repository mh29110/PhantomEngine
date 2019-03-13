#pragma once 
#include "Portable.h"
#include "BaseApplication.h"

OBJC_CLASS(NSWindow);

namespace Phantom {
    class CocoaApplication : public BaseApplication
    {
    public:
        using BaseApplication::BaseApplication;

        void Finalize() override;
        // One cycle of the main loop
        void Tick() override;

        void* GetMainWindowHandler() override;
        void CreateMainWindow() override;

    protected:
        NSWindow* m_pWindow;
    };
}

