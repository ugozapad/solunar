#include <cstddef>

#include <fstream>
#include <string>

#include "d3dcompiler.h"

#include "render/core/dx11/dx11renderer.h"
#include "render/core/dx11/dx11shaderprogram.h"

namespace solunar
{

extern void debugSaveBytecode(ID3DBlob* blob);

ID3DBlob* createShaderFromText(const char* text, ShaderType shaderType)
{
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorTextBlob = nullptr;

	const char* entryPoint = (shaderType == ShaderType_Vertex) ? "VSMain" : "PSMain";
	const char* shaderTarget = (shaderType == ShaderType_Vertex) ? "vs_5_0" : "ps_5_0";

	HRESULT hr = D3DCompile(text, strlen(text), "UNKNOWED", NULL, NULL, entryPoint, shaderTarget, 0, 0, &shaderBlob, &errorTextBlob);
	if (FAILED(hr))
	{
		std::string errorText = "Failed to compile shader!";

		if (errorTextBlob)
		{
			errorText += "\n";
			errorText += "Reason: ";
			errorText += (const char*)errorTextBlob->GetBufferPointer();
			errorText += "\n";

			errorTextBlob->Release();
			errorTextBlob = nullptr;
		}
		else
		{
			errorText += "\n";
			errorText += "Reason: Unknown";
			errorText += "\n";
		}

		printf("%s", errorText.c_str());

		DebugBreak();
	}

	if (errorTextBlob)
	{
		errorTextBlob->Release();
		errorTextBlob = nullptr;
	}

	return shaderBlob;
}

DX11ShaderProgram::DX11ShaderProgram(const char* vstext, const char* pstext, const std::vector<ShaderInputLayout>& inputLayouts) :
	m_inputLayout(nullptr),
	m_vertexShader(nullptr),
	m_pixelShader(nullptr)
{
	ID3DBlob* vertexShaderBlob = createShaderFromText(vstext, ShaderType_Vertex);
	g_dx11Renderer->getDevice()->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_vertexShader);

	createInputLayout(vertexShaderBlob, inputLayouts);

	// save bytecode
	debugSaveBytecode(vertexShaderBlob);

	vertexShaderBlob->Release();
	vertexShaderBlob = nullptr;

	ID3DBlob* pixelShaderBlob = createShaderFromText(pstext, ShaderType_Pixel);
	g_dx11Renderer->getDevice()->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), NULL, &m_pixelShader);

	pixelShaderBlob->Release();
	pixelShaderBlob = nullptr;
}

DX11ShaderProgram::~DX11ShaderProgram()
{
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = nullptr;
	}

	if (m_inputLayout)
	{
		m_inputLayout->Release();
		m_inputLayout = nullptr;
	}

	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = nullptr;
	}
}

void DX11ShaderProgram::createInputLayout(ID3DBlob* vertexShaderBlob, const std::vector<ShaderInputLayout>& inputLayouts)
{
	// #TODO: convert engine inputLayouts to D3D11 input layout

	// Reflect shader info
	ID3D11ShaderReflection* shaderReflection = nullptr;
	D3DReflect(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&shaderReflection);

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	shaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	uint32_t byteOffset = 0;
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (uint32_t i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		shaderReflection->GetInputParameterDesc(i, &paramDesc);

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = 0;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = byteOffset;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			byteOffset += 4;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			byteOffset += 8;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			byteOffset += 12;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			byteOffset += 16;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	g_dx11Renderer->getDevice()->CreateInputLayout(&inputLayoutDesc[0], (UINT)inputLayoutDesc.size(), vertexShaderBlob->GetBufferPointer(), 
		vertexShaderBlob->GetBufferSize(), &m_inputLayout);

	shaderReflection->Release();
}

void DX11ShaderProgram::setTextureSampler(int slot, const char * name)
{
	DebugBreak();
}

void DX11ShaderProgram::setInteger(int slot, int value)
{
	DebugBreak();
}

void DX11ShaderProgram::setFloat(int slot, float value)
{
	DebugBreak();
}

uint32_t DX11ShaderProgram::getUniformLocation(const char * uniform_name)
{
	DebugBreak();
	return -1;
}

}
