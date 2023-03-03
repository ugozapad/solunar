#ifndef RENDER_CORE_VULKAN_VULKANLOGICALDEVICE_H
#define RENDER_CORE_VULKAN_VULKANLOGICALDEVICE_H

#include "render/core/vulkan/vulkanshared.h"

namespace solunar
{

class VulkanDevice
{
public:
	static VulkanDevice* getInstance();

public:
	VulkanDevice();
	~VulkanDevice();

	void release();

	void create();

	const VkDevice& getDevice() const { return m_device; }

private:
	void findDeviceFeatures();

private:
	VkDevice m_device;
	VkQueue m_deviceQueue;
};

}

#endif // !RENDER_CORE_VULKAN_VULKANLOGICALDEVICE_H
