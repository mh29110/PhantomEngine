#pragma once
#include "IRuntimeModule.h"
#include "mat4.h"
#include "vector.h"
#include "camera.h"


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
	private:
		void CalculateCameraMatrix();

		void UpdateConstants();
	protected:
	
	};
	extern GraphicsManager* g_pGraphicsManager;
}
