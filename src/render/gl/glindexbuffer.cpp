#include "render/gl/glindexbuffer.h"

namespace solunar
{

GLIndexBuffer::GLIndexBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferDesc.m_bufferMemorySize, subresourceDesc.m_memory, getBufferAccess(bufferDesc.m_bufferAccess));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}

void GLIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void* GLIndexBuffer::map(BufferMapping mapping)
{
	void* ptr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, getBufferMapping(mapping));
	return ptr;
}

void GLIndexBuffer::unmap()
{
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void GLIndexBuffer::updateSubresource(void* data)
{
	//glBufferData(GL_ARRAY_BUFFER, size, data, isStream ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

}