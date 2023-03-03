#include "render/core/vulkan/vulkandevice.h"
#include "render/core/vulkan/vulkanrenderer.h"
#include "render/core/vulkan/vulkanphysicaldevice.h"

namespace solunar
{

VulkanDevice* VulkanDevice::getInstance()
{
	static VulkanDevice instance;
	return &instance;
}

VulkanDevice::VulkanDevice()
{
}

VulkanDevice::~VulkanDevice()
{
}

void VulkanDevice::release()
{
	vkDestroyDevice(m_device, nullptr);
}

void VulkanDevice::create()
{
	QueueFamilyIndices familyIndices = VulkanPhysicalDevice::getInstance()->getFamilyIndices();

	// Fill queue create info
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = familyIndices.graphicsFamily;
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	// #TODO: do smth with this
	VkPhysicalDeviceFeatures deviceFeatures = {};

	// Fill device create info
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;

	if (vkCreateDevice(VulkanPhysicalDevice::getInstance()->getPhysicalDevice(), &createInfo, nullptr, &m_device) != VK_SUCCESS)
	{
		printf("failed to create device\n");
	}

	vkGetDeviceQueue(m_device, familyIndices.graphicsFamily, 0, &m_deviceQueue);
}

void VulkanDevice::findDeviceFeatures()
{
	printf("IMPLEMENT !!!\n");
}

}
