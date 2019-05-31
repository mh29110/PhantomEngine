#include "OpenGLShader.h"
#include "AssetLoadManager.h"

using namespace std;
namespace Phantom { 

	void string_replace_first( string& allStr , string& src , string& dest)
	{
		string::size_type pos = 0;
		string::size_type srcLen = src.size();
		if( (pos = allStr.find( src , pos)) != string::npos)
		{
			allStr.replace( pos , srcLen , dest );
		}
	}

	OpenGLShader::OpenGLShader(const char* $vPath,const char* $fPath):vPath($vPath),fPath($fPath)
	{
		m_ShaderId = compile();
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_ShaderId);	
	}
	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}
	GLuint OpenGLShader::compile(){
//load
		std::string vsString = g_pAssetLoader->SyncOpenAndReadTextFileToString(vPath);
		std::string fsString = g_pAssetLoader->SyncOpenAndReadTextFileToString(fPath);
        std::string macroString = g_pAssetLoader->SyncOpenAndReadTextFileToString("Resources/shaders/GfxStruct.glsl"); //Unifrom block 所需结构体用宏统一标示
        
        string macroVar = "UNIFORM_BLOCK_MACRO";
        string_replace_first( vsString , macroVar , macroString);
        string_replace_first( fsString , macroVar , macroString);

		char* vs = (char* )vsString.data();
		char* fs = (char* )fsString.data();
        
//compile
		GLint compileRes;

		m_vShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vShaderId,1,&vs , NULL);
		glCompileShader(m_vShaderId);
		glGetShaderiv(m_vShaderId, GL_COMPILE_STATUS, &compileRes);
		if(compileRes == GL_FALSE)
		{
			printShaderInfoLog(m_vShaderId);
		}

		m_fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fShaderId,1,&fs , NULL);
		glCompileShader(m_fShaderId);
		glGetShaderiv(m_fShaderId, GL_COMPILE_STATUS, &compileRes);
		if(compileRes == GL_FALSE)
		{
			printShaderInfoLog(m_fShaderId);
		}	
	
		GLuint compilingPId = glCreateProgram();
		glAttachShader(compilingPId , m_vShaderId);
		glAttachShader(compilingPId, m_fShaderId);
		glLinkProgram(compilingPId);
		printProgramInfoLog(compilingPId);

		glDeleteShader(m_vShaderId);
		glDeleteShader(m_fShaderId);
		return compilingPId;
	}
	void OpenGLShader::printShaderInfoLog(GLuint id){
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		// Open a file to write the error message to.
		//fout.open("linker-error.txt");

		//// Write out the error message.
		//for (i = 0; i < logSize; i++)
		//{
		//	fout << infoLog[i];
		//}

		//// Close the file.
		//fout.close();
		glGetShaderiv(id, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(id, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

	void OpenGLShader::printProgramInfoLog(GLuint id){
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(id, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

	GLint OpenGLShader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_ShaderId, name);
	}

	// 类比    material.SetInt("_SrcBlend", (int) value);
	void OpenGLShader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void OpenGLShader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void OpenGLShader::setUniform2f(const GLchar* name, const maths::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void OpenGLShader::setUniform3f(const GLchar* name, const maths::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void OpenGLShader::setUniform4f(const GLchar* name, const maths::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::setUniformMat4(const GLchar* name, const maths::mat4x4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	OpenGLShader::~OpenGLShader(){

		if (m_vShaderId) {
			glDetachShader(m_ShaderId, m_vShaderId);
			glDeleteShader(m_vShaderId);
		}
		if (m_fShaderId) {
			glDetachShader(m_ShaderId, m_fShaderId);
			glDeleteShader(m_fShaderId);
		}
		// Delete the shader program.
		glDeleteProgram(m_ShaderId);
	}
}
