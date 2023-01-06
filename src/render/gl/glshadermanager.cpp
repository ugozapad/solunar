#include "render/gl/glshadermanager.h"
#include "render/gl/glshaderprogram.h"

namespace solunar
{

// Table for all sized of InputType
const size_t g_inputTypeSizeTable[InputType_MAX] =
{
	0, // InputType_None

	1,	// InputType_Float
	2,	// InputType_Vec2
	3,	// InputType_Vec3
	4	// InputType_Vec4
};


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
}

void GLShaderManager::setShaderProgram(GLShaderProgram* program)
{
	if (program)
	{
		// apply vertex attributes
		const std::vector<ShaderInputLayout>& inputLayouts = program->m_shaderInputLayout;
		const int inputLayoutsCount = inputLayouts.size();
		size_t appliedOffset = 0;
		for (int i = 0; i < inputLayoutsCount; i++)
		{
			const ShaderInputLayout& layout = inputLayouts[i];
			const size_t& elementSize = g_inputTypeSizeTable[layout.m_semanticType];

			// #TODO: Only float now
			glVertexAttribPointer(i, elementSize, GL_FLOAT, GL_FALSE, (elementSize * sizeof(float)) + layout.m_offset, (void*)0);
			glEnableVertexAttribArray(i);
		}
	}

	glUseProgram(program ? program->m_program : 0);
}

void GLShaderManager::deleteProgram(GLShaderProgram* program)
{
	if (program) {
		delete program;
	}
}

}
