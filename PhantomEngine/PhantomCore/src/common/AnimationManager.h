#pragma once

#include "interface/IRuntimeModule.h"
#include "common/Singleton.h"
#include "scene/SceneHeaders.h"
#include <list>

namespace Phantom {

	class AnimationManager : public Singleton<AnimationManager> //implements IRuntimeModule ? Tick改好多地方。
	{
	public:
		int Init();
		void Shutdown();
		void Tick(float delta);
		int AttachCurScene();

		void AddAnimationClip(std::shared_ptr<SceneObjectAnimationClip> clip);
		void ClearAnimationClips();
	public:
		AnimationManager() {};
		~AnimationManager() {};
	private:
		std::list<std::shared_ptr<SceneObjectAnimationClip>> m_AnimationClips;
		//bool m_bTimeLineStarted = false;
	};
}
