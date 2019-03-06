#include "GVertexBuffer.h"

phantom::graphics::GVertexBuffer::GVertexBuffer(GLfloat * data, GLsizei size, GLuint componentCount):
	m_ComponentCount(componentCount)
{
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ARRAY_BUFFER, size , data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

phantom::graphics::GVertexBuffer::~GVertexBuffer()
{
	glDeleteBuffers(1, &m_BufferId);
}

void phantom::graphics::GVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER,m_BufferId);
}

void phantom::graphics::GVertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

