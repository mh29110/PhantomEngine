#pragma once
#include "GraphicsManager.h"
#include "OpenGLShader.h"
#include "GfxStruct.h"
#include <unordered_map>

namespace Phantom {
	enum //shader绑定点    
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

		virtual void DrawGUI();

		virtual void DrawSkyBox();

		virtual void resize(int32_t width, int32_t height);

	protected:
	private:
		void RenderBatches();
		
		void RenderShadowMap();
		void BeginShadowMap();        
        void EndShadowMap();
		void SetShadowMap();


		bool InitializeBuffers();
		bool InitializeShader();
		bool initializeSkyBox();
		bool initializeTextVao();

		virtual void SetPerFrameConstants(const ContextPerFrame& context);
		virtual void SetPerFrameLight();
		virtual void SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches);

		virtual void BindShaderByType(Shader_Type st);
	private:
		std::shared_ptr<OpenGLShader>     m_pShader;
		std::shared_ptr<OpenGLShader>     m_skyboxShader;
		std::shared_ptr<OpenGLShader>     m_pShadowMapShader;
		std::shared_ptr<OpenGLShader>     m_TextShader;
		std::weak_ptr<OpenGLShader>       m_currentShader;

		GLuint m_uboFrameId; 
		GLuint m_uboBatchId; 
		GLuint m_lightId;
		GLuint m_shadowMapFboId;

		//text vao && vbo  for test
		GLuint m_TextVaoId;
		GLuint m_TextVboId;
		GLuint m_TextTextureId;

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

