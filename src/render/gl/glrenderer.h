#ifndef RENDER_GL_GLRENDERER_H
#define RENDER_GL_GLRENDERER_H

#include "render/irenderer.h"

namespace solunar
{

class GLRenderer : public IRenderer
{
public:
	GLRenderer(GLFWwindow* window);
	~GLRenderer();

	void initialize() override;
	void shutdown() override;

	void beginFrame() override;
	void endFrame() override;

	IBuffer* createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc) override;
	void setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset) override;
	void setIndexBuffer(IBuffer* buffer) override;

private:
	GLFWwindow* m_window;
};

}

#endif // !RENDER_GL_GLRENDERER_H
