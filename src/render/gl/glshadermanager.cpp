#include "render/gl/glshadermanager.h"
#include "render/gl/glshaderprogram.h"

namespace solunar
{

GLShaderManager* g_shaderManager = nullptr;

void GLShaderManager::init()
{
	//Logger::msg("Initialize shader manager ...");

	int maxVertexUniformBlocks = 0;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxVertexUniformBlocks);
	//Logger::msg("max vertex uniform blocks %i", maxVertexUniformBlocks);
}

void GLShaderManager::shutdown()
{
	for (std::vector<GLShaderProgram*>::iterator it = m_programs.begin(); it != m_programs.end(); ++it) {
		if (*it) {
			deleteProgram(*it);
		}
	}

	m_programs.clear();
}

void GLShaderManager::setShaderProgram(GLShaderProgram* program)
{
	glUseProgram(program ? program->m_program : 0);
}

GLShaderProgram* GLShaderManager::createShaderProgram(const char* name, const char* vsfilename, const char* fsfilename)
{
	for (std::vector<GLShaderProgram*>::iterator it = m_programs.begin(); it != m_programs.end(); ++it) {
		if (strcmp((*it)->m_file_name, name) == 0 && (*it)->m_defines == nullptr) {
			return (*it);
		}
	}

	GLShaderProgram* program = new GLShaderProgram(name, vsfilename, fsfilename);
	m_programs.push_back(program);
	return program;
}

GLShaderProgram* GLShaderManager::createShaderProgram(const char* name, const char* vsfilename, const char* fsfilename, const char* defines)
{
	for (std::vector<GLShaderProgram*>::iterator it = m_programs.begin(); it != m_programs.end(); ++it) {
		if (strcmp((*it)->m_file_name, name) == 0 && (*it)->m_defines && strcmp((*it)->m_defines, defines) == 0) {
			return (*it);
		}
	}

	GLShaderProgram* program = new GLShaderProgram(name, vsfilename, fsfilename, defines);
	m_programs.push_back(program);
	return program;
}

GLShaderProgram* GLShaderManager::createShaderProgram(const char* name)
{
	for (std::vector<GLShaderProgram*>::iterator it = m_programs.begin(); it != m_programs.end(); ++it) {
		if (strcmp((*it)->m_file_name, name) == 0) {
			return (*it);
		}
	}

	//Core::error("ShaderManager::createShaderProgram: failed to create shader %s, because them doesnt exist", name);

	return nullptr;
}

void GLShaderManager::deleteProgram(GLShaderProgram* program)
{
	if (program) {
		delete program;
	}
}


}
