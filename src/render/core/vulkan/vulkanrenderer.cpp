#include "render/core/vulkan/vulkanrenderer.h"
#include "render/core/vulkan/vulkanphysicaldevice.h"
#include "render/core/vulkan/vulkandevice.h"

#include <glfw/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace solunar
{

VulkanRenderer* g_vulkanRenderer = nullptr;

VulkanRenderer::VulkanRenderer(GLFWwindow* window) :
    m_vulkanInstance(nullptr)
{
	g_vulkanRenderer = this;

	m_renderWindow = window;
}

VulkanRenderer::~VulkanRenderer()
{
	m_renderWindow = nullptr;

	g_vulkanRenderer = nullptr;
}

void VulkanRenderer::init()
{
    // Initialize vulkan instance
    initInstance();

	// Pick physical device
	VulkanPhysicalDevice::getInstance()->enumerateDevice();

	// Find family queue
	VulkanPhysicalDevice::getInstance()->findQueueFamily();

	// Create vulkan device
	VulkanDevice::getInstance()->create();

	// create render surface
	createSurface();
}

void VulkanRenderer::initInstance()
{
    VkApplicationInfo applicationInfo = {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "Solunar Engine";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "Solunar";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;

    // proceed vulkan extensions
    uint32_t extensionCount = 0;
    const char** extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;

    // create instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_vulkanInstance);
    if (result != VK_SUCCESS)
    {
        printf("Failed to create vulkan instance\n");
    }
}

void VulkanRenderer::initValidationLayer()
{
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

}

void VulkanRenderer::shutdown()
{
	// Release vulkan device
	VulkanDevice::getInstance()->release();

	destroySurface();

    if (m_vulkanInstance)
    {
        vkDestroyInstance(m_vulkanInstance, nullptr);
        m_vulkanInstance = nullptr;
    }
}

void VulkanRenderer::beginFrame()
{
}

void VulkanRenderer::endFrame()
{
}

void VulkanRenderer::draw(uint32_t verticesCount, uint32_t startVertexLocation)
{
}

void VulkanRenderer::drawIndexed(uint32_t indicesCount, uint32_t startIndexLocation, int32_t baseVertexLocation)
{
}

void VulkanRenderer::setPrimitiveMode(PrimitiveMode primitiveMode)
{
}

IBuffer* VulkanRenderer::createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
    return nullptr;
}

void VulkanRenderer::setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset)
{
}

void VulkanRenderer::setIndexBuffer(IBuffer* buffer)
{
}

IShaderProgram* VulkanRenderer::createShaderProgram(const ShaderCreationDesc& vertexShaderDesc, const ShaderCreationDesc& pixelShaderDesc, const std::vector<ShaderInputLayout>& inputLayouts)
{
    return nullptr;
}

void VulkanRenderer::setShaderProgram(IShaderProgram* shaderProgram)
{
}

void VulkanRenderer::setConstantBuffer(uint32_t slot, IBuffer* constantBuffer)
{
}

ITexture2D* VulkanRenderer::createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc)
{
    return nullptr;
}

void VulkanRenderer::setTexture2D(uint32_t slot, ITexture2D* texture)
{
}

ISamplerState* VulkanRenderer::createSamplerState(const SamplerDesc& samplerDesc)
{
    return nullptr;
}

void VulkanRenderer::setSamplerState(int slot, ISamplerState* samplerState)
{
}

//////////////////////////////////////////////////////////////////////////
// Vulkan render specific

void VulkanRenderer::createSurface()
{
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = glfwGetWin32Window(m_renderWindow);
	surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	if (vkCreateWin32SurfaceKHR(m_vulkanInstance, &surfaceCreateInfo, nullptr, &m_renderSurface) != VK_SUCCESS)
	{
		printf("failed to create window surface\n");
	}
}

void VulkanRenderer::destroySurface()
{
	vkDestroySurfaceKHR(m_vulkanInstance, m_renderSurface, nullptr);
}

IRenderer* createVulkanRenderer(GLFWwindow* window)
{
    return new VulkanRenderer(window);
}

}
