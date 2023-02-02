#ifndef RENDER_CORE_DX11_DX11TEXTURE_H
#define RENDER_CORE_DX11_DX11TEXTURE_H

#include "render/core/itexture.h"
#include "render/core/ibuffer.h"

#include <d3d11.h>

namespace solunar
{

class DX11Texture2D : public ITexture2D
{
public:
	DX11Texture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc);
	~DX11Texture2D();

	ID3D11Texture2D* getTexture() { return m_texture; }
	ID3D11ShaderResourceView* getShaderResourceView() { return m_shaderResourceView; }

private:
	ID3D11Texture2D* m_texture;
	ID3D11ShaderResourceView* m_shaderResourceView;
};

}

#endif // !RENDER_CORE_DX11_DX11TEXTURE_H
