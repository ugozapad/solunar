#include <cstddef>

#include "render/core/gl/glshaderprogram.h"
#include "core/filesystem/vfs.h"
#include "core/filesystem/file.h"

#include <fstream>
#include <string>

namespace solunar
{

GLuint createShaderFromText(GLenum target, const char* text)
{
	GLuint shader = glCreateShader(target);
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("createShaderFromText: failed to compile shader %s\n", infoLog);
	}

	return shader;
}

GLShaderProgram::GLShaderProgram(const char* vstext, const char* pstext, const std::vector<ShaderInputLayout>& inputLayouts) :
	m_shaderInputLayout(inputLayouts)
{
	GLuint vertexShader = createShaderFromText(GL_VERTEX_SHADER, vstext);
	GLuint fragmentShader = createShaderFromText(GL_FRAGMENT_SHADER, pstext);

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_program, 512, NULL, infoLog);
		printf("GLShaderProgram::GLShaderProgram: failed to link program %s\n", infoLog);
	}
}

GLShaderProgram::~GLShaderProgram()
{
	glDeleteProgram(m_program);
}

}
