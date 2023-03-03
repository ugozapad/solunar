#include "render/core/vulkan/vulkanbuffer.h"
#include "render/core/vulkan/vulkandevice.h"
#include "render/core/vulkan/vulkanrenderer.h"

namespace solunar
{

VkBufferUsageFlags getVulkanBufferUsage(const BufferDesc& bufferDesc)
{
	switch (bufferDesc.m_bufferType)
	{
	case BufferType_VertexBuffer:
		return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

	case BufferType_IndexBuffer:
		return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

	case BufferType_ConstantBuffer:
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

	default:
		break;
	}

	return 0;
}

VulkanBuffer::VulkanBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc) :
	m_bufferDesc(bufferDesc),
	m_subresourceDesc(subresourceDesc)
{
	VkBufferCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	createInfo.size = bufferDesc.m_bufferMemorySize;
	createInfo.usage = getVulkanBufferUsage(bufferDesc);
	createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(VulkanDevice::getInstance()->getDevice(), &createInfo, nullptr, &m_buffer) != VK_SUCCESS)
	{
		printf("failed to create buffer\n");
	}
}

VulkanBuffer::~VulkanBuffer()
{
	vkDestroyBuffer(VulkanDevice::getInstance()->getDevice(), m_buffer, nullptr);
}

void* VulkanBuffer::map(BufferMapping mapping)
{
	void* data;
	vkMapMemory(VulkanDevice::getInstance()->getDevice(), nullptr, 0, m_bufferDesc.m_bufferMemorySize, 0, &data);

	return data;
}

void VulkanBuffer::unmap()
{
	vkUnmapMemory(VulkanDevice::getInstance()->getDevice(), nullptr);
}

void VulkanBuffer::updateSubresource(void* data, size_t size)
{

}

}