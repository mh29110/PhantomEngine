#pragma once
#include "vector.h"
#include "mat4.h"

namespace Phantom {
	class CameraNode
	{
	public:
	public:
		Phantom::maths::mat4x4 m_worldMatrix;
		Phantom::maths::mat4x4 m_viewMatrix;
		Phantom::maths::mat4x4 m_projectionMatrix;

		float m_positionX = 0, m_positionY = -20, m_positionZ = 0;
		float m_rotationX = 0, m_rotationY = 0, m_rotationZ = 0;

	};

}