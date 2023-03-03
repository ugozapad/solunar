#ifndef RENDER_CORE_VULKAN_VULKANPHYSICALDEVICE_H
#define RENDER_CORE_VULKAN_VULKANPHYSICALDEVICE_H

#include <vulkan/vulkan.h>

namespace solunar
{

struct QueueFamilyIndices
{
	uint32_t graphicsFamily;

	QueueFamilyIndices()
	{
		graphicsFamily = -1;
	}

	bool isValid()
	{
		return graphicsFamily != -1;
	}
};

class VulkanPhysicalDevice
{
public:
	static VulkanPhysicalDevice* getInstance();

public:
	VulkanPhysicalDevice();
	~VulkanPhysicalDevice();

	void release();

	void enumerateDevice();
	void findQueueFamily();

	const VkPhysicalDevice& const getPhysicalDevice() { return m_physicalDevice; }
	const QueueFamilyIndices& const getFamilyIndices() { return m_familyIndices; }

private:
	bool isDeviceSuitable(VkPhysicalDevice physicsDevice);

private:
	VkPhysicalDevice m_physicalDevice;
	QueueFamilyIndices m_familyIndices;
};

}

#endif // !RENDER_CORE_VULKAN_VULKANPHYSICALDEVICE_H
