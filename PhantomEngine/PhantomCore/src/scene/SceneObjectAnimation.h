#pragma once

#include <vector>
#include <memory>
#include "SceneBaseObject.h"
#include "ability/IAnimatable.h"
#include "SceneObjectTrack.h"


namespace Phantom {
	class SceneObjectAnimationClip : public SceneBaseObject,public IAnimatable<float>
	{
	public:
		SceneObjectAnimationClip() = delete;
		SceneObjectAnimationClip(int idx) : SceneBaseObject(SceneObjectType::kSceneObjectTypeAnimationClip),
											m_nIndex(idx){}

		void AddTrack(std::shared_ptr<SceneObjectTrack>& track);
		void Update(const float deltaTime) final;
	private:
		int m_nIndex = 0;
		std::vector<std::shared_ptr<SceneObjectTrack>>  m_tracks;
	};
}
