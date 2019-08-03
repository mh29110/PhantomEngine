#pragma once
#ifdef _DEBUG
#include "interface/IRuntimeModule.h"

namespace Phantom {
    class DebugManager : implements IRuntimeModule
    {
    public:
        int Init();
        void Shutdown();
        void Tick();

        void ToggleDebugInfo();

        void DrawDebugInfo();

    protected:
        void DrawAxis();

        bool m_bDrawDebugInfo = false;
    };

    extern DebugManager* g_pDebugManager;
}

#endif