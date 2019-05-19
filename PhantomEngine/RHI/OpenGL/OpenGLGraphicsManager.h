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

		virtual void DrawSkyBox();

		virtual void resize(int32_t width, int32_t height);

	protected:
	private:
		bool SetShaderParameters(maths::mat4x4  worldMatrix, maths::mat4x4  viewMatrix, maths::mat4x4  projectionMatrix);

		void RenderBuffers();
		
		void RenderShadowMap();
		void BeginShadowMap();        
        void EndShadowMap();


		bool InitializeBuffers();
		bool InitializeShader();
		bool initializeSkyBox();

		virtual void SetPerFrameConstants(const ContextPerFrame& context);
		virtual void SetPerFrameLight(const Light & light);
		virtual void SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches);

		virtual void bindCommonShader();
	private:
		OpenGLShader*     m_pShader;
		OpenGLShader*     m_skyboxShader;
		OpenGLShader*     m_pShadowMapShader;

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

		OpenGLContextPerDrawBatch m_skyboxContext;
	};


}

