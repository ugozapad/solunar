#ifndef RENDER_BUFFER_H
#define RENDER_BUFFER_H

#include <stdint.h>

namespace solunar
{

enum BufferType
{
	BufferType_VertexBuffer,
	BufferType_IndexBuffer,
	BufferType_ConstantBuffer
};

enum BufferAccess
{
	BufferAccess_Default,
	BufferAccess_Dynamic
};

enum BufferMapping
{
	BufferMapping_Read,
	BufferMapping_Write,
	BufferMapping_WriteDiscard,
	BufferMapping_ReadAndWrite
};

struct BufferDesc
{
	BufferType m_bufferType;
	BufferAccess m_bufferAccess;
	uint32_t m_bufferMemorySize;
	/*uint32_t m_stride;
	uint32_t m_offset;*/
};

struct SubresourceDesc
{
	void* m_memory;
	uint32_t m_memoryPitch;
	uint32_t m_memorySlicePitch;
};

class IBuffer
{
public:
	virtual ~IBuffer() {}

	virtual void* map(BufferMapping mapping) = 0;
	virtual void  unmap() = 0;

	virtual void updateSubresource(void* data, size_t size) = 0;
};

}

#endif // !RENDER_CORE_BUFFER_H
