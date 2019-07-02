#pragma once
#include "interface/IApplication.h"

namespace Phantom {
    class BaseApplication : implements IApplication
    {
    public:
        BaseApplication(GfxConfiguration& cfg);
        virtual int Init();
        virtual void Shutdown();
        // One cycle of the main loop
        virtual void Tick();

        virtual bool IsQuit();

        inline GfxConfiguration& GetConfiguration() { return m_Config; };

        virtual void CreateMainWindow() = 0;
        virtual void* GetMainWindowHandler() = 0;
    protected:
        virtual void OnDraw() {};

    protected:
        // Flag if need quit the main loop of the application
        static bool m_bQuit;
        GfxConfiguration m_Config;

    private:
        // hide the default construct to enforce a configuration
        BaseApplication(){};
    };
}
