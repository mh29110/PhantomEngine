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
const char* MVP_NAME_M = "ojbect2world_matrix";
const char* MVP_NAME_V = "world2view_matrix";
const char* MVP_NAME_P = "projection_matrix";

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
				if (i > 1) break;
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

	static void OutputShaderErrorMessage(unsigned int shaderId, const char* shaderFilename)
	{
		int logSize, i;
		char* infoLog;
		ofstream fout;

		// Get the size of the string containing the information log for the failed shader compilation message.
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = new char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

		// Open a file to write the error message to.
		fout.open("shader-error.txt");

		// Write out the error message.
		for (i = 0; i < logSize; i++)
		{
			fout << infoLog[i];
		}

		// Close the file.
		fout.close();

		// Pop a message up on the screen to notify the user to check the text file for compile errors.
		cerr << "Error compiling shader.  Check shader-error.txt for message." << shaderFilename << endl;

		return;
	}

	static void OutputLinkerErrorMessage(unsigned int programId)
	{
		int logSize, i;
		char* infoLog;
		ofstream fout;


		// Get the size of the string containing the information log for the failed shader compilation message.
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

		// Increment the size by one to handle also the null terminator.
		logSize++;

		// Create a char buffer to hold the info log.
		infoLog = new char[logSize];
		if (!infoLog)
		{
			return;
		}

		// Now retrieve the info log.
		glGetProgramInfoLog(programId, logSize, NULL, infoLog);

		// Open a file to write the error message to.
		fout.open("linker-error.txt");

		// Write out the error message.
		for (i = 0; i < logSize; i++)
		{
			fout << infoLog[i];
		}

		// Close the file.
		fout.close();

		// Pop a message up on the screen to notify the user to check the text file for linker errors.
		cerr << "Error compiling linker.  Check linker-error.txt for message." << endl;
	}

	int OpenGLGraphicsManager::Initialize()
	{
		
		int result;
		result = gladLoadGL();//在OpenGL RHI下初始化glad ，注意各平台引用glad/(_wgl).c不同，暂在cmake中设置
		if (!result) {
			cerr << "OpenGL load failed!" << endl;
			result = -1;
		}
		else {
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

			InitializeShader(VS_SHADER_SOURCE_FILE, PS_SHADER_SOURCE_FILE);
			InitializeBuffers();
		}
		GraphicsManager::Initialize();
		return result;
	}

	void OpenGLGraphicsManager::Finalize()
	{
		// Disable the two vertex array attributes.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Release the vertex buffer.
		/*glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_vertexBufferId);*/

			// Detach the vertex and fragment shaders from the program.
		glDetachShader(m_shaderProgram, m_vertexShader);
		glDetachShader(m_shaderProgram, m_fragmentShader);

		// Delete the vertex and fragment shaders.
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);

		// Delete the shader program.
		glDeleteProgram(m_shaderProgram);
	}

	void OpenGLGraphicsManager::Tick()
	{
		Clear();
		GraphicsManager::Tick();
	}

	void OpenGLGraphicsManager::Clear()
	{
		// Set the color to clear the screen to.
		glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
		// Clear the screen and depth buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLGraphicsManager::Draw()
	{
//        static float rotateAngle = 0.0f;
		shared_ptr<CameraNode> camera = g_pSceneManager->GetSceneForRendering().camera;
		// Update world matrix to rotate the model
		/*rotateAngle += PI / 120;
		Matrix4X4f rotationMatrixY;
		Matrix4X4f rotationMatrixZ;
		MatrixRotationY(rotationMatrixY, rotateAngle);
		MatrixRotationZ(rotationMatrixZ, rotateAngle);
		MatrixMultiply(m_worldMatrix, rotationMatrixZ, rotationMatrixY)*/;


		// Set the color shader as the current shader program and set the matrices that it will use for rendering.
		glUseProgram(m_shaderProgram);
		SetShaderParameters(camera->m_worldMatrix, camera->m_viewMatrix, camera->m_projectionMatrix);

		// Render the model using the color shader.
		RenderBuffers();

		glFlush();
	}

	void OpenGLGraphicsManager::resize(float width, float height)
	{
		glViewport(0, 0, width, height);
	}

	bool OpenGLGraphicsManager::SetShaderParameters(mat4x4  worldMatrix, mat4x4  viewMatrix, mat4x4  projectionMatrix)
	{
		unsigned int location;

		// Set the world matrix in the vertex shader.
		location = glGetUniformLocation(m_shaderProgram, MVP_NAME_M);
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, worldMatrix.elements);

		// Set the view matrix in the vertex shader.
		location = glGetUniformLocation(m_shaderProgram, MVP_NAME_V);
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, viewMatrix.elements);

		// Set the projection matrix in the vertex shader.
		location = glGetUniformLocation(m_shaderProgram, MVP_NAME_P);
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location, 1, false, projectionMatrix.elements);

		return true;
	}

	void OpenGLGraphicsManager::RenderBuffers()
	{
		// Bind the vertex array object that stored all the information about the vertex and index buffers.

		for (auto& pDbc : m_Frame.batchContexts)
		{
			const OpenGLContextPerDrawBatch& dbc = dynamic_cast<const OpenGLContextPerDrawBatch&>(*pDbc);
			glBindVertexArray(dbc.vao);
			glDrawElements(dbc.mode, dbc.indexCount, dbc.type, 0x00);
		}
		glBindVertexArray(0);
	}

	

	bool OpenGLGraphicsManager::InitializeShader(const char* vsFilename, const char* fsFilename)
	{
		std::string vertexShaderBuffer;
		std::string fragmentShaderBuffer;
		int status;

		// Load the vertex shader source file into a text buffer.
		vertexShaderBuffer = g_pAssetLoader->SyncOpenAndReadTextFileToString(vsFilename);
		if (vertexShaderBuffer.empty())
		{
			return false;
		}

		// Load the fragment shader source file into a text buffer.
		fragmentShaderBuffer = g_pAssetLoader->SyncOpenAndReadTextFileToString(fsFilename);
		if (fragmentShaderBuffer.empty())
		{
			return false;
		}

		// Create a vertex and fragment shader object.
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Copy the shader source code strings into the vertex and fragment shader objects.
		const char* _v_c_str = vertexShaderBuffer.c_str();
		glShaderSource(m_vertexShader, 1, &_v_c_str, NULL);
		const char* _f_c_str = fragmentShaderBuffer.c_str();
		glShaderSource(m_fragmentShader, 1, &_f_c_str, NULL);

		// Compile the shaders.
		glCompileShader(m_vertexShader);
		glCompileShader(m_fragmentShader);

		// Check to see if the vertex shader compiled successfully.
		glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &status);
		if (status != 1)
		{
			// If it did not compile then write the syntax error message out to a text file for review.
			OutputShaderErrorMessage(m_vertexShader, vsFilename);
			return false;
		}

		// Check to see if the fragment shader compiled successfully.
		glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &status);
		if (status != 1)
		{
			// If it did not compile then write the syntax error message out to a text file for review.
			OutputShaderErrorMessage(m_fragmentShader, fsFilename);
			return false;
		}

		// Create a shader program object.
		m_shaderProgram = glCreateProgram();

		// Attach the vertex and fragment shader to the program object.
		glAttachShader(m_shaderProgram, m_vertexShader);
		glAttachShader(m_shaderProgram, m_fragmentShader);

		// Bind the shader input variables.
		/*glBindAttribLocation(m_shaderProgram, 0, "inputPosition");
		glBindAttribLocation(m_shaderProgram, 1, "inputColor");
	*/
	// Link the shader program.
		glLinkProgram(m_shaderProgram);

		// Check the status of the link.
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
		if (status != 1)
		{
			// If it did not link then write the syntax error message out to a text file for review.
			OutputLinkerErrorMessage(m_shaderProgram);
			return false;
		}

		return true;
	}
}
