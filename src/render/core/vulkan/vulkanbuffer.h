#ifndef RENDER_CORE_VULKAN_VULKANBUFFER_H
#define RENDER_CORE_VULKAN_VULKANBUFFER_H

#include "render/core/ibuffer.h"

#include "render/core/vulkan/vulkanshared.h"

namespace solunar
{

class VulkanBuffer : public IBuffer
{
public:
	VulkanBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc);
	~VulkanBuffer();

	void* map(BufferMapping mapping) override;
	void unmap() override;

	void updateSubresource(void* data, size_t size) override;

private:
	BufferDesc m_bufferDesc;
	SubresourceDesc m_subresourceDesc;

	VkBuffer m_buffer;
};

}

#endif // !RENDER_CORE_VULKAN_VULKANBUFFER_H
