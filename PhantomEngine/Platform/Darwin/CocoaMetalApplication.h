#pragma once
#include "CocoaApplication.h"

namespace Phantom {
    class CocoaMetalApplication : public CocoaApplication {
    public:
        CocoaMetalApplication(GfxConfiguration& config)
            : CocoaApplication(config) {};

        void Tick() override;

        void CreateMainWindow() override;
    };
}
