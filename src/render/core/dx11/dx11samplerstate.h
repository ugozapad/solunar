#ifndef RENDER_CORE_DX11_DX11SAMPLERSTATE_H
#define RENDER_CORE_DX11_DX11SAMPLERSTATE_H

#include "render/core/itexture.h"
#include "render/core/dx11/dx11renderer.h"

namespace solunar
{

class DX11SamplerState : public ISamplerState
{
public:
	DX11SamplerState(const SamplerDesc& samplerDesc);
	~DX11SamplerState();

	void create(const SamplerDesc& samplerDesc);
	void destroy();

	ID3D11SamplerState* getSamplerState() { return m_samplerState; }

private:
	ID3D11SamplerState* m_samplerState;
};


}

#endif // !RENDER_CORE_DX11_DX11SAMPLERSTATE_H
