#ifndef RENDER_CORE_DX11_DX11RENDERER_H
#define RENDER_CORE_DX11_DX11RENDERER_H

#include "render/core/irenderer.h"

#include <d3d11.h>

namespace solunar
{

class DX11Renderer : public IRenderer
{
public:
	DX11Renderer(GLFWwindow * window);
	~DX11Renderer();

	void init() override;
	void shutdown() override;

	void beginFrame() override;
	void endFrame() override;

	void draw(uint32_t verticesCount, uint32_t startVertexLocation) override;
	void drawIndexed(uint32_t indicesCount, uint32_t startIndexLocation, int32_t baseVertexLocation) override;
	void setPrimitiveMode(PrimitiveMode primitiveMode) override;

	IBuffer* createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc);
	void setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset) override;
	void setIndexBuffer(IBuffer* buffer) override;
	
	IShaderProgram* createShaderProgram(const ShaderCreationDesc& vertexShaderDesc, const ShaderCreationDesc& pixelShaderDesc, const std::vector<ShaderInputLayout>& inputLayouts) override;
	void setShaderProgram(IShaderProgram* shaderProgram) override;
	void setConstantBuffer(uint32_t slot, IBuffer* constantBuffer) override;

	ITexture2D* createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc) override;
	void setTexture2D(uint32_t slot, ITexture2D* texture) override;

	ISamplerState* createSamplerState(const SamplerDesc& samplerDesc) override;
	void setSamplerState(int slot, ISamplerState* samplerState) override;

public:
	ID3D11Device* getDevice() { return m_device; }
	ID3D11DeviceContext* getDeviceContext() { return m_deviceContext; }

private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_renderTargetView;

	ID3D11Texture2D* m_depthTexture;
	ID3D11DepthStencilView* m_depthStencilView;

};

// Global instance of DX11Renderer
extern DX11Renderer* g_dx11Renderer;

}

#endif // !RENDER_CORE_DX11_DX11RENDERER_H
