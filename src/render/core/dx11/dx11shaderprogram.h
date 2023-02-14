#ifndef RENDER_CORE_DX11_DX11SHADERPROGRAM_H
#define RENDER_CORE_DX11_DX11SHADERPROGRAM_H

#include <vector>

#include <d3d11.h>

#include "render/core/ishaderprogram.h"

namespace solunar
{

class DX11ShaderManager;

class DX11ShaderProgram : public IShaderProgram
{
	friend class DX11ShaderManager;
public:
	DX11ShaderProgram(const char* vstext, const char* pstext, const std::vector<ShaderInputLayout>& inputLayouts);
	~DX11ShaderProgram();

	void createInputLayout(ID3DBlob* vertexShaderBlob, const std::vector<ShaderInputLayout>& inputLayouts);

private:
	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

};

}

#endif // !RENDER_CORE_DX11_DX11SHADERPROGRAM_H