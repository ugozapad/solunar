#include "render/gl/gluniformbuffer.h"

namespace solunar
{

GLUniformBuffer::GLUniformBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, m_buffer);
	glBufferData(GL_UNIFORM_BUFFER, bufferDesc.m_bufferMemorySize, subresourceDesc.m_memory, getBufferAccess(bufferDesc.m_bufferAccess));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLUniformBuffer::~GLUniformBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}

void GLUniformBuffer::bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_buffer);
}

void* GLUniformBuffer::map(BufferMapping mapping)
{
	void* ptr = glMapBuffer(GL_UNIFORM_BUFFER, getBufferMapping(mapping));
	return ptr;
}

void GLUniformBuffer::unmap()
{
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}

void GLUniformBuffer::updateSubresource(void* data)
{
	//glBufferData(GL_UNIFORM_BUFFER, size, data, isStream ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

}