#include "DefaultApplication.h"
#include "GraphicsManager.h"
#include "GfxConfiguration.h"
#include "IApplication.h"
// #include "MemoryManager.h"
 

namespace Phantom {
	GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, ("Game Engine From Scratch (Windows)"));

	DefaultApplication * app = new DefaultApplication(config);
	IApplication* g_pApp = static_cast<IApplication*>(app);
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new GraphicsManager);
	// MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);

}