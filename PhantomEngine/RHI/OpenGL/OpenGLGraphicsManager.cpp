#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include "OpenGLGraphicsManager.h"
#include "AssetLoadManager.h"
#include "SceneManager.h"
#include "GfxConfiguration.h"
#include "IApplication.h"
#include "Scene.h"
#include <unordered_map>
#include "SceneObjectGeometry.h"
#include "SceneObjectVertexArray.h"
#include "SceneObjectIndexArray.h"
#include "GfxStruct.h"

const char VS_SHADER_SOURCE_FILE[] = "Resources/shaders/vert_light.shader";
const char PS_SHADER_SOURCE_FILE[] = "Resources/shaders/frag_light.shader";

const char SKYBOX_VS_SHADER_SOURCE_FILE[] = "Resources/shaders/skybox_vert.shader";
const char SKYBOX_PS_SHADER_SOURCE_FILE[] = "Resources/shaders/skybox_frag.shader";
float cubeVertices[] = {
	// positions          // texture Coords
		-50.0f, -50.0f, -50.0f,  0.0f, 0.0f,
	 50.0f, -50.0f, -50.0f,  1.0f, 0.0f,
	 50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
	 50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
	-50.0f,  50.0f, -50.0f,  0.0f, 1.0f,
	-50.0f, -50.0f, -50.0f,  0.0f, 0.0f,

	-50.0f, -50.0f,  50.0f,  0.0f, 0.0f,
	 50.0f, -50.0f,  50.0f,  1.0f, 0.0f,
	 50.0f,  50.0f,  50.0f,  1.0f, 1.0f,
	 50.0f,  50.0f,  50.0f,  1.0f, 1.0f,
	-50.0f,  50.0f,  50.0f,  0.0f, 1.0f,
	-50.0f, -50.0f,  50.0f,  0.0f, 0.0f,

	-50.0f,  50.0f,  50.0f,  1.0f, 0.0f,
	-50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
	-50.0f, -50.0f, -50.0f,  0.0f, 1.0f,
	-50.0f, -50.0f, -50.0f,  0.0f, 1.0f,
	-50.0f, -50.0f,  50.0f,  0.0f, 0.0f,
	-50.0f,  50.0f,  50.0f,  1.0f, 0.0f,

	 50.0f,  50.0f,  50.0f,  1.0f, 0.0f,
	 50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
	 50.0f, -50.0f, -50.0f,  0.0f, 1.0f,
	 50.0f, -50.0f, -50.0f,  0.0f, 1.0f,
	 50.0f, -50.0f,  50.0f,  0.0f, 0.0f,
	 50.0f,  50.0f,  50.0f,  1.0f, 0.0f,

	-50.0f, -50.0f, -50.0f,  0.0f, 1.0f,
	 50.0f, -50.0f, -50.0f,  1.0f, 1.0f,
	 50.0f, -50.0f,  50.0f,  1.0f, 0.0f,
	 50.0f, -50.0f,  50.0f,  1.0f, 0.0f,
	-50.0f, -50.0f,  50.0f,  0.0f, 0.0f,
	-50.0f, -50.0f, -50.0f,  0.0f, 1.0f,

	-50.0f,  50.0f, -50.0f,  0.0f, 1.0f,
	 50.0f,  50.0f, -50.0f,  1.0f, 1.0f,
	 50.0f,  50.0f,  50.0f,  1.0f, 0.0f,
	 50.0f,  50.0f,  50.0f,  1.0f, 0.0f,
	-50.0f,  50.0f,  50.0f,  0.0f, 0.0f,
	-50.0f,  50.0f, -50.0f,  0.0f, 1.0f
};

using namespace std;
using namespace Phantom::maths;

extern struct gladGLversionStruct GLVersion;

namespace Phantom {

	extern AssetLoadManager* g_pAssetLoader;
	extern SceneManager* g_pSceneManager;
	extern IApplication* g_pApp;

	bool OpenGLGraphicsManager::InitializeBuffers()
	{
		uint32_t batchCounter = 0;
		auto& scene = g_pSceneManager->GetSceneForRendering();
		std::unordered_map<std::string, std::shared_ptr<SceneObjectGeometry>> geoOjbects = scene.GeometryOjbects;
		for (const auto& iter : scene.GeometryNodes)
		{
			const auto& pGeometryNode = iter.second.lock();
			if (!pGeometryNode /*&& pGeometryNode->Visible()*/)
			{
				continue;
			}
			const std::string& gKey = pGeometryNode->GetSceneObjectRef();
			auto i = geoOjbects.find(gKey);
			if (i == geoOjbects.end())
			{
				continue;
			}
			const auto&pGeometry = i->second;
			const auto& pMesh = pGeometry->GetMesh().lock();

			//--- mesh ---- 拆解---------
			const auto vertexPropertiesCount = pMesh->GetVertexPropertiesCount();

			GLuint vertexArrayId;
			// Allocate an OpenGL vertex array object.
			glGenVertexArrays(1, &vertexArrayId);
			// Bind the vertex array object to store all the buffers and vertex attributes we create here.
			glBindVertexArray(vertexArrayId);

			GLuint vertexBufferId;
			// Generate an ID for the vertex buffer.
			for (GLuint i = 0; i < vertexPropertiesCount; i++)
			{
				const SceneObjectVertexArray & vProArr = pMesh->GetVertexPropertyArray(i);
				const auto vProArrSize = vProArr.GetDataSize();
				const auto vProArrData = vProArr.GetData();

				glGenBuffers(1, &vertexBufferId);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
				glBufferData(GL_ARRAY_BUFFER, vProArrSize, vProArrData, GL_STATIC_DRAW);

				glEnableVertexAttribArray(i);
				switch (vProArr.GetDataType()) {
				case VertexDataType::kVertexDataTypeFloat1:
					glVertexAttribPointer(i, 1, GL_FLOAT, false, 0, 0);
					break;
				case VertexDataType::kVertexDataTypeFloat2:
					glVertexAttribPointer(i, 2, GL_FLOAT, false, 0, 0);
					break;
				case VertexDataType::kVertexDataTypeFloat3:
					glVertexAttribPointer(i, 3, GL_FLOAT, false, 0, 0);
					break;
				case VertexDataType::kVertexDataTypeFloat4:
					glVertexAttribPointer(i, 4, GL_FLOAT, false, 0, 0);
					break;
#if !defined(OS_ANDROID) && !defined(OS_WEBASSEMBLY)
				case VertexDataType::kVertexDataTypeDouble1:
					glVertexAttribPointer(i, 1, GL_DOUBLE, false, 0, 0);
					break;
				case VertexDataType::kVertexDataTypeDouble2:
					glVertexAttribPointer(i, 2, GL_DOUBLE, false, 0, 0);
					break;
				case VertexDataType::kVertexDataTypeDouble3:
					glVertexAttribPointer(i, 3, GL_DOUBLE, false, 0, 0);
					break;
				case VertexDataType::kVertexDataTypeDouble4:
					glVertexAttribPointer(i, 4, GL_DOUBLE, false, 0, 0);
					break;
#endif
				default:
					assert(0);
				}
				//#todo buff id 需要统计管理，以备释放切换场景释放
			}

			const auto indexGroupCount = pMesh->GetIndexGroupCount();

			uint32_t  mode;
			switch (pMesh->GetPrimitiveType())
			{
			case PrimitiveType::kPrimitiveTypePointList:
				mode = GL_POINTS;
				break;
			case PrimitiveType::kPrimitiveTypeLineList:
				mode = GL_LINES;
				break;
			case PrimitiveType::kPrimitiveTypeLineStrip:
				mode = GL_LINE_STRIP;
				break;
			case PrimitiveType::kPrimitiveTypeTriList:
				mode = GL_TRIANGLES;
				break;
			case PrimitiveType::kPrimitiveTypeTriStrip:
				mode = GL_TRIANGLE_STRIP;
				break;
			case PrimitiveType::kPrimitiveTypeTriFan:
				mode = GL_TRIANGLE_FAN;
				break;
			default:
				// ignore
				break;
			}
			GLuint indexBufferId = 0;
			int32_t indexCount = 0;
			for (GLuint i = 0; i < indexGroupCount; i++)
			{
				// Generate an ID for the index buffer.
				glGenBuffers(1, &indexBufferId);

				const SceneObjectIndexArray& index_array = pMesh->GetIndexArray(i);
				const auto index_array_size = index_array.GetDataSize();
				const auto index_array_data = index_array.GetData();

				// Bind the index buffer and load the index data into it.
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array_size, index_array_data, GL_STATIC_DRAW);
				// Set the number of indices in the index array.
				indexCount = static_cast<int32_t>(index_array.GetIndexCount());
				uint32_t type;
				switch (index_array.GetIndexType())
				{
				case IndexDataType::kIndexDataTypeInt8:
					type = GL_UNSIGNED_BYTE;
					break;
				case IndexDataType::kIndexDataTypeInt16:
					type = GL_UNSIGNED_SHORT;
					break;
				case IndexDataType::kIndexDataTypeInt32:
					type = GL_UNSIGNED_INT;
					break;
				default:
					// not supported by OpenGL
					//cerr << "Error: Unsupported Index Type " << index_array << endl;
					//cerr << "Mesh: " << *pMesh << endl;
					//cerr << "Geometry: " << *pGeometry << endl;
					continue;
				}
				auto contextPerBatch = make_shared<OpenGLContextPerDrawBatch>();
				//materials
				//const auto matName = pGeometryNode->GetMaterialRef(0);
				const auto material = scene.GetFirstMaterial();
				if (material) {
					const auto & color = material->GetBaseColor();
					if (color.ValueMap) {
						const auto& texture = color.ValueMap->GetTextureImage();
						const auto& textureName = color.ValueMap->GetName();
						GLuint textureId;
						auto iter = m_textures.find(textureName);
						if (iter == m_textures.end())
						{
							glGenTextures(1, &textureId);
							glBindTexture(GL_TEXTURE_2D, textureId);
							glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, texture->Width, texture->Height,
								0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
							glGenerateMipmap(GL_TEXTURE_2D);

							glBindTexture(GL_TEXTURE_2D, 0);
							m_textures[textureName] = textureId;
						}
						else {
							textureId = iter->second;
						}
						contextPerBatch->diffuseMap = static_cast<int32_t>(textureId);
					}

				}

				contextPerBatch->batchIndex = batchCounter++;
				contextPerBatch->vao = vertexArrayId;
				contextPerBatch->mode = mode;
				contextPerBatch->type = type;
				contextPerBatch->indexCount = indexCount;
				contextPerBatch->node = pGeometryNode;
				m_Frame.batchContexts.push_back(contextPerBatch);
			}
			glBindVertexArray(0);
		}
		return true;
	}

	int OpenGLGraphicsManager::Init()
	{

		int result;
		result = gladLoadGL();//在OpenGL RHI下初始化glad ，注意各平台引用glad/(_wgl).c不同，暂在cmake中设置
		if (!result) {
			cerr << "OpenGL load failed!" << endl;
			result = -1;
		}
		result = 0;
		cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << " loaded" << endl;

		if (GLAD_GL_VERSION_3_0) {
			// Set the depth buffer to be entirely cleared to 1.0 values.
			glClearDepth(1.0f);

			// Enable depth testing.
			glEnable(GL_DEPTH_TEST);

			// Set the polygon winding to front facing for the right handed system.
			//默认值是GL_CCW，它代表逆时针，GL_CW代表顺时针顺序。
			glFrontFace(GL_CCW);


			// Enable back face culling.
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		InitializeShader();
		InitializeBuffers();
		initializeSkyBox();
		
		GraphicsManager::Init();
		glGenBuffers(1, &m_uboBatchId);
		glGenBuffers(1, &m_uboFrameId);
		glGenBuffers(1, &m_lightId);
		return result;
	}

	void OpenGLGraphicsManager::Shutdown()
	{
		//#todo

		// Disable the two vertex array attributes.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Release the vertex buffer.
		/*glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_vertexBufferId);*/

		m_textures.clear();

		delete m_pShader;
		delete m_skyboxShader;
		delete m_cubeShader;
	}

	void OpenGLGraphicsManager::Tick()
	{
		Clear();
		GraphicsManager::Tick();
	}

	void OpenGLGraphicsManager::Clear()
	{
		for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
		{
			printf("gl error = %d", err);
		}
		// Set the color to clear the screen to.
		glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
		// Clear the screen and depth buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLGraphicsManager::Draw()
	{
		// Render the model using the color shader.
		RenderBuffers();
		DrawSkyBox();
		m_pShader->unbind();
		glFlush();
	}

	bool OpenGLGraphicsManager::initializeSkyBox()
	{
		


		//==============================================
		static const float skyboxVertices[] = {
			  1.0f,  1.0f,  1.0f,  // 0
		-1.0f,  1.0f,  1.0f,  // 1
		 1.0f, -1.0f,  1.0f,  // 2
		 1.0f,  1.0f, -1.0f,  // 3
		-1.0f,  1.0f, -1.0f,  // 4
		 1.0f, -1.0f, -1.0f,  // 5
		-1.0f, -1.0f,  1.0f,  // 6
		-1.0f, -1.0f, -1.0f   // 7
		};

		static const uint8_t skyboxIndices[] = {
			4, 7, 5,
			5, 3, 4,

			6, 7, 4,
			4, 1, 6,

			5, 2, 0,
			0, 3, 5,

			6, 1, 0,
			0, 2, 6,

			4, 3, 0,
			0, 1, 4,

			7, 6, 5,
			5, 6, 2
		};
		GLenum target;
#if defined(OS_WEBASSEMBLY)
		target = GL_TEXTURE_2D_ARRAY;
#else
		target = GL_TEXTURE_CUBE_MAP;
#endif
		uint32_t texture_id;
		glGenTextures(1, &texture_id);
		glBindTexture(target, texture_id);
		std::string names[] = {"Textures/front.jpg","Textures/back.jpg","Textures/left.jpg",
								"Textures/right.jpg" ,"Textures/top.jpg","Textures/bottom.jpg" };
		for (int picIdx = 0; picIdx < 6; picIdx++)
		{
			Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary(names[picIdx].c_str());
			JpegParser parser;
			auto imgptr = std::make_shared<Image>(parser.Parse(buf));
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + picIdx, 0, GL_RGB, imgptr->Width, imgptr->Height,
				0, GL_RGB, GL_UNSIGNED_BYTE, imgptr->data);
			glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
			//glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, kMaxMipLevels);
			glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
		{
			printf("gl error = %d", err);
		}


		m_textures["SkyBox"] = texture_id;
		m_Frame.frameContext.skybox = texture_id;

		// skybox VAO
		uint32_t skyboxVAO, skyboxVBO[2];
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(2, skyboxVBO);
		glBindVertexArray(skyboxVAO);
		// vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxVBO[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);

		glBindVertexArray(0);

		m_skyboxContext.vao = skyboxVAO;
		m_skyboxContext.mode = GL_TRIANGLES;
		m_skyboxContext.type = GL_UNSIGNED_BYTE;
		m_skyboxContext.indexCount = sizeof(skyboxIndices) / sizeof(skyboxIndices[0]);
		



		// cube VAO
		unsigned int cubeVAO, cubeVBO;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		m_cubeVAOID = cubeVAO;


		Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary("Textures/back.jpg");
		JpegParser parser;
		auto imgptr = std::make_shared<Image>(parser.Parse(buf));
		GLuint cubeTexture;
		glGenTextures(1, &cubeTexture);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgptr->Width, imgptr->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgptr->data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		m_textures["cube"] = cubeTexture;

	
		return true;
	}

	//在最后绘制,实际绘制的面积小性能更好。在shader里面强制其深度为1.0（就是最远）。
	//将深度测试条件从小于改为小于等于。因为在帧开始的时候深度缓冲区被清为1.0，所以只有没有绘制场景物体的部分会保持1.0，
	//也就是只有那些场景物体没有覆盖的地方会被天空盒覆盖。
	void OpenGLGraphicsManager::DrawSkyBox()
	{
		m_cubeShader->bind();
		m_cubeShader->setUniform1i("texture1", 0);
		m_cubeShader->setUniformMat4("projection", m_Frame.frameContext.projectionMatrix);
		m_cubeShader->setUniformMat4("view", m_Frame.frameContext.viewMatrix);
		m_cubeShader->setUniformMat4("model", m_Frame.batchContexts[0]->modelMatrix);
	
		glBindVertexArray(m_cubeVAOID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textures["cube"]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		m_skyboxShader->bind();
		 //Prepare & Bind per frame constant buffer
		//uint32_t blockIndex = glGetUniformBlockIndex(m_skyboxShader->m_ShaderId, "ConstantsPerFrame");

		//if (blockIndex == GL_INVALID_INDEX)
		//{
		//	// the shader does not use "ConstantsPerFrame"
		//	// simply return here
		//	return;
		//}
		//glUniformBlockBinding(m_skyboxShader->m_ShaderId, blockIndex, ConstantsPerFrameBind);//frame'ubo bind constant position
		//glBindBufferBase(GL_UNIFORM_BUFFER, ConstantsPerFrameBind, m_uboFrameId);


		GLint OldCullFaceMode;
		glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
		GLint OldDepthFuncMode;
		glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content

		int32_t texture_id = m_Frame.frameContext.skybox;
		int loc = glGetUniformLocation(m_skyboxShader->m_ShaderId, "skybox");
		if (loc < 0)
		{
			printf("Uniform: %d not found.\n", loc);
		}
		mat4x4 m1 = m_Frame.frameContext.viewMatrix;

		glBindVertexArray(m_skyboxContext.vao);
		m_skyboxShader->setUniform1i("skybox", 0);
		m_skyboxShader->setUniformMat4("projection", m_Frame.frameContext.projectionMatrix);
		m_skyboxShader->setUniformMat4("view", m1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
		glDrawElements(m_skyboxContext.mode, m_skyboxContext.indexCount, m_skyboxContext.type, 0x00);
		glBindVertexArray(0);

		glCullFace(OldCullFaceMode);
		glDepthFunc(OldDepthFuncMode);
		m_skyboxShader->unbind();


	}

	void OpenGLGraphicsManager::resize(int32_t width, int32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLGraphicsManager::bindCommonShader()
	{
		m_pShader->bind();
	}

	void OpenGLGraphicsManager::RenderBuffers()
	{
		//使用ubo 获取一帧期间的常量
		uint32_t blockIndex = glGetUniformBlockIndex(m_pShader->m_ShaderId, "ConstantsPerFrame");
		if (blockIndex != GL_INVALID_INDEX)
		{
			glUniformBlockBinding(m_pShader->m_ShaderId, blockIndex, ConstantsPerFrameBind);
			glBindBufferBase(GL_UNIFORM_BUFFER, ConstantsPerFrameBind, m_uboFrameId);
		}

		//light 
		uint32_t lightBlockIdx = glGetUniformBlockIndex(m_pShader->m_ShaderId, "Light");
		if (lightBlockIdx != GL_INVALID_INDEX)
		{
			glUniformBlockBinding(m_pShader->m_ShaderId, lightBlockIdx, FrameLightBind);
			glBindBufferBase(GL_UNIFORM_BUFFER, FrameLightBind, m_lightId);
		}


		uint32_t bIndex = glGetUniformBlockIndex(m_pShader->m_ShaderId, "ConstantsPerBatch");
		for (auto& pDbc : m_Frame.batchContexts)
		{
			const OpenGLContextPerDrawBatch& dbc = dynamic_cast<const OpenGLContextPerDrawBatch&>(*pDbc);
			//绑定每批次渲染时的常量
			glBindBufferRange(GL_UNIFORM_BUFFER, bIndex, m_uboBatchId,
				dbc.batchIndex * kSizeOfBatchConstantBuffer, kSizeOfBatchConstantBuffer);
			//绑定纹理
			m_pShader->setUniform1i("diffuseColor", 0);


			glActiveTexture(GL_TEXTURE0);
			if (dbc.diffuseMap > 0) {
				glBindTexture(GL_TEXTURE_2D, dbc.diffuseMap);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, 0);
			}



			glBindVertexArray(dbc.vao);
			glDrawElements(dbc.mode, dbc.indexCount, dbc.type, 0x00);
		}
		glBindVertexArray(0);
	}



	bool OpenGLGraphicsManager::InitializeShader()
	{
		m_pShader = new  OpenGLShader(VS_SHADER_SOURCE_FILE, PS_SHADER_SOURCE_FILE);
		m_skyboxShader =  new OpenGLShader(SKYBOX_VS_SHADER_SOURCE_FILE, SKYBOX_PS_SHADER_SOURCE_FILE);
		m_cubeShader =  new OpenGLShader("Resources/shaders/cubevs.shader", "Resources/shaders/cubefs.shader");

		return true;
	}

	

	void OpenGLGraphicsManager::SetPerFrameLight(const Light & light)
	{
		m_Frame.light.lightPos = vec4(1000.0f, 0.0f, 0.0f, 0.0f);
		m_Frame.light.lightDir = vec4(1.0f, 0.0f, 0.0f, 0.0f);
		m_Frame.light.lightColor = vec4(255.0f, 255.0f, 0.0f, 255.0f);
		glBindBuffer(GL_UNIFORM_BUFFER, m_lightId);
		glBufferData(GL_UNIFORM_BUFFER, kSizeOfLigtBuffer, &light, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLGraphicsManager::SetPerFrameConstants(const ContextPerFrame& context)
	{
		shared_ptr<CameraNode> camera = g_pSceneManager->GetSceneForRendering().camera;
		m_Frame.frameContext.viewMatrix = camera->m_viewMatrix;
		m_Frame.frameContext.projectionMatrix = camera->m_projectionMatrix;


		ConstantsPerFrame constants = static_cast<ConstantsPerFrame>(context);
		glBindBuffer(GL_UNIFORM_BUFFER, m_uboFrameId);
		glBufferData(GL_UNIFORM_BUFFER, kSizeOfFrameConstantBuffer, &constants, GL_DYNAMIC_DRAW);// 256 对齐  ， gpu块读取 todo
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLGraphicsManager::SetPerBatchConstants(const std::vector<std::shared_ptr<ContextPerDrawBatch>>& batches)
	{
		uint8_t * pBuffer = new uint8_t[kSizeOfBatchConstantBuffer* batches.size()];
		for (auto & pBatch : batches)
		{
			const ConstantsPerBatch& constants = static_cast<ConstantsPerBatch&>(*pBatch);
			memcpy(pBuffer + pBatch->batchIndex * kSizeOfBatchConstantBuffer, &constants, kSizeOfBatchConstantBuffer);
		}

		glBindBuffer(GL_UNIFORM_BUFFER, m_uboBatchId);
		glBufferData(GL_UNIFORM_BUFFER, kSizeOfBatchConstantBuffer*batches.size(), pBuffer, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		delete[] pBuffer;
		pBuffer = nullptr;
	}

}
