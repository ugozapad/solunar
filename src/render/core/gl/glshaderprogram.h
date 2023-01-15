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

	//////////////////////////////////////////////////////////////////////////
	// Applying shader uniforms as slot index
	void setTextureSampler(int slot, const char* name);

	void setInteger(int slot, int value);
	void setFloat(int slot, float value);

	//void setVector3(int slot, const glm::vec3& vector);
	//void setMatrix4(int slot, const glm::mat4& matrix);
	//////////////////////////////////////////////////////////////////////////

	uint32_t getUniformLocation(const char* uniform_name);

private:
	std::vector<ShaderInputLayout> m_shaderInputLayout;
	uint32_t m_program;
};

}

#endif // !RENDER_GL_GLSHADERPROGRAM_H