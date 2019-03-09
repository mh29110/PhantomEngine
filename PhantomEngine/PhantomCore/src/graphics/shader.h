#ifndef _FILE_SHADER_H_
#define _FILE_SHADER_H_
// *有个小插曲，fileUtils的include的写在头文件里，造成重复定义了，查了半天*
#include <glad/glad.h>
#include "../maths/maths.h"

namespace phantom { namespace graphics {

	class Shader
	{
	public:
		Shader (const char* $vPath,const char* $fPath);

		virtual~Shader();

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

		GLuint compile();
		void printShaderInfoLog(GLuint id);
		void printProgramInfoLog(GLuint id);

		GLint getUniformLocation(const GLchar* name);
	};

}}
#endif //_FILE_SHADER_H_