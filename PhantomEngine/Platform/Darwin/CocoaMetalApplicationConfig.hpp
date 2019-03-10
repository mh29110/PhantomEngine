#include "CocoaMetalApplication.h"

namespace Phantom {
    extern GfxConfiguration config;
    IApplication* g_pApp                = static_cast<IApplication*>(new CocoaMetalApplication(config));
}
