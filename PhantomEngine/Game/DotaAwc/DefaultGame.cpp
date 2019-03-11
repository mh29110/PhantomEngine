#include "GraphicsManager.h"
#ifdef OS_MACOS
	#include "CocoaMetalApplication.h"
#endif
#ifdef OS_WINDOWS
	#include "WindowsApplication.h"
    #include "D2d/D2dGraphicsManager.h"
	//#include "D3d/D3d12GraphicsManager.h"
#endif
#include "GfxConfiguration.h"
#include "IApplication.h"
#include "AssetLoadManager.h"
// #include "MemoryManager.h"
 

namespace Phantom {
	GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, (" Windows !"));
#if defined(OS_MACOS)
	IApplication*    g_pApp = static_cast<IApplication*>(new CocoaMetalApplication(config));
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new GraphicsManager);
#else
	IApplication*    g_pApp = static_cast<IApplication*>(new WindowsApplication(config));
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new D2dGraphicsManager);
#endif
	AssetLoadManager* g_pLoadMgr = static_cast<AssetLoadManager*>(new AssetLoadManager);
	// MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);
}