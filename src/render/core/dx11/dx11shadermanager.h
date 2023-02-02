#ifndef RENDER_CORE_DX11_DX11SHADERMANAGER_H
#define RENDER_CORE_DX11_DX11SHADERMANAGER_H

#include <vector>

#include "render/core/ishadermanager.h"

namespace solunar
{

class DX11ShaderProgram;

class DX11ShaderManager : public IShaderManager
{
public:
	void init() override;
	void shutdown() override;

	static void setShaderProgram(DX11ShaderProgram* program);
	static void deleteProgram(DX11ShaderProgram* program);
};

}

#endif // !RENDER_CORE_DX11_DX11SHADERMANAGER_H
