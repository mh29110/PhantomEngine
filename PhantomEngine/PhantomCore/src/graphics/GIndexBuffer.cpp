#include "GIndexBuffer.h"

phantom::graphics::GIndexBuffer::GIndexBuffer(GLuint * data, GLsizei count)
{
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

phantom::graphics::GIndexBuffer::~GIndexBuffer()
{
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_BufferId);
}
