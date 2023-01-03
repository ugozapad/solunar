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
	static void deleteProgram(GLShaderProgram* program);
};

extern GLShaderManager* g_shaderManager;

}

#endif // !RENDER_GL_GLSHADERMANAGER_H
