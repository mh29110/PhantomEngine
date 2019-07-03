#include "SceneObjectAnimation.h"
using namespace Phantom;
void SceneObjectAnimationClip::AddTrack(std::shared_ptr<SceneObjectTrack>& track)
{
	m_tracks.push_back(track);
}

void SceneObjectAnimationClip::Update(const float deltaTime)
{
	for (auto track : m_tracks){
		track->Update(deltaTime);
	}
}
