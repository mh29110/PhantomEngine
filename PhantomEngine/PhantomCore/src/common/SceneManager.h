#pragma once
#include <memory>
#include "scene/Scene.h"
#include "interface/IRuntimeModule.h"

namespace Phantom {
	class SceneManager : implements IRuntimeModule
	{
	public:
		virtual ~SceneManager() {};

		virtual int Init();
		virtual void Shutdown();

		virtual void Tick();

		const Scene& GetSceneForRendering();

		bool LoadScene(const std::string&  sceneName = "Resources/Scene/c8.ogex");

		void SwitchScene(const std::string& sceneName);
	protected:
		std::shared_ptr<Scene>  m_pScene;
		
	};
	extern SceneManager* g_pSceneManager;
}
