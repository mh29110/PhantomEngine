#pragma once
#include <unordered_map>
#include "interface/IRuntimeModule.h"
#include "maths/mat4.h"
#include "maths/vector.h"
#include "scene/camera.h"
#include "scene/Scene.h"
#include "graphics/GfxStruct.h"
#include "graphics/textCore/FontEngine.h"
#include "graphics/gui/GuiCommon.h"
#include "eventQueue/EventManager.h"

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
	protected:
		virtual void EnterScene(const Scene& scene);
		virtual void PurgeCurScene();

	private:
		void CalculateCameraMatrix();
		void CalculateLights();

		void CalculateSkeletonSkin();

		void UpdateConstants();

		virtual void BindShaderByType(Shader_Type st) = 0;

		virtual void SetPerFrameConstants(const ContextPerFrame& context) {}
		virtual void SetPerFrameLight() {}
		virtual void SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches) {}

		
	protected:
		Frame  m_Frame;
		TextCore::FontEngine fontEngine;
		std::unordered_map<char , GUI::GuiDisplayUnit> m_GuiUnitMap;


		EventQueue::ClassBasedEventHandler<GraphicsManager> * evthandler;
		int OnLoadSceneCompleted(EventQueue::Event * evt);
	};
	extern GraphicsManager* g_pGraphicsManager;
}
