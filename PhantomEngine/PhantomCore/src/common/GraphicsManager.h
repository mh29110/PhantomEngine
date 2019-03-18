#pragma once
#include "IRuntimeModule.h"
#include "mat4.h"
#include "vector.h"
#include "camera.h"
#include "GfxStruct.h"


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

		virtual void resize(float width, float height) {};

		bool Inited = false;
	private:
		void CalculateCameraMatrix();

		void UpdateConstants();
	protected:
		Frame  m_Frame;
	};
	extern GraphicsManager* g_pGraphicsManager;
}
