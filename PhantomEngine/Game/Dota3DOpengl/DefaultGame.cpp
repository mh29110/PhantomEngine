#include "GraphicsManager.h"
#ifdef OS_MACOS
	#include "CocoaMetalApplication.h"
#endif
#ifdef OS_WINDOWS
	#include "WindowsApplication.h"
#endif
#include "OpenGL/OpenGLGraphicsManager.h"
#include "OpenGLApplication.h"
#include "GfxConfiguration.h"
#include "IApplication.h"
#include "AssetLoadManager.h"
#include "InputManager.h"
#include "Image.h"
#include "BmpParser.h"
#include "utility.hpp"
// #include "MemoryManager.h"
 
namespace Phantom {
	class TestApplication : public OpenGLApplication
	{
	public:
		using OpenGLApplication::OpenGLApplication;

		virtual int Initialize();

		virtual void OnDraw() {}

	private:
		Image m_Image[2];
	};
}


namespace Phantom {
	GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, (" Windows !"));
#if defined(OS_MACOS)
	IApplication*    g_pApp = static_cast<IApplication*>(new CocoaMetalApplication(config));
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new GraphicsManager);
#else
	IApplication*    g_pApp = static_cast<IApplication*>(new TestApplication(config));
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new OpenGLGraphicsManager);
#endif
	AssetLoadManager* g_pAssetLoader = static_cast<AssetLoadManager*>(new AssetLoadManager);
	InputManager*    g_pInputManager    = static_cast<InputManager*>(new InputManager);
	// MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);
}

int Phantom::TestApplication::Initialize()
{
	int result;

	result = WindowsApplication::Initialize();

	if (result == 0) {
		BmpParser   parser;
		Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary("Resources/texture/bmp.bmp");

		m_Image[0] = parser.Parse(buf);

		buf = g_pAssetLoader->SyncOpenAndReadBinary("Resources/texture/bmp.bmp");

		m_Image[1] = parser.Parse(buf);
	}

	return result;
}
