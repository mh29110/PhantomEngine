#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <math.h>
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

			//--- mesh ---- ²ð½â---------
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
				//#todo buff id ÐèÒªÍ³¼Æ¹ÜÀí£¬ÒÔ±¸ÊÍ·ÅÇÐ»»³¡¾°ÊÍ·Å
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
				/*const*/ auto material_index = index_array.GetMaterialIndex();
				material_index = 0;//²»Ì«¶®3dmaxµÄ²ÄÖÊ¹ÜÀí£¬ÏÈÄ¬ÈÏ²ÉÓÃGeomatry¹ÒµÄµÚÒ»¸ö²ÄÖÊ¡£

				const auto& matName = pGeometryNode->GetMaterialRef(material_index);
				const auto material = scene.GetMaterial(matName);
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
		result = gladLoadGL();//ÔÚOpenGL RHIÏÂ³õÊ¼»¯glad £¬×¢Òâ¸÷Æ½Ì¨ÒýÓÃglad/(_wgl).c²»Í¬£¬ÔÝÔÚcmakeÖÐÉèÖÃ
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
			//Ä¬ÈÏÖµÊÇGL_CCW£¬Ëü´ú±íÄæÊ±Õë£¬GL_CW´ú±íË³Ê±ÕëË³Ðò¡£
			glFrontFace(GL_CCW);

			/*glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);*/
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
			// positions          
		  -1.0f,  1.0f, -1.0f,
		  -1.0f, -1.0f, -1.0f,
		   1.0f, -1.0f, -1.0f,
		   1.0f, -1.0f, -1.0f,
		   1.0f,  1.0f, -1.0f,
		  -1.0f,  1.0f, -1.0f,

		  -1.0f, -1.0f,  1.0f,
		  -1.0f, -1.0f, -1.0f,
		  -1.0f,  1.0f, -1.0f,
		  -1.0f,  1.0f, -1.0f,
		  -1.0f,  1.0f,  1.0f,
		  -1.0f, -1.0f,  1.0f,

		   1.0f, -1.0f, -1.0f,
		   1.0f, -1.0f,  1.0f,
		   1.0f,  1.0f,  1.0f,
		   1.0f,  1.0f,  1.0f,
		   1.0f,  1.0f, -1.0f,
		   1.0f, -1.0f, -1.0f,

		  -1.0f, -1.0f,  1.0f,
		  -1.0f,  1.0f,  1.0f,
		   1.0f,  1.0f,  1.0f,
		   1.0f,  1.0f,  1.0f,
		   1.0f, -1.0f,  1.0f,
		  -1.0f, -1.0f,  1.0f,

		  -1.0f,  1.0f, -1.0f,
		   1.0f,  1.0f, -1.0f,
		   1.0f,  1.0f,  1.0f,
		   1.0f,  1.0f,  1.0f,
		  -1.0f,  1.0f,  1.0f,
		  -1.0f,  1.0f, -1.0f,

		  -1.0f, -1.0f, -1.0f,
		  -1.0f, -1.0f,  1.0f,
		   1.0f, -1.0f, -1.0f,
		   1.0f, -1.0f, -1.0f,
		  -1.0f, -1.0f,  1.0f,
		   1.0f, -1.0f,  1.0f
		};
		unsigned int skyboxVAO, skyboxVBO;
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
		GLenum target;
		target = GL_TEXTURE_CUBE_MAP;
		uint32_t texture_id;
		glGenTextures(1, &texture_id);
		glBindTexture(target, texture_id);
		vector<std::string> names = { "Textures/right.jpg","Textures/left.jpg","Textures/top.jpg",
								"Textures/bottom.jpg" ,"Textures/front.jpg","Textures/back.jpg" };
		for (int picIdx = 0; picIdx < 6; picIdx++)
		{
			Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary(names[picIdx].c_str());
			JpegParser parser;
			auto imgptr = std::make_shared<Image>(parser.Parse(buf));
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + picIdx, 0, GL_RGB, imgptr->Width, imgptr->Height,
				0, GL_RGB, GL_UNSIGNED_BYTE, imgptr->data);
		}
		
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		for (GLenum err; (err = glGetError()) != GL_NO_ERROR;)
		{
			printf("gl error = %d", err);
		}

		m_textures["SkyBox"] = texture_id;
		m_Frame.frameContext.skybox = texture_id;
		m_skyboxShader->bind();
		m_skyboxShader->setUniform1i("skybox", 0); //0号纹理
		

		m_skyboxContext.vao = skyboxVAO;
		m_skyboxContext.mode = GL_TRIANGLES;
		m_skyboxContext.type = GL_UNSIGNED_BYTE;
		m_skyboxContext.indexCount = 36;
		

	
		return true;
	}

	//ÔÚ×îºó»æÖÆ,Êµ¼Ê»æÖÆµÄÃæ»ýÐ¡ÐÔÄÜ¸üºÃ¡£ÔÚshaderÀïÃæÇ¿ÖÆÆäÉî¶ÈÎª1.0£¨¾ÍÊÇ×îÔ¶£©¡£
	//½«Éî¶È²âÊÔÌõ¼þ´ÓÐ¡ÓÚ¸ÄÎªÐ¡ÓÚµÈÓÚ¡£ÒòÎªÔÚÖ¡¿ªÊ¼µÄÊ±ºòÉî¶È»º³åÇø±»ÇåÎª1.0£¬ËùÒÔÖ»ÓÐÃ»ÓÐ»æÖÆ³¡¾°ÎïÌåµÄ²¿·Ö»á±£³Ö1.0£¬
	//Ò²¾ÍÊÇÖ»ÓÐÄÇÐ©³¡¾°ÎïÌåÃ»ÓÐ¸²¸ÇµÄµØ·½»á±»Ìì¿ÕºÐ¸²¸Ç¡£
	void OpenGLGraphicsManager::DrawSkyBox()
	{
		
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


		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
		m_skyboxShader->bind();
		int32_t texture_id = m_Frame.frameContext.skybox;

		m_skyboxShader->setUniformMat4("projection", m_Frame.frameContext.projectionMatrix);
		m_skyboxShader->setUniformMat4("view", m_Frame.frameContext.viewMatrix);



		glBindVertexArray(m_skyboxContext.vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
		//glDrawElements(m_skyboxContext.mode, m_skyboxContext.indexCount, m_skyboxContext.type, 0x00);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
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
		//Ê¹ÓÃubo »ñÈ¡Ò»Ö¡ÆÚ¼äµÄ³£Á¿
		uint32_t blockIndex = glGetUniformBlockIndex(m_pShader->m_ShaderId, "ConstantsPerFrame");//Shader.PropertyToID
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
			//°ó¶¨Ã¿Åú´ÎäÖÈ¾Ê±µÄ³£Á¿
			glBindBufferRange(GL_UNIFORM_BUFFER, bIndex, m_uboBatchId,
				dbc.batchIndex * kSizeOfBatchConstantBuffer, kSizeOfBatchConstantBuffer);

			//°ó¶¨ÎÆÀí
			m_pShader->setUniform1i("diffuseColor", 0);  //material.SetTexture.
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

		return true;
	}

	
	static float factor = 0.0f;

	void OpenGLGraphicsManager::SetPerFrameLight(const Light & light)
	{
		//À´¸öÈÕ³öÈÕÂä
		float tempX = cos(factor);
		float tempY = sin(factor);
		factor += 0.003f;

		m_Frame.light.lightPos = vec4(0.0f, 200.0f, 0.0f, 0.0f);//µ±Ç°Æ½ÐÐ¹âÏÂÃ»ÓÐÓÃµ½
		m_Frame.light.lightDir = vec4(tempX, tempY, 0.0f, 0.0f);
		m_Frame.light.lightColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);

		glBindBuffer(GL_UNIFORM_BUFFER, m_lightId);
		glBufferData(GL_UNIFORM_BUFFER, kSizeOfLigtBuffer, &light, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLGraphicsManager::SetPerFrameConstants(const ContextPerFrame& context)
	{
		shared_ptr<CameraNode> camera = g_pSceneManager->GetSceneForRendering().camera;
		m_Frame.frameContext.viewMatrix = camera->m_viewMatrix;
		m_Frame.frameContext.projectionMatrix = camera->m_projectionMatrix;


		ConstantsPerFrame constants = static_cast<ConstantsPerFrame>(context);   //MaterialPropertyBlock
		glBindBuffer(GL_UNIFORM_BUFFER, m_uboFrameId);
		glBufferData(GL_UNIFORM_BUFFER, kSizeOfFrameConstantBuffer, &constants, GL_DYNAMIC_DRAW);// 256 ¶ÔÆë  £¬ gpu¿é¶ÁÈ¡ todo
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
