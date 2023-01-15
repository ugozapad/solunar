#ifndef RENDER_GL_GLBUFFER_H
#define RENDER_GL_GLBUFFER_H

#include "render/core/gl/glshared.h"

namespace solunar
{

class GLBuffer : public IBuffer
{
public:
	GLBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc);
	~GLBuffer();

	void bind();

	void* map(BufferMapping mapping) override;
	void unmap() override;

	void updateSubresource(void* data) override;

	uint32_t getHandle() { return m_buffer; }

private:
	uint32_t m_buffer;
	GLenum m_target;
};

}

#endif // !RENDER_GL_GLBUFFER_H
