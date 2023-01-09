#ifndef RENDER_GL_GLSHADERMANAGER_H
#define RENDER_GL_GLSHADERMANAGER_H

#include <vector>

#include "render/ishadermanager.h"

namespace solunar
{

class GLShaderProgram;

class GLShaderManager : public IShaderManager
{
public:
	void init() override;
	void shutdown() override;

	static void setShaderProgram(GLShaderProgram* program);
	static void deleteProgram(GLShaderProgram* program);
};

}

#endif // !RENDER_GL_GLSHADERMANAGER_H
