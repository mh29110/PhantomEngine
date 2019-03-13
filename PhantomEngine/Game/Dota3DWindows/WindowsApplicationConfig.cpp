#include "D3d/D3d12GraphicsManager.h"
#include "AssetLoadManager.h"
#include "GfxConfiguration.h"
#include "IApplication.h"
#include "WindowsApplication.h"
#include "SceneManager.h"

namespace Phantom {
    GfxConfiguration config(8, 8, 8, 8, 24, 8, 0, 960, 540, "Game  (Windows)");
	IApplication* g_pApp = static_cast<IApplication*>(new WindowsApplication(config));
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new D3d12GraphicsManager);
	AssetLoadManager*     g_pAssetLoader = static_cast<AssetLoadManager*>(new AssetLoadManager);
	SceneManager*     g_pSceneManager = static_cast<SceneManager*>(new SceneManager);
}

