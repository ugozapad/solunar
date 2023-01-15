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

//////////////////////////////////////////////////////////////////////////
void GLShaderProgram::setTextureSampler(int slot, const char* name)
{
	glUniform1i(getUniformLocation(name), slot);
}

void GLShaderProgram::setInteger(int slot, int value)
{
	glUniform1i(slot, value);
}

void GLShaderProgram::setFloat(int slot, float value)
{
	glUniform1f(slot, value);
}

//void ShaderProgram::setVector3(int slot, const glm::vec3& vector)
//{
//	glUniform3fv(slot, 1, glm::value_ptr(vector));
//}
//
//void ShaderProgram::setMatrix4(int slot, const glm::mat4& matrix)
//{
//	glUniformMatrix4fv(slot, 1, GL_FALSE, glm::value_ptr(matrix));
//}
//////////////////////////////////////////////////////////////////////////

uint32_t GLShaderProgram::getUniformLocation(const char* uniform_name)
{
	return glGetUniformLocation(m_program, uniform_name);
}

}
