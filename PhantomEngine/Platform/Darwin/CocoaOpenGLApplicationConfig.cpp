#include "CocoaOpenGLApplication.h"
#include "OpenGL/OpenGLGraphicsManager.h"
#include "AssetLoadManager.h"

namespace Phantom {
    GfxConfiguration config(8, 8, 8, 8, 24, 8, 0, 960, 540, "Game Engine From Scratch (MacOS Cocoa OpenGL)");
    IApplication* g_pApp                = static_cast<IApplication*>(new CocoaOpenGLApplication(config));
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new OpenGLGraphicsManager);
    AssetLoadManager*     g_pAssetLoader     = static_cast<AssetLoadManager*>(new AssetLoadManager);
}

