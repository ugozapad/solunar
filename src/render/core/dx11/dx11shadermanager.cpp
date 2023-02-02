#include <cstddef>
#include <cstdio>

#include "render/core/dx11/dx11renderer.h"
#include "render/core/dx11/dx11shadermanager.h"
#include "render/core/dx11/dx11shaderprogram.h"

namespace solunar
{

// Table for all sized of InputType
const size_t g_inputTypeSizeTable[InputType_MAX] =
{
	0, // InputType_None

	1,	// InputType_Float
	2,	// InputType_Vec2
	3,	// InputType_Vec3
	4	// InputType_Vec4
};

void DX11ShaderManager::init()
{
}

void DX11ShaderManager::shutdown()
{
}

void DX11ShaderManager::setShaderProgram(DX11ShaderProgram* program)
{
	// #TODO: REFACTOR
	if (program)
	{
		g_dx11Renderer->getDeviceContext()->IASetInputLayout(program->m_inputLayout);
		g_dx11Renderer->getDeviceContext()->VSSetShader(program->m_vertexShader, NULL, 0);
		g_dx11Renderer->getDeviceContext()->PSSetShader(program->m_pixelShader, NULL, 0);
	}
	else
	{
		g_dx11Renderer->getDeviceContext()->IASetInputLayout(NULL);
		g_dx11Renderer->getDeviceContext()->VSSetShader(NULL, NULL, 0);
		g_dx11Renderer->getDeviceContext()->PSSetShader(NULL, NULL, 0);
	}
}

void DX11ShaderManager::deleteProgram(DX11ShaderProgram* program)
{
	if (program) {
		delete program;
	}
}

}
