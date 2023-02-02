#ifndef RENDER_CORE_DX11_DX11BUFFER_H
#define RENDER_CORE_DX11_DX11BUFFER_H

#include "render/core/ibuffer.h"
#include "render/core/dx11/dx11renderer.h"

namespace solunar
{

class DX11Buffer : public IBuffer
{
public:
	DX11Buffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc);
	~DX11Buffer();

	void* map(BufferMapping mapping) override;
	void  unmap() override;

	void updateSubresource(void* data, size_t size) override;

	ID3D11Buffer* getBuffer() { return m_buffer; }

private:
	ID3D11Buffer* m_buffer;

};

}

#endif // !RENDER_CORE_DX11_DX11BUFFER_H
