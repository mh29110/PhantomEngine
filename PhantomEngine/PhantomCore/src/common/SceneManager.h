#pragma once
#include <memory>
#include "Scene.h"
#include "IRuntimeModule.h"

namespace Phantom {
	class SceneManager : implements IRuntimeModule
	{
	public:
		virtual ~SceneManager() {};

		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();

		const Scene& GetSceneForRendering();
	protected:
		std::shared_ptr<Scene>  m_pScene;
	};
	extern SceneManager* g_pSceneManager;
}
