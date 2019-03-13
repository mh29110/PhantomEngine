#pragma once
#include "GraphicsManager.h"
#include "mat4.h"

namespace Phantom {
	class OpenGLGraphicsManager : public GraphicsManager
	{
	public:
		OpenGLGraphicsManager() {}
		virtual int Initialize();
		virtual void Finalize();

		virtual void Tick();

		virtual void Clear();

		virtual void Draw();

	private:
		bool SetShaderParameters(maths::mat4x4  worldMatrix, maths::mat4x4  viewMatrix, maths::mat4x4  projectionMatrix);

		bool InitializeBuffers();
		void RenderBuffers();
		void CalculateCameraPosition();
		bool InitializeShader(const char* vsFilename, const char* fsFilename);

	private:
		unsigned int m_vertexShader;
		unsigned int m_fragmentShader;
		unsigned int m_shaderProgram;

		const bool VSYNC_ENABLED = true;
		const float screenDepth = 1000.0f;
		const float screenNear = 0.1f;

		int     m_vertexCount, m_indexCount;
		unsigned int m_vertexArrayId, m_vertexBufferId, m_indexBufferId;

		float m_positionX = 0, m_positionY = 0, m_positionZ = -10;
		float m_rotationX = 0, m_rotationY = 0, m_rotationZ = 0;
		Phantom::maths::mat4x4 m_worldMatrix;
		Phantom::maths::mat4x4 m_viewMatrix;
		Phantom::maths::mat4x4 m_projectionMatrix;
	};
}

