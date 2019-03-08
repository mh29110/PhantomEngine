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
		virtual void DrawSingleMesh();
	};

}
