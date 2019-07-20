#include "SceneObjectSkin.h"

using namespace Phantom;

void Phantom::SceneObjectSkeleton::ApplyTransform(const std::shared_ptr<SceneObjectTransform>&& transform)
{
	m_Transform  = std::move(transform);
}
