#pragma once
#include "SceneBaseNode.h"
#include "SceneObjectLight.h"

namespace Phantom
{
	class SceneLightNode : public SceneNode<SceneObjectLight>
	{
	protected:
		bool m_bShadow;
	public:
		using SceneNode::SceneNode;
		void SetCastShadow(bool isShadow) { m_bShadow = isShadow; }
		const bool CastShadow() { return m_bShadow; }
	};
}