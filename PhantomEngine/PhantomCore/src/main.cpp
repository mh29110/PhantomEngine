#include <stdio.h>
#include "interface/IApplication.h"
#include "common/GraphicsManager.h"
#include "common/AssetLoadManager.h"
#include "common/BehaviourManager.h"
#include "common/SceneManager.h"
#include "common/InputManager.h"
// #include "MemoryManager.h"
#include "common/AnimationManager.h"
#include "utils/Timer.h"

using namespace Phantom;
using namespace std;

namespace Phantom {
	extern IApplication*    g_pApp;
	extern AssetLoadManager* g_pAssetLoader;
    //extern MemoryManager*   g_pMemoryManager;
    extern GraphicsManager* g_pGraphicsManager;
    extern SceneManager* g_pSceneManager;
    extern BehaviourManager* g_pBehaviourManager;
    extern InputManager* g_pInputManager;
}


int main(int argc, char** argv) {


	int ret;

	if ((ret = g_pApp->Init()) != 0) {
		printf("App Init failed, will exit now.");
		return ret;
	}
	// create the main window
#ifndef  OS_MACOS
	g_pApp->CreateMainWindow();
#endif
	// if ((ret = g_pMemoryManager->Init()) != 0) {
	// 	printf("Memory Manager Init failed, will exit now.");
	// 	return ret;
	// }
	if ((ret = g_pAssetLoader->Init()) != 0) {
		cerr << "Failed. err =  g_pAssetLoader initialize failed , will exit now." << ret;
		return ret;
	}
	if ((ret = g_pSceneManager->Init()) != 0) {
		cerr << "Failed. err =  g_pSceneManager initialize failed , will exit now." << ret;
		return ret;
	}
	if ((ret = g_pGraphicsManager->Init()) != 0) {
		printf("Graphics Manager Init failed, will exit now.");
		return ret;
	}
	if ((ret = g_pBehaviourManager->Init()) != 0) {
		printf("g_pBehaviourManager  Init failed, will exit now.");
		return ret;
	}
	if ((ret = g_pInputManager->Init()) != 0) {
		printf("g_pInputManager  Init failed, will exit now.");
		return ret;
	}

	if ((ret = AnimationManager::GetInstance().Init()) != 0) {
		printf("AnimationManager  Init failed, will exit now.");
		return ret;
	}


	Timer timer;
	float secondCount = 0.0f;
	float lastFrameTime = 0.0f;
	unsigned int  frames = 0;
	while (!g_pApp->IsQuit()) {
		float now = timer.ElapsedMillis();
		float deltaTime = now - lastFrameTime;
		lastFrameTime = now;

		g_pApp->Tick();
		// g_pMemoryManager->Tick(deltaTime);
		g_pAssetLoader->Tick();
		g_pSceneManager->Tick();
		AnimationManager::GetInstance().Tick(deltaTime);
        g_pGraphicsManager->Tick();
		g_pBehaviourManager->Tick();
		g_pInputManager->Tick();


		frames++;
		if (timer.Elapsed() - secondCount > 1.0f)
		{
			secondCount += 1.0f;
			string str = std::to_string(frames);
			g_pGraphicsManager->DrawString(GUI::FrameGuiIdx,20, 400, "fps:" + str);
		/* 由于N卡默认开启自动同步，除非手动代码设置（或者显卡配置），最多60帧。 A卡默认关闭。*/
			frames = 0;
		}
	}

    // g_pMemoryManager->Shutdown();
	AnimationManager::GetInstance().Shutdown();
	g_pInputManager->Shutdown();
	g_pBehaviourManager->Shutdown();
    g_pGraphicsManager->Shutdown();
	g_pSceneManager->Shutdown();
	g_pAssetLoader->Shutdown();
	g_pApp->Shutdown();
	delete g_pInputManager;
	delete g_pBehaviourManager;
	delete g_pGraphicsManager;
	delete g_pSceneManager;
	delete g_pAssetLoader;
	delete g_pApp;
	return 0;
}
