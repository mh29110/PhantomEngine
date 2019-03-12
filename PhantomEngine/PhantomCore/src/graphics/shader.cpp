#include "shader.h"
#include "../utils/fileUtils.h"

namespace Phantom { namespace graphics {

	Shader::Shader (const char* $vPath,const char* $fPath):vPath($vPath),fPath($fPath)
	{
		m_ShaderId = compile();
	}

	void Shader::bind() const
	{
		glUseProgram(m_ShaderId);	
	}
	void Shader::unbind() const
	{
		glUseProgram(0);
	}
	GLuint Shader::compile(){
//load
		char* vs = NULL , * fs = NULL;
		vs = read_file(vPath);
		fs = read_file(fPath);

//compile
		GLint compileRes;

		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader,1,&vs , NULL);
		glCompileShader(vShader);
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &compileRes);
		if(compileRes == GL_FALSE)
		{
			printShaderInfoLog(vShader);
		}

		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader,1,&fs , NULL);
		glCompileShader(fShader);
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &compileRes);
		if(compileRes == GL_FALSE)
		{
			printShaderInfoLog(fShader);
		}	
		free(vs);free(fs);
		GLuint compilingPId = glCreateProgram();
		glAttachShader(compilingPId , vShader);
		glAttachShader(compilingPId, fShader);
		glLinkProgram(compilingPId);
		printProgramInfoLog(compilingPId);

		glDeleteShader(vShader);
		glDeleteShader(fShader);

		return compilingPId;
	}
	void Shader::printShaderInfoLog(GLuint id){
		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetShaderiv(id, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(id, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
	}

	void Shader::printProgramInfoLog(GLuint id){
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

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_ShaderId, name);
	}

	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const maths::mat4x4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	Shader::~Shader(){
		glDeleteProgram(m_ShaderId);
	}
}}