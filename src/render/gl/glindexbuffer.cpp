#include "pch.h"
#include "render/indexbuffer.h"

#include "render/gl_shared.h"

IndexBuffer::IndexBuffer(void* data, size_t size, bool isStream /*= false*/)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, isStream ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if (isStream) {
		Logger::msg("created dynamic index stream ...");
	}
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}
