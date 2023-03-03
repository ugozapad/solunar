#ifndef RENDER_CORE_VULKAN_VULKANRENDERER_H
#define RENDER_CORE_VULKAN_VULKANRENDERER_H

#include "render/core/irenderer.h"

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

namespace solunar
{

class VulkanRenderer : public IRenderer
{
public:
	VulkanRenderer(GLFWwindow* window);
	~VulkanRenderer();

	void init() override;
	void initInstance();
	void initValidationLayer();

	void shutdown() override;

	void beginFrame() override;
	void endFrame() override;

	void draw(uint32_t verticesCount, uint32_t startVertexLocation) override;
	void drawIndexed(uint32_t indicesCount, uint32_t startIndexLocation, int32_t baseVertexLocation) override;
	void setPrimitiveMode(PrimitiveMode primitiveMode) override;

	IBuffer* createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc) override;
	void setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset) override;
	void setIndexBuffer(IBuffer* buffer) override;

	IShaderProgram* createShaderProgram(const ShaderCreationDesc& vertexShaderDesc, const ShaderCreationDesc& pixelShaderDesc, const std::vector<ShaderInputLayout>& inputLayouts) override;
	void setShaderProgram(IShaderProgram* shaderProgram) override;
	void setConstantBuffer(uint32_t slot, IBuffer* constantBuffer) override;

	ITexture2D* createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc) override;
	void setTexture2D(uint32_t slot, ITexture2D* texture) override;

	ISamplerState* createSamplerState(const SamplerDesc& samplerDesc) override;
	void setSamplerState(int slot, ISamplerState* samplerState) override;

	//////////////////////////////////////////////////////////////////////////
	// Vulkan render specific
	void createSurface();
	void destroySurface();

	VkInstance getVulkanInstance() { return m_vulkanInstance; }

	//VulkanDevice* getVulkanDevice() { return &m_vulkanDevice; }

private:
	GLFWwindow* m_renderWindow;

	VkInstance m_vulkanInstance;
	VkSurfaceKHR m_renderSurface;

	//VulkanDevice m_vulkanDevice;
};

extern VulkanRenderer* g_vulkanRenderer;

}

#endif // !RENDER_CORE_VULKAN_VULKANRENDERER_H
