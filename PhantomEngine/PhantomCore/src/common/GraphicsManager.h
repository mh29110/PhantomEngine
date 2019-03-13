#pragma once
#include "IRuntimeModule.h"


namespace Phantom {
	class GraphicsManager: implements IRuntimeModule
	{
	public:
		virtual ~GraphicsManager() {};

		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();

		virtual void Clear() = 0;
		virtual void Draw() = 0;
	};
	extern GraphicsManager* g_pGraphicsManager;
}
