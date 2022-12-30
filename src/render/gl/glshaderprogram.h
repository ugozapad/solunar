#ifndef RENDER_GL_GLSHADERPROGRAM_H
#define RENDER_GL_GLSHADERPROGRAM_H

#include "render/ishaderprogram.h"
#include "render/gl/glshared.h"

namespace solunar
{

class GLShaderManager;

class GLShaderProgram : public IShaderProgram
{
	friend class GLShaderManager;
public:
	GLShaderProgram(const char* name, const char* vsfilename, const char* fsfilename);
	GLShaderProgram(const char* name, const char* vsfilename, const char* fsfilename, const char* defines);

	GLShaderProgram(const char* vstext, const char* pstext);

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
	const char* m_file_name;
	const char* m_defines;
	uint32_t m_program;
};

}

#endif // !RENDER_GL_GLSHADERPROGRAM_H