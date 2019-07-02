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
	protected:
		std::shared_ptr<Scene>  m_pScene;
		bool LoadScene();
	};
	extern SceneManager* g_pSceneManager;
}
