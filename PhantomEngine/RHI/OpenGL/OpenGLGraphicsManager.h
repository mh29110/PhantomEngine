#pragma once
#include "GraphicsManager.h"
#include "OpenGLShader.h"
#include "GfxStruct.h"

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

		virtual void resize(float width, float height);
	private:
		bool SetShaderParameters(maths::mat4x4  worldMatrix, maths::mat4x4  viewMatrix, maths::mat4x4  projectionMatrix);

		bool InitializeBuffers();
		void RenderBuffers();
		bool InitializeShader(const char* vsFilename, const char* fsFilename);

		virtual void SetPerFrameConstants(const ContextPerFrame& context);
		virtual void SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches);

		virtual void bindShader();

	private:
		OpenGLShader * m_pShader;
		GLuint m_uboFrame; 
		GLuint m_uboBatch; 

		const bool VSYNC_ENABLED = true;

		struct OpenGLContextPerDrawBatch : public ContextPerDrawBatch {
			uint32_t vao;
			uint32_t mode;
			uint32_t type;
			int32_t indexCount;
		};
	};


}

