#include "render/gl/glshaderprogram.h"
#include "core/filesystem/vfs.h"
#include "core/filesystem/file.h"

#include <fstream>
#include <string>

namespace solunar
{

GLuint createShader(GLenum target, const char* filename, const char* defines = nullptr)
{
	std::string content;

	IFile* f = VirtualFileSystem::getInstance()->openFile(filename);
	//assert(f->getHandle());

	f->seek(0, FileSeek_End);
	size_t fileLength = f->tell();
	f->seek(0, FileSeek_Begin);

	content.resize(fileLength + 1);
	f->read((void*)content.data(), fileLength);
	content[fileLength] = '\0';

	delete f;
	f = nullptr;

	if (defines && strlen(defines) > 0) {
		size_t versionLocation = content.find("#version 330 core");

		size_t definesStringLength = versionLocation + strlen("#version 330 core") + 2;
		std::string newContentString = content.substr(0, definesStringLength);

		newContentString.append(defines);
		newContentString.append(content.substr(definesStringLength));

		content = newContentString;
	}

	const char* contentCStr = content.c_str();

	GLuint shader = glCreateShader(target);
	glShaderSource(shader, 1, &contentCStr, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		//Logger::msg("=== SHADER COMPILE ERROR ===");
		//Logger::msg("%s", contentCStr);
		//Logger::msg("============================");
		//Core::error("createShader: failed to compile shader %s\n%s", filename, infoLog);
	}

	//Logger::msg("created %s shader from file %s", (target == GL_VERTEX_SHADER) ? "vertex" : "fragment", filename);

	return shader;
}

GLShaderProgram::GLShaderProgram(const char* name, const char* vsfilename, const char* fsfilename)
{
	m_file_name = strdup(name);
	m_defines = nullptr;

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vsfilename);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fsfilename);

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
		//Core::error("ShaderProgram::ShaderProgram: failed to link program %s", infoLog);
	}
}

GLShaderProgram::GLShaderProgram(const char* name, const char* vsfilename, const char* fsfilename, const char* defines)
{
	m_file_name = strdup(name);
	m_defines = strdup(defines);

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vsfilename, defines);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fsfilename, defines);

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
		//Core::error("ShaderProgram::ShaderProgram: failed to link program %s", infoLog);
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
