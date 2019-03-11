#include <stdio.h>
#include "interface/IApplication.h"
#include "GraphicsManager.h"
#include "AssetLoadManager.h"
// #include "MemoryManager.h"
#include "parser/BMPParser.h"
#include "Image.h"
#ifdef OS_WINDOWS
	#include "D2d/D2dGraphicsManager.h"
#endif
#include "Timer.h"

using namespace Phantom;
using namespace std;

namespace Phantom {
	extern IApplication*    g_pApp;
	extern AssetLoadManager* g_pLoadMgr;
    //extern MemoryManager*   g_pMemoryManager;
    extern GraphicsManager* g_pGraphicsManager;
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
	if ((ret = g_pLoadMgr->Initialize()) != 0) {
		cerr << "Failed. err =  g_pLoadMgr initialize failed , will exit now." << ret;
		return ret;
	}
	if ((ret = g_pGraphicsManager->Initialize()) != 0) {
		printf("Graphics Manager Initialize failed, will exit now.");
		return ret;
	}
#ifdef OS_WINDOWS
	Buffer bmpdata = g_pLoadMgr->SyncOpenAndReadBinary("Resources/texture/bmp.bmp");
	BmpParser bp;
	Image  image = bp.Parse(bmpdata);
	Image m_Image[1];
	m_Image[0] = image;
	static_cast<D2dGraphicsManager*> (g_pGraphicsManager)->DrawBitmap(m_Image, 0);
#endif

	Timer timer;
	float timeCount = 0.0f;
	unsigned int  frames = 0;
	while (!g_pApp->IsQuit()) {
		g_pApp->Tick();
		float now = timer.ElapsedMillis();
        // g_pMemoryManager->Tick();
        g_pGraphicsManager->Tick();
		g_pLoadMgr->Tick();
#ifdef OS_WINDOWS		
		static_cast<D2dGraphicsManager*> (g_pGraphicsManager)->DrawBitmap(m_Image, 0);
#endif
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
	g_pLoadMgr->Finalize();

	return 0;
}
