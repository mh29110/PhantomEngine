#pragma once
#include "GraphicsManager.h"
#include "OpenGLShader.h"
#include "GfxStruct.h"
#include <unordered_map>

namespace Phantom {
	enum //shader°ó¶¨µã    
	{
		ConstantsPerBatchBind = 10,
		ConstantsPerFrameBind = 11,
		FrameLightBind = 12
	};
	class OpenGLGraphicsManager : public GraphicsManager
	{
	public:
		OpenGLGraphicsManager() {}
		virtual int Init();
		virtual void Shutdown();

		virtual void Tick();

		virtual void Clear();

		virtual void Draw();

		virtual void resize(int32_t width, int32_t height);
	private:
		bool SetShaderParameters(maths::mat4x4  worldMatrix, maths::mat4x4  viewMatrix, maths::mat4x4  projectionMatrix);

		bool InitializeBuffers();
		void RenderBuffers();
		bool InitializeShader(const char* vsFilename, const char* fsFilename);

		virtual void SetPerFrameConstants(const ContextPerFrame& context);
		virtual void SetPerFrameLight(const Light & light);
		virtual void SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches);

		virtual void bindShader();

	private:
		OpenGLShader * m_pShader;
		GLuint m_uboFrameId; 
		GLuint m_uboBatchId; 
		GLuint m_lightId;
		std::unordered_map<std::string, GLuint> m_textures;

		const bool VSYNC_ENABLED = true;

		struct OpenGLContextPerDrawBatch : public ContextPerDrawBatch {
			uint32_t vao;
			uint32_t mode;
			uint32_t type;
			int32_t indexCount;
		};
	};


}

