#include "render/gl/glvertexbuffer.h"

namespace solunar
{

GLVertexBuffer::GLVertexBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, bufferDesc.m_bufferMemorySize, subresourceDesc.m_memory, getBufferAccess(bufferDesc.m_bufferAccess));
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
	void* ptr = glMapBuffer(GL_ARRAY_BUFFER, getBufferMapping(mapping));
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