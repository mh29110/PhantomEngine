#pragma once
#include "IRuntimeModule.h"
#include "src/common/GfxConfiguration.h"

namespace Phantom {
    Interface IApplication : implements IRuntimeModule
    {
    public:
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;
        // One cycle of the main loop
        virtual void Tick() = 0;

        virtual bool IsQuit() = 0;

        virtual GfxConfiguration& GetConfiguration() = 0;
    };
}