#ifndef RENDER_GL_GLUNIFORMBUFFER_H
#define RENDER_GL_GLUNIFORMBUFFER_H

#include "render/gl/glshared.h"

namespace solunar
{

class GLUniformBuffer : public IGLBufferBase
{
public:
	GLUniformBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc);
	~GLUniformBuffer();

	void bind();

	void* map(BufferMapping mapping) override;
	void unmap() override;

	void updateSubresource(void* data) override;

	uint32_t getHandle() { return m_buffer; }

private:
	uint32_t m_buffer;
};

}

#endif // !RENDER_GL_GLUNIFORMBUFFER_H
