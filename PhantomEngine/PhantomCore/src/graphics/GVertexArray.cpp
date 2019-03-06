#include "GVertexArray.h"

phantom::graphics::GVertexArray::GVertexArray()
{
	glGenVertexArrays(1, &m_ArrayId);
}

phantom::graphics::GVertexArray::~GVertexArray()
{
	int length = m_Buffers.size();
	for (int i = 0 ; i < length;i++)
	{
		delete m_Buffers[i];
	}
}

void phantom::graphics::GVertexArray::bind() const
{
	glBindVertexArray(m_ArrayId);
}

void phantom::graphics::GVertexArray::unbind() const
{
	glBindVertexArray(0);
}

void phantom::graphics::GVertexArray::addBuffer(GVertexBuffer * buffer, GLuint index)
{
	bind();
	buffer->bind();
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(index);
	buffer->unbind();
	unbind();
}
