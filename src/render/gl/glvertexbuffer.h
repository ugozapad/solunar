#ifndef RENDER_GL_GLVERTEXBUFFER_H
#define RENDER_GL_GLVERTEXBUFFER_H

#include "render/gl/glshared.h"

namespace solunar
{

class GLVertexBuffer : public IGLBufferBase
{
public:
	GLVertexBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc);
	~GLVertexBuffer();

	void bind();

	void* map(BufferMapping mapping) override;
	void unmap() override;

	void updateSubresource(void* data) override;

private:
	uint32_t m_buffer;
};

}

#endif // !RENDER_GL_GLVERTEXBUFFER_H
