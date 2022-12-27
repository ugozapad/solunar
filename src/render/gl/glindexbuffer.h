#ifndef RENDER_GL_GLINDEXBUFFER_H
#define RENDER_GL_GLINDEXBUFFER_H

#include "render/buffer.h"

namespace solunar
{

class GLIndexBuffer : public IBuffer
{
public:
	GLIndexBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc);
	~GLIndexBuffer();

	void bind();

	void* map(BufferMapping mapping) override;
	void unmap() override;

	void updateSubresource(void* data) override;

private:
	uint32_t m_buffer;
};

}

#endif // !INDEXOBJECT_H
