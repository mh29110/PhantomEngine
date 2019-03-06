#pragma once 

#include "gl/glew.h"

namespace phantom {namespace graphics {

		class GIndexBuffer
		{
		public:
			GIndexBuffer(GLuint*data , GLsizei count);
			~GIndexBuffer();
			inline void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId); }
			inline void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

			inline GLuint getCount() const { return m_Count; }
		private:
			GLuint m_BufferId;
			GLuint m_Count;
		};
	}
}