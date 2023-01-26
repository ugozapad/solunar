#include "render/core/gl/glbuffer.h"

namespace solunar
{

GLBuffer::GLBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc) :
	m_buffer(0),
	m_target(0)
{
	if (bufferDesc.m_bufferType == BufferType_VertexBuffer)
		m_target = GL_ARRAY_BUFFER;
	else if (bufferDesc.m_bufferType == BufferType_IndexBuffer)
		m_target = GL_ELEMENT_ARRAY_BUFFER;
	else if (bufferDesc.m_bufferType == BufferType_ConstantBuffer)
		m_target = GL_UNIFORM_BUFFER;

	glGenBuffers(1, &m_buffer);
	glBindBuffer(m_target, m_buffer);
	glBufferData(m_target, bufferDesc.m_bufferMemorySize, subresourceDesc.m_memory, getBufferAccess(bufferDesc.m_bufferAccess));
	glBindBuffer(m_target, 0);
}

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}

void GLBuffer::bind()
{
	glBindBuffer(m_target, m_buffer);
}

void* GLBuffer::map(BufferMapping mapping)
{
	void* ptr = glMapBuffer(m_target, getBufferMapping(mapping));
	return ptr;
}

void GLBuffer::unmap()
{
	glUnmapBuffer(m_target);
}

void GLBuffer::updateSubresource(void* data, size_t size)
{
	glBufferSubData(m_target, 0, size, data);
}

}