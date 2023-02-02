#include "render/core/dx11/dx11buffer.h"

namespace solunar
{

UINT getD3D11BindFlags(const BufferDesc& bufferDesc)
{
	switch (bufferDesc.m_bufferType)
	{
		case BufferType_VertexBuffer:
			return D3D11_BIND_VERTEX_BUFFER;
			
		case BufferType_IndexBuffer:
			return D3D11_BIND_INDEX_BUFFER;
			
		case BufferType_ConstantBuffer:
			return D3D11_BIND_CONSTANT_BUFFER;
			
		default:
			break;
	}
	
	//ASSERT2(0, "Unknowed buffer type");
	return 0;
}

D3D11_MAP getD3D11Map(BufferMapping mapping)
{
	switch (mapping)
	{
		case BufferMapping_Read:
			return D3D11_MAP_READ;
		
		case BufferMapping_Write:
			return D3D11_MAP_WRITE;

		case BufferMapping_WriteDiscard:
			return D3D11_MAP_WRITE_DISCARD;
			
		case BufferMapping_ReadAndWrite:
			return D3D11_MAP_READ_WRITE;
			
		default:
			break;
	}
	
	//ASSERT2(0, "Unknowed buffer mapping type");
	return (D3D11_MAP)0;
}

D3D11_USAGE getD3D11Usage(const BufferDesc& desc)
{
	switch (desc.m_bufferAccess)
	{
	case BufferAccess_Default:
		return D3D11_USAGE_DEFAULT;
	case BufferAccess_Dynamic:
		return D3D11_USAGE_DYNAMIC;

	default:
		break;
	}

	return (D3D11_USAGE)0;
}

DX11Buffer::DX11Buffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	D3D11_BUFFER_DESC d3d11BufferDesc;
	memset(&d3d11BufferDesc, 0, sizeof(d3d11BufferDesc));
	d3d11BufferDesc.Usage = getD3D11Usage(bufferDesc);
	d3d11BufferDesc.ByteWidth = bufferDesc.m_bufferMemorySize;
	d3d11BufferDesc.BindFlags = getD3D11BindFlags(bufferDesc);
	d3d11BufferDesc.CPUAccessFlags = (bufferDesc.m_bufferAccess == BufferAccess_Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0;
	d3d11BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData;
	memset(&subresourceData, 0, sizeof(subresourceData));
	subresourceData.pSysMem = subresourceDesc.m_memory;
	subresourceData.SysMemPitch = subresourceDesc.m_memoryPitch;
	subresourceData.SysMemSlicePitch = subresourceDesc.m_memorySlicePitch;

	g_dx11Renderer->getDevice()->CreateBuffer(&d3d11BufferDesc, subresourceDesc.m_memory ? &subresourceData : NULL, &m_buffer);
}

DX11Buffer::~DX11Buffer()
{
	if (m_buffer)
	{
		m_buffer->Release();
		m_buffer = nullptr;
	}
}

void* DX11Buffer::map(BufferMapping mapping)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	memset(&mappedSubresource, 0, sizeof(mappedSubresource));

	g_dx11Renderer->getDeviceContext()->Map(m_buffer, 0, getD3D11Map(mapping), 0, &mappedSubresource);

	return mappedSubresource.pData;
}

void DX11Buffer::unmap()
{
	g_dx11Renderer->getDeviceContext()->Unmap(m_buffer, 0);
}

void DX11Buffer::updateSubresource(void* data, size_t size)
{
	g_dx11Renderer->getDeviceContext()->UpdateSubresource(m_buffer, 0, NULL, data, 0, 0);
}

}