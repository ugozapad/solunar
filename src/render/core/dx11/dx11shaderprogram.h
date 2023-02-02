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

	virtual void setTextureSampler(int slot, const char * name) override;
	virtual void setInteger(int slot, int value) override;
	virtual void setFloat(int slot, float value) override;

	virtual uint32_t getUniformLocation(const char * uniform_name) override;

};

}

#endif // !RENDER_CORE_DX11_DX11SHADERPROGRAM_H