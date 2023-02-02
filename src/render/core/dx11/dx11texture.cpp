#include "render/core/dx11/dx11renderer.h"
#include "render/core/dx11/dx11texture.h"


namespace solunar
{

const char* g_pixelFormatStrings[PixelFormat_Max] =
{
	"PixelFormat_Unknown",

	// Usigned char formats
	"PixelFormat_R8",
	"PixelFormat_RGB8",
	"PixelFormat_RGBA8",
};

const char* g_texturesTypeString[TextureType_Texture2D + 1] =
{
	"TextureType_Unknown",
	"TextureType_Texture2D"
};

DXGI_FORMAT getDxgiFormat(PixelFormat format)
{
	switch (format)
	{
	case PixelFormat_R8:
		return DXGI_FORMAT_R8_UNORM;

	case PixelFormat_RGBA8:
		return DXGI_FORMAT_R8G8B8A8_UNORM;

	default:
		break;
	}

	return DXGI_FORMAT_UNKNOWN;
}


DX11Texture2D::DX11Texture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc)
{
	UINT formatSupported = 0;
	if (g_dx11Renderer->getDevice()->CheckFormatSupport(getDxgiFormat(textureDesc.m_format), &formatSupported) != S_OK)
	{
		char buffer[512];
		sprintf(buffer, "DX11Texture2D::DX11Texture2D: failed to create texture, format %s is unsupported.",
			g_pixelFormatStrings[textureDesc.m_format]);

		printf("%s\n", buffer);

		// #TODO: make our debug break but it's enough now
		DebugBreak();
	}

	D3D11_TEXTURE2D_DESC texture2DDesc;
	memset(&texture2DDesc, 0, sizeof(texture2DDesc));
	texture2DDesc.Width = textureDesc.m_width;
	texture2DDesc.Height = textureDesc.m_height;
	texture2DDesc.MipLevels = (textureDesc.m_mipmapLevel < 1 ? 1 : textureDesc.m_mipmapLevel);
	texture2DDesc.ArraySize = 1;
	texture2DDesc.Format = getDxgiFormat(textureDesc.m_format);
	texture2DDesc.SampleDesc.Count = 1;
	texture2DDesc.Usage = D3D11_USAGE_DEFAULT;
	texture2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture2DDesc.CPUAccessFlags = 0; // can't write in to texture now :(
	texture2DDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData;
	memset(&subresourceData, 0, sizeof(subresourceData));
	subresourceData.pSysMem = subresourceDesc.m_memory;
	subresourceData.SysMemPitch = subresourceDesc.m_memoryPitch;
	subresourceData.SysMemSlicePitch = subresourceDesc.m_memorySlicePitch;

	// Create texture
	HRESULT hr = g_dx11Renderer->getDevice()->CreateTexture2D(&texture2DDesc, subresourceDesc.m_memory ? &subresourceData : NULL, &m_texture);

#if 0
	// format debug info
	char buffer[512];
	snprintf(buffer, sizeof(buffer), "%s:%s", g_texturesTypeString[textureDesc.m_textureType],
		g_pixelFormatStrings[textureDesc.m_format]);

	// and add it to texture
	m_texture->SetPrivateData(WKPDID_D3DDebugObjectName, strlen(buffer), buffer);

#endif

	// Create shader resource view of our texture
	hr = g_dx11Renderer->getDevice()->CreateShaderResourceView((ID3D11Resource*)m_texture, NULL, &m_shaderResourceView);
}

DX11Texture2D::~DX11Texture2D()
{
	if (m_shaderResourceView)
	{
		m_shaderResourceView->Release();
		m_shaderResourceView = nullptr;
	}

	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

}