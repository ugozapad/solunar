#ifndef RENDER_RENDER_H
#define RENDER_RENDER_H

#include <vector>

#include "render/buffer.h"
#include "render/texture.h"
#include "render/ishaderprogram.h"

struct GLFWwindow;

namespace solunar
{

enum PrimitiveMode
{
	PrimitiveMode_TriangleList
};

class IRenderer
{
public:
	virtual ~IRenderer() {}

	virtual void initialize() = 0;
	virtual void shutdown() = 0;

	virtual void beginFrame() = 0;
	virtual void endFrame() = 0;

	virtual void draw(uint32_t verticesCount, uint32_t startVertexLocation) = 0;
	virtual void drawIndexed(uint32_t indicesCount, uint32_t startIndexLocation, int32_t baseVertexLocation) = 0;
	virtual void setPrimitiveMode(PrimitiveMode primitiveMode) = 0;

	virtual IBuffer* createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc) = 0;
	virtual void setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset) = 0;
	virtual void setIndexBuffer(IBuffer* buffer) = 0;

	virtual IShaderProgram* createShaderProgram(const ShaderCreationDesc& vertexShaderDesc, const ShaderCreationDesc& pixelShaderDesc, const std::vector<ShaderInputLayout>& inputLayouts) = 0;
	virtual void setShaderProgram(IShaderProgram* shaderProgram) = 0;
	virtual void setConstantBuffer(uint32_t slot, IBuffer* constantBuffer) = 0;

	//virtual void setVertexShader(IVertexShader* shader) = 0;
	//virtual void setPixelShader(IPixelShader* shader) = 0;
    //
	//virtual void setVSConstantBuffer(uint32_t slot, IBuffer* buffer) = 0;
	//virtual void setPSConstantBuffer(uint32_t slot, IBuffer* buffer) = 0;

	virtual ITexture2D* createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc) = 0;
};

extern IRenderer* g_renderer;

IRenderer* createGLRenderer(GLFWwindow* window);

}

#endif // !RENDERER_RENDERER_H
