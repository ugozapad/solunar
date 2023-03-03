#include "render/core/vulkan/vulkanphysicaldevice.h"
#include "render/core/vulkan/vulkanrenderer.h"

namespace solunar
{

VulkanPhysicalDevice* VulkanPhysicalDevice::getInstance()
{
	static VulkanPhysicalDevice instance;
	return &instance;
}

VulkanPhysicalDevice::VulkanPhysicalDevice() :
	m_physicalDevice(VK_NULL_HANDLE)
{
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
	m_physicalDevice = VK_NULL_HANDLE;
}

void VulkanPhysicalDevice::release()
{

}

void VulkanPhysicalDevice::enumerateDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(g_vulkanRenderer->getVulkanInstance(), &deviceCount, nullptr);
	if (deviceCount == 0)
	{
		printf("no found devices with vulkan support\n");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(g_vulkanRenderer->getVulkanInstance(), &deviceCount, &devices[0]);

	for (const auto& device : devices)
	{
		if (isDeviceSuitable(device))
		{
			m_physicalDevice = device;
			break;
		}
	}

	if (m_physicalDevice == VK_NULL_HANDLE)
	{
		printf("failed to find suitable device\n");
	}
}

void VulkanPhysicalDevice::findQueueFamily()
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			m_familyIndices.graphicsFamily = i;
		}

		if (m_familyIndices.isValid()) {
			break;
		}

		i++;
	}
}

bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice physicsDevice)
{
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(physicsDevice, &deviceProperties);

	// only discrete devices are supported 
	return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
}

}