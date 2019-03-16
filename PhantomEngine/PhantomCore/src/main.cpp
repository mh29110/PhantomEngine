#include <stdio.h>
#include "interface/IApplication.h"
#include "GraphicsManager.h"
#include "AssetLoadManager.h"
#include "BehaviourManager.h"
#include "SceneManager.h"
#include "InputManager.h"
// #include "MemoryManager.h"
#include "Timer.h"

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

	if ((ret = g_pApp->Initialize()) != 0) {
		printf("App Initialize failed, will exit now.");
		return ret;
	}
	// create the main window
	g_pApp->CreateMainWindow();
	// if ((ret = g_pMemoryManager->Initialize()) != 0) {
	// 	printf("Memory Manager Initialize failed, will exit now.");
	// 	return ret;
	// }
	if ((ret = g_pAssetLoader->Initialize()) != 0) {
		cerr << "Failed. err =  g_pAssetLoader initialize failed , will exit now." << ret;
		return ret;
	}
	if ((ret = g_pSceneManager->Initialize()) != 0) {
		cerr << "Failed. err =  g_pSceneManager initialize failed , will exit now." << ret;
		return ret;
	}
	if ((ret = g_pGraphicsManager->Initialize()) != 0) {
		printf("Graphics Manager Initialize failed, will exit now.");
		return ret;
	}
	if ((ret = g_pBehaviourManager->Initialize()) != 0) {
		printf("g_pBehaviourManager  Initialize failed, will exit now.");
		return ret;
	}
	if ((ret = g_pInputManager->Initialize()) != 0) {
		printf("g_pInputManager  Initialize failed, will exit now.");
		return ret;
	}

	Timer timer;
	float timeCount = 0.0f;
	unsigned int  frames = 0;
	while (!g_pApp->IsQuit()) {
		g_pApp->Tick();
		float now = timer.ElapsedMillis();
        // g_pMemoryManager->Tick();
		g_pAssetLoader->Tick();
		g_pSceneManager->Tick();
        g_pGraphicsManager->Tick();
		g_pBehaviourManager->Tick();
		g_pInputManager->Tick();

		frames++;
		if (timer.Elapsed() - timeCount > 1.0f)
		{
			timeCount += 1.0f;
			std::cout << "frames === " << frames << std::endl;
			frames = 0;
		}
	}

    g_pGraphicsManager->Finalize();
    // g_pMemoryManager->Finalize();
	g_pApp->Finalize();
	g_pAssetLoader->Finalize();
	return 0;
}
