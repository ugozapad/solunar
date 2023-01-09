#include <cstddef>
#include <cstdio>

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

void GLShaderManager::init()
{
	int maxVertexUniformBlocks = 0;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxVertexUniformBlocks);
	printf("max vertex uniform blocks %i\n", maxVertexUniformBlocks);
}

void GLShaderManager::shutdown()
{
}

void GLShaderManager::setShaderProgram(GLShaderProgram* program)
{
	// #TODO: REFACTOR
	if (program)
	{
		// apply vertex attributes
		const std::vector<ShaderInputLayout>& inputLayouts = program->m_shaderInputLayout;
		const int inputLayoutsCount = inputLayouts.size();

		size_t inputLayoutElementsCount = 0;
		for (int i = 0; i < inputLayoutsCount; i++)
			inputLayoutElementsCount += g_inputTypeSizeTable[inputLayouts[i].m_semanticType];

		size_t appliedOffset = 0;
		for (int i = 0; i < inputLayoutsCount; i++)
		{
			const ShaderInputLayout& layout = inputLayouts[i];
			const size_t& elementSize = g_inputTypeSizeTable[layout.m_semanticType];

			// #TODO: Only float now
			if (appliedOffset > 0)
				glVertexAttribPointer(i, elementSize, GL_FLOAT, GL_FALSE, inputLayoutElementsCount * sizeof(float), (void*)(appliedOffset * sizeof(float)));
			else
				glVertexAttribPointer(i, elementSize, GL_FLOAT, GL_FALSE, inputLayoutElementsCount * sizeof(float), (void*)0);
			
			glEnableVertexAttribArray(i);

			appliedOffset += elementSize;
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
