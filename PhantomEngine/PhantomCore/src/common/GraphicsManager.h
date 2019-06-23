#pragma once
#include "IRuntimeModule.h"
#include "mat4.h"
#include "vector.h"
#include "camera.h"
#include "GfxStruct.h"
#include "textCore/FontEngine.h"

namespace Phantom {
	
	enum Shader_Type
	{
		Common_Shader = 0,
		SkyBox_Shader,
		ShadowMap_Shader
	};
	class GraphicsManager: implements IRuntimeModule
	{
	public:
		virtual ~GraphicsManager() {};

		virtual int Init();
		virtual void Shutdown();

		virtual void Tick();
		virtual void Clear() = 0;
		virtual void Draw() = 0;
		virtual void DrawString() = 0;

		// sky box
		virtual void DrawSkyBox() {}

		virtual void resize(int32_t width, int32_t height) {};

		bool Inited = false;
	private:
		void CalculateCameraMatrix();
		void CalculateLights();

		void UpdateConstants();

		virtual void BindShaderByType(Shader_Type st) = 0;

		virtual void SetPerFrameConstants(const ContextPerFrame& context) {}
		virtual void SetPerFrameLight() {}
		virtual void SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches) {}
	protected:
		Frame  m_Frame;
		TextCore::FontEngine fontEngine;
	};
	extern GraphicsManager* g_pGraphicsManager;
}
