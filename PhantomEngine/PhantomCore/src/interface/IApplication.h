#pragma once
#include "IRuntimeModule.h"
#include "common/GfxConfiguration.h"

namespace Phantom {
    IInterface IApplication : implements IRuntimeModule
    {
    public:
        virtual int Init() = 0;
        virtual void Shutdown() = 0;
        // One cycle of the main loop
        virtual void Tick() = 0;

        virtual bool IsQuit() = 0;

        virtual GfxConfiguration& GetConfiguration() = 0;

        virtual void CreateMainWindow() = 0;
        virtual void* GetMainWindowHandler() = 0;
    };
}