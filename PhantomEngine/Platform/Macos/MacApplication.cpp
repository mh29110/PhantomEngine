#include "BaseApplication.h"
#include "GraphicsManager.h"
// #include "MemoryManager.h"
 

namespace Phantom {
    GfxConfiguration config;
    IApplication*    g_pApp             = static_cast<IApplication*>(new BaseApplication(config));
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new GraphicsManager);
    // MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);
}