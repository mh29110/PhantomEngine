#include "GraphicsManager.h"
#include "GfxConfiguration.h"
#include "IApplication.h"
#if defined(OS_MACOS)
#include "CocoaApplication.h"
#else
#include "WindowsApplication.h"
#endif
// #include "MemoryManager.h"
 

namespace Phantom {
	GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, (" Windows !"));
#if defined(OS_MACOS)
	IApplication*    g_pApp = static_cast<IApplication*>(new CocoaApplication(config));
#else
	IApplication*    g_pApp = static_cast<IApplication*>(new WindowsApplication(config));
#endif
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new GraphicsManager);
	// MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);

}