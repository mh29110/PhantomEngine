#include "projectConfig.h"
#ifdef OS_WINDOWS
	#include "OpenGLApplication.h"
#endif

#ifdef OS_MACOS
	#include "CocoaOpenGLApplication.h"
	// #include "CocoaMetalApplication.h"
#endif
#include "OpenGL/OpenGLGraphicsManager.h"
#include "AssetLoadManager.h"
#include "SceneManager.h"
#include "SceneBaseObject.h"
#include <unordered_map>
#include "GfxConfiguration.h"
#include "IApplication.h"
#include "BehaviourManager.h"
#include "InputManager.h"

namespace Phantom {
	//ÅäÖÃ³ÌÐò¼¯ÃüÃû¿Õ¼äÄÚ¹ÜÀíÆ÷µÄÈ«¾Ö±äÁ¿
    GfxConfiguration config(8, 8, 8, 8, 24, 8, 0, 960, 540, "Game  (Windows/mac OpenGL)");

    IApplication* g_pApp   = static_cast<IApplication*>(new CocoaOpenGLApplication(config));

    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new OpenGLGraphicsManager);
    AssetLoadManager*     g_pAssetLoader     = static_cast<AssetLoadManager*>(new AssetLoadManager);
	SceneManager*     g_pSceneManager     = static_cast<SceneManager*>(new SceneManager);
    InputManager* g_pInputManager = static_cast<InputManager* >(new InputManager);

}

