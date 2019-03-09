#pragma once 
#include <glad/glad.h>

namespace phantom {namespace graphics {	

	class GVertexBuffer
	{
	public:
		GVertexBuffer(GLfloat *data, GLsizei size, GLuint componentCount);
		~GVertexBuffer();
		void bind();
		void unbind();
		GLuint getComponentCount() const { return m_ComponentCount; }

	private:
		GLuint m_BufferId;
		GLuint m_ComponentCount;
	};
}
}