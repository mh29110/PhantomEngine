#include "AnimationManager.h"
#include "scene/SceneHeaders.h"
#include "common/SceneManager.h"

using namespace Phantom;

int AnimationManager::Init()
{
	return 0;
}

void AnimationManager::Shutdown()
{
}

void AnimationManager::Tick(float delta)
{
    //OMG: accelerate by multiply the objects.
    static float pg = 0.0f;
    pg += (delta / 1000.0f);
    pg = pg > 18.0f ? 0.0f : pg;
    //printf("pg : %f \n", pg);
	for (auto clip : m_AnimationClips)
	{
		clip->Update(pg);
	}
}

int Phantom::AnimationManager::AttachCurScene()
{
	auto &scene = g_pSceneManager->GetSceneForRendering();
	for (auto node : scene.AnimationNodes)
	{
		auto pNode = node.lock();
		if (pNode) {
			const std::map<int, std::shared_ptr<SceneObjectAnimationClip>> clipMap = pNode->GetAnimationClipMap();
			std::map<int, std::shared_ptr<SceneObjectAnimationClip>>::const_iterator iter;

			for (iter = clipMap.begin(); iter != clipMap.end(); iter++)
			{
				AddAnimationClip(iter->second);
			}
		}
	}
	return 0;
}

void AnimationManager::AddAnimationClip(std::shared_ptr<SceneObjectAnimationClip> clip)
{
	m_AnimationClips.push_back(clip);
}

void AnimationManager::ClearAnimationClips()
{
	m_AnimationClips.clear();
}
