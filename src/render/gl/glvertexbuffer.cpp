#include "render/gl/glvertexbuffer.h"

#include <glad/glad.h>

namespace solunar
{

GLVertexBuffer::GLVertexBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	//glBufferData(GL_ARRAY_BUFFER, size, data, isStream ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}

void GLVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void* GLVertexBuffer::map(BufferMapping mapping)
{
	GLenum accessGl = 0;

	switch (access)
	{
	case BufferMapping_Read:
		accessGl = GL_READ_ONLY;
		break;
	case BufferMapping_Write:
		accessGl = GL_WRITE_ONLY;
		break;
	case BufferMapping_WriteDiscard:
		accessGl = GL_READ_WRITE;
		break;
	}

	void* ptr = glMapBuffer(GL_ARRAY_BUFFER, accessGl);
	return ptr;
}

void GLVertexBuffer::unmap()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void GLVertexBuffer::updateSubresource(void* data)
{
	//glBufferData(GL_ARRAY_BUFFER, size, data, isStream ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

}