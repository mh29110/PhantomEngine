#include "GraphicsManager.h"
#ifdef OS_MACOS
	#include "CocoaMetalApplication.h"
#endif
#ifdef OS_WINDOWS
	#include "WindowsApplication.h"
#endif
#include "OpenGL/OpenGLGraphicsManager.h"
#include "CocoaMetalApplication.h"
#include "GfxConfiguration.h"
#include "IApplication.h"
#include "AssetLoadManager.h"
#include "InputManager.h"
#include "Image.h"
#include "BmpParser.h"
#include "utility.hpp"
// #include "MemoryManager.h"
 
// namespace Phantom {
// 	class TestApplication : public CocoaOpenGLApplication
// 	{
// 	public:
// 		using CocoaOpenGLApplication::CocoaOpenGLApplication;

// 		virtual int Initialize();

// 		virtual void OnDraw() {}

// 	private:
// 		Image m_Image[2];
// 	};
// }


namespace Phantom {
	InputManager*    g_pInputManager    = static_cast<InputManager*>(new InputManager);
}


// int Phantom::TestApplication::Initialize()
// {
// 	int result;

// 	result = CocoaOpenGLApplication::Initialize();

// 	if (result == 0) {
// 		BmpParser   parser;
// 		Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary("Resources/texture/bmp.bmp");

// 		m_Image[0] = parser.Parse(buf);

// 		buf = g_pAssetLoader->SyncOpenAndReadBinary("Resources/texture/bmp.bmp");

// 		m_Image[1] = parser.Parse(buf);
// 	}

// 	return result;
// }
