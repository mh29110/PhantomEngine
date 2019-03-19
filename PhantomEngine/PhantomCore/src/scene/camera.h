#pragma once
#include "vector.h"
#include "mat4.h"
#include "SceneBaseNode.h"

namespace Phantom {
	class CameraNode : public SceneBaseNode
	{
	public:
		using SceneBaseNode::SceneBaseNode;
		Phantom::maths::mat4x4 m_viewMatrix;
		Phantom::maths::mat4x4 m_projectionMatrix;

		void CalculateVPMatrix();
		float m_positionX = 0, m_positionY = 0, m_positionZ = 5;
		float m_rotationX = 0, m_rotationY = 0, m_rotationZ = 0;

	};

}