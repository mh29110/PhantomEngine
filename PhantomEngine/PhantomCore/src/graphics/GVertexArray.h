#pragma once 
#include "gl/glew.h"
#include <vector>
#include "GVertexBuffer.h"

namespace phantom {namespace graphics {	

	class GVertexArray
	{
	public:
		GVertexArray();
		~GVertexArray();
		void bind() const ;
		void unbind() const ;
		void addBuffer(GVertexBuffer* buffer, GLuint index);

	private:
		GLuint m_ArrayId;
		std::vector<GVertexBuffer*> m_Buffers;
	};
}
}