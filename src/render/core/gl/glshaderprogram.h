#ifndef RENDER_GL_GLSHADERPROGRAM_H
#define RENDER_GL_GLSHADERPROGRAM_H

#include <vector>

#include "render/core/ishaderprogram.h"
#include "render/core/gl/glshared.h"

namespace solunar
{

class GLShaderManager;

class GLShaderProgram : public IShaderProgram
{
	friend class GLShaderManager;
public:
	GLShaderProgram(const char* vstext, const char* pstext, const std::vector<ShaderInputLayout>& inputLayouts);
	~GLShaderProgram();

private:
	std::vector<ShaderInputLayout> m_shaderInputLayout;
	uint32_t m_program;
};

}

#endif // !RENDER_GL_GLSHADERPROGRAM_H