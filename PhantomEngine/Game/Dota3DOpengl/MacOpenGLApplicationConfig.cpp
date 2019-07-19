#include "projectConfig.h"
#ifdef OS_WINDOWS
	#include "OpenGLApplication.h"
#endif

#ifdef OS_MACOS
	#include "CocoaOpenGLApplication.h"
	// #include "CocoaMetalApplication.h"
#endif
#include "OpenGL/OpenGLGraphicsManager.h"
#include "common/AssetLoadManager.h"
#include "common/SceneManager.h"
#include "scene/SceneHeaders.h"
#include <unordered_map>
#include "common/GfxConfiguration.h"
#include "interface/IApplication.h"
#include "common/BehaviourManager.h"
#include "common/InputManager.h"

namespace Phantom {
	//ÅäÖÃ³ÌÐò¼¯ÃüÃû¿Õ¼äÄÚ¹ÜÀíÆ÷µÄÈ«¾Ö±äÁ¿
    GfxConfiguration config(8, 8, 8, 8, 24, 8, 0, 960, 540, "Game  (Windows/mac OpenGL)");

    IApplication* g_pApp   = static_cast<IApplication*>(new CocoaOpenGLApplication(config));

    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new OpenGLGraphicsManager);
    AssetLoadManager*     g_pAssetLoader     = static_cast<AssetLoadManager*>(new AssetLoadManager);
	SceneManager*     g_pSceneManager     = static_cast<SceneManager*>(new SceneManager);
    InputManager* g_pInputManager = static_cast<InputManager* >(new InputManager);

}

