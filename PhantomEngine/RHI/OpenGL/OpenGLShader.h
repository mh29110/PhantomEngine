#pragma once
#include <glad/glad.h>
#include "../maths/PhMaths.h"

namespace Phantom { 

	class OpenGLShader
	{
	public:
		OpenGLShader(const char* $vPath,const char* $fPath);

		virtual~OpenGLShader();

		GLuint m_ShaderId;
		void bind() const;
		void unbind() const;


		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::mat4x4& matrix);

	private:
		const char* vPath;
		const char* fPath;

		GLuint m_vShaderId;
		GLuint m_fShaderId;

		GLuint compile();
		void printShaderInfoLog(GLuint id);
		void printProgramInfoLog(GLuint id);

		GLint getUniformLocation(const GLchar* name);
	};

}