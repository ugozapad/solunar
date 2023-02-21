#include "render/core/dx11/dx11samplerstate.h"

namespace solunar
{

// ANGLE - renderer11_utils.cpp - ConvertFilter
// https://chromium.googlesource.com/angle/angle/+/563e45aabaed2bba173236f0b9d47eaacb2a813a/src/libANGLE/renderer/d3d/d3d11/renderer11_utils.cpp
D3D11_FILTER getD3D11Filter(const SamplerDesc& samplerDesc)
{
	if (samplerDesc.m_anisotropyLevel > 1.0f)
		return D3D11_ENCODE_ANISOTROPIC_FILTER(FALSE);

	TextureFilter ourMinFilter = samplerDesc.m_minFilter;
	TextureFilter ourMagFilter = samplerDesc.m_magFilter;

	D3D11_FILTER_TYPE minFilter;
	D3D11_FILTER_TYPE mipFilter;
	
	switch (ourMinFilter)
	{
	case TextureFilter_Nearest:
		minFilter = D3D11_FILTER_TYPE_POINT;
		mipFilter = D3D11_FILTER_TYPE_POINT;
		break;

	case TextureFilter_Linear:
		minFilter = D3D11_FILTER_TYPE_LINEAR;
		mipFilter = D3D11_FILTER_TYPE_POINT;
		break;

	case TextureFilter_NearestMipmapNearest:
		minFilter = D3D11_FILTER_TYPE_POINT;
		mipFilter = D3D11_FILTER_TYPE_POINT;
		break;

	case TextureFilter_LinearMipmapNearest:
		minFilter = D3D11_FILTER_TYPE_LINEAR;
		mipFilter = D3D11_FILTER_TYPE_POINT;
		break;

	case TextureFilter_NearestMipmapLinear:
		minFilter = D3D11_FILTER_TYPE_POINT;
		mipFilter = D3D11_FILTER_TYPE_LINEAR;
		break;

	case TextureFilter_LinearMipmapLinear:
		minFilter = D3D11_FILTER_TYPE_LINEAR;
		mipFilter = D3D11_FILTER_TYPE_LINEAR;
		break;

	default:
		break;
	}

	D3D11_FILTER_TYPE magFilter;
	switch (ourMagFilter)
	{
	case TextureFilter_Nearest:
		magFilter = D3D11_FILTER_TYPE_POINT;
		break;

	case TextureFilter_Linear:
		magFilter = D3D11_FILTER_TYPE_LINEAR;
		break;

	default:
		break;
	}

	return D3D11_ENCODE_BASIC_FILTER(minFilter, magFilter, mipFilter, FALSE);
}

D3D11_TEXTURE_ADDRESS_MODE getD3D11AddressMode(TextureWrap textureWrap)
{
	switch (textureWrap)
	{
	case TextureWrap_Repeat:
		return D3D11_TEXTURE_ADDRESS_WRAP;

	case TextureWrap_MirroredRepeat:
		return D3D11_TEXTURE_ADDRESS_MIRROR;

	case TextureWrap_ClampToEdge:
		return D3D11_TEXTURE_ADDRESS_CLAMP;

	case TextureWrap_ClampToBorder:
		return D3D11_TEXTURE_ADDRESS_BORDER;

	default:
		break;
	}

	return (D3D11_TEXTURE_ADDRESS_MODE)0;
}

DX11SamplerState::DX11SamplerState(const SamplerDesc& samplerDesc) :
    m_samplerState(nullptr)
{
	create(samplerDesc);
}

DX11SamplerState::~DX11SamplerState()
{
	destroy();
}

void DX11SamplerState::create(const SamplerDesc& samplerDesc)
{
	D3D11_SAMPLER_DESC d3d11SamplerDesc;
	memset(&d3d11SamplerDesc, 0, sizeof(d3d11SamplerDesc));
	d3d11SamplerDesc.Filter = getD3D11Filter(samplerDesc);
	d3d11SamplerDesc.AddressU = getD3D11AddressMode(samplerDesc.m_wrapS);
	d3d11SamplerDesc.AddressV = getD3D11AddressMode(samplerDesc.m_wrapT);
	d3d11SamplerDesc.AddressW = getD3D11AddressMode(samplerDesc.m_wrapRepeat);
	d3d11SamplerDesc.MaxAnisotropy = samplerDesc.m_anisotropyLevel;

	g_dx11Renderer->getDevice()->CreateSamplerState(&d3d11SamplerDesc, &m_samplerState);
}

void DX11SamplerState::destroy()
{
    if (m_samplerState)
    {
        m_samplerState->Release();
        m_samplerState = nullptr;
    }
}

}