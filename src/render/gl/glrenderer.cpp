#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string.h>
#include <stdio.h>

#include "render/gl/glrenderer.h"
#include "render/gl/glvertexbuffer.h"
#include "render/gl/glindexbuffer.h"
#include "render/gl/glshadermanager.h"
#include "render/gl/glshaderprogram.h"
#include "render/gl/gltexture2d.h"
#include "render/gl/gluniformbuffer.h"

namespace solunar
{

GLRenderer::GLRenderer(GLFWwindow* window) :
	m_window(window),
	m_renderFeature(GLRenderFeature_None),
	m_separatedShaderObjects(GLShaderFeature_None),
	m_primitiveMode(0),
	m_vertexArraysObject(0)
{
	glfwMakeContextCurrent(window);

	// Load OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// do something we in trouble :(((
	}

	initRenderFeatures();

	glGenVertexArrays(1, &m_vertexArraysObject);
	glBindVertexArray(m_vertexArraysObject);
}

GLRenderer::~GLRenderer()
{
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vertexArraysObject);	
}

void GLRenderer::initialize()
{
}

void GLRenderer::shutdown()
{
}

void GLRenderer::beginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5f, 0.5, 0.5f, 1.0f);
}

void GLRenderer::endFrame()
{
	glfwSwapBuffers(m_window);
}

void GLRenderer::draw(uint32_t verticesCount, uint32_t startVertexLocation)
{
	glDrawArrays(m_primitiveMode, startVertexLocation, verticesCount);
}

void GLRenderer::drawIndexed(uint32_t indicesCount, uint32_t startIndexLocation, int32_t baseVertexLocation)
{
	glDrawElements(m_primitiveMode, indicesCount, GL_UNSIGNED_INT, 0);
}

void GLRenderer::setPrimitiveMode(PrimitiveMode primitiveMode)
{
	if (primitiveMode == PrimitiveMode_TriangleList)
		m_primitiveMode = GL_TRIANGLES;
}

IBuffer* GLRenderer::createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	switch (bufferDesc.m_bufferType)
	{
	case BufferType_VertexBuffer:
		return new GLVertexBuffer(bufferDesc, subresourceDesc);
	case BufferType_IndexBuffer:
		return new GLIndexBuffer(bufferDesc, subresourceDesc);
	case BufferType_ConstantBuffer:
		return new GLUniformBuffer(bufferDesc, subresourceDesc);
	default:
		break;
	}
	return nullptr;
}

void GLRenderer::setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset)
{
	IGLBufferBase* bufferBase = (IGLBufferBase*)buffer;
	if (bufferBase)
		bufferBase->bind();
	else
		glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLRenderer::setIndexBuffer(IBuffer* buffer)
{
	IGLBufferBase* bufferBase = (IGLBufferBase*)buffer;
	if (bufferBase)
		bufferBase->bind();
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IShaderProgram* GLRenderer::createShaderProgram(const ShaderCreationDesc& vertexShaderDesc, const ShaderCreationDesc& pixelShaderDesc, const std::vector<ShaderInputLayout>& inputLayouts)
{
	return new GLShaderProgram((const char*)vertexShaderDesc.m_bytecode, (const char*)pixelShaderDesc.m_bytecode, inputLayouts);
}

void GLRenderer::setShaderProgram(IShaderProgram* shaderProgram)
{
	GLShaderProgram* glshaderProgram = (GLShaderProgram*)shaderProgram;
	if (glshaderProgram)
		GLShaderManager::setShaderProgram(glshaderProgram);
	else
		GLShaderManager::setShaderProgram(nullptr);
}

void GLRenderer::setConstantBuffer(uint32_t slot, IBuffer* constantBuffer)
{
	GLUniformBuffer* uniformBuffer = (GLUniformBuffer*)constantBuffer;
	if (uniformBuffer)
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, uniformBuffer->getHandle());
	else
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, 0);
}

ITexture2D* GLRenderer::createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc)
{
	return new GLTexture2D(textureDesc, subresourceDesc);
}

void GLRenderer::initRenderFeatures()
{
	//////////////////////////////////////////////////////////////////////////
	// Direct State Access

	// Try to find EXT_direct_state_access or ARB_direct_state_access
	if (findExtension("GL_EXT_direct_state_access"))
		m_renderFeature = GLRenderFeature_EXTDSA;
	if (findExtension("GL_ARB_direct_state_access"))
		m_renderFeature = GLRenderFeature_ARBDSA;

	// log what we found
	if (m_renderFeature == GLRenderFeature_ARBDSA)
		printf("found ARB_direct_state_access\n");
	else if (m_renderFeature == GLRenderFeature_EXTDSA)
		printf("found EXT_direct_state_access\n");
	else
		printf("not found any direct state access extension\n");

	//////////////////////////////////////////////////////////////////////////
	// Separated shader objects

	// Try to find EXT_separate_shader_objects or ARB_separate_shader_objects
	if (findExtension("GL_EXT_separate_shader_objects"))
		m_separatedShaderObjects = GLShaderFeature_EXTSeparated;
	if (findExtension("GL_ARB_separate_shader_objects"))
		m_separatedShaderObjects = GLShaderFeature_ARBSeparated;

	// log what we found
	if (m_separatedShaderObjects == GLShaderFeature_ARBSeparated)
		printf("found ARB_separate_shader_objects\n");
	else if (m_separatedShaderObjects == GLShaderFeature_EXTSeparated)
		printf("found EXT_separate_shader_objects\n");
	else
		printf("not found any separated shader objects extension\n");
}

bool GLRenderer::findExtension(const char* name)
{
	GLint extensionCount = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &extensionCount);

	for (int i = 0; i < extensionCount; i++) {
		const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
		if (strcmp(extension, name) == 0)
			return true;
	}

	return false;
}

IRenderer* createGLRenderer(GLFWwindow* window)
{
	return new GLRenderer(window);
}

}