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
		bool InitializeShader(const char* vsFilename, const char* fsFilename);

	private:
		unsigned int m_vertexShader;
		unsigned int m_fragmentShader;
		unsigned int m_shaderProgram;

		const bool VSYNC_ENABLED = true;

		int     m_indexCount;
		unsigned int m_vertexArrayId, m_indexBufferId;

	};
}

