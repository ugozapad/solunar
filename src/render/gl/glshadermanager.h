#ifndef RENDER_GL_GLSHADERMANAGER_H
#define RENDER_GL_GLSHADERMANAGER_H

#include <vector>

namespace solunar
{

class GLShaderProgram;

class GLShaderManager
{
public:
	void init();
	void shutdown();

	static void setShaderProgram(GLShaderProgram* program);

	GLShaderProgram* createShaderProgram(const char* name, const char* vsfilename, const char* fsfilename);
	GLShaderProgram* createShaderProgram(const char* name, const char* vsfilename, const char* fsfilename, const char* defines);
	GLShaderProgram* createShaderProgram(const char* name);

	static void deleteProgram(GLShaderProgram* program);

private:
	std::vector<GLShaderProgram*> m_programs;
};

extern GLShaderManager* g_shaderManager;

}

#endif // !RENDER_GL_GLSHADERMANAGER_H
