#include "OpenGLApplication.h"
#include "OpenGL/OpenGLGraphicsManager.h"
#include "AssetLoadManager.h"
#include "SceneManager.h"
#include "SceneBaseObject.h"
#include <unordered_map>

namespace Phantom {
	//配置程序集命名空间内管理器的全局变量
    GfxConfiguration config(8, 8, 8, 8, 24, 8, 0, 960, 540, "Game  (Windows OpenGL)");
    IApplication* g_pApp                = static_cast<IApplication*>(new OpenGLApplication(config));
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new OpenGLGraphicsManager);
    AssetLoadManager*     g_pAssetLoader     = static_cast<AssetLoadManager*>(new AssetLoadManager);
	SceneManager*     g_pSceneManager     = static_cast<SceneManager*>(new SceneManager);

	std::unordered_map<std::string, std::shared_ptr<SceneBaseObject>> g_SceneObjects;
}

