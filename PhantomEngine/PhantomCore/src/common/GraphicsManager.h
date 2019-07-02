#pragma once
#include "interface/IRuntimeModule.h"
#include "maths/mat4.h"
#include "maths/vector.h"
#include "scene/camera.h"
#include "graphics/GfxStruct.h"
#include "graphics/textCore/FontEngine.h"
#include "graphics/gui/GuiCommon.h"
#include <unordered_map>

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
		virtual void DrawGUI() = 0;
		virtual void DrawString(GUI::GUIIndex idx, float posx, float posy, std::string content);

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
		std::unordered_map<char , GUI::GuiDisplayUnit> m_GuiUnitMap;
	};
	extern GraphicsManager* g_pGraphicsManager;
}
