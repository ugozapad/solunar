#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string.h>
#include <stdio.h>

#include "render/core/gl/glrenderer.h"
#include "render/core/gl/glbuffer.h"
#include "render/core/gl/glshadermanager.h"
#include "render/core/gl/glshaderprogram.h"
#include "render/core/gl/gltexture2d.h"

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

void GLRenderer::init()
{
	// Create shader manager for GL
	g_shaderManager = new GLShaderManager();
	g_shaderManager->init();
}

void GLRenderer::shutdown()
{
	// Destroy shader manager
	if (g_shaderManager)
	{
		g_shaderManager->shutdown();

		delete g_shaderManager;
		g_shaderManager = nullptr;
	}
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
	//glDrawElements(m_primitiveMode, indicesCount, GL_UNSIGNED_INT, 0);
	glDrawElementsBaseVertex(m_primitiveMode, indicesCount, GL_UNSIGNED_INT, 0, baseVertexLocation);
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
		return new GLBuffer(bufferDesc, subresourceDesc);
	case BufferType_IndexBuffer:
		return new GLBuffer(bufferDesc, subresourceDesc);
	case BufferType_ConstantBuffer:
		return new GLBuffer(bufferDesc, subresourceDesc);
	default:
		break;
	}
	return nullptr;
}

void GLRenderer::setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset)
{
	GLBuffer* bufferBase = (GLBuffer*)buffer;
	if (bufferBase)
		glBindBuffer(GL_ARRAY_BUFFER, bufferBase->getHandle());
	else
		glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLRenderer::setIndexBuffer(IBuffer* buffer)
{
	GLBuffer* bufferBase = (GLBuffer*)buffer;
	if (bufferBase)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferBase->getHandle());
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
	GLBuffer* uniformBuffer = (GLBuffer*)constantBuffer;
	if (uniformBuffer)
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, uniformBuffer->getHandle());
	else
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, 0);
}

ITexture2D* GLRenderer::createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc)
{
	return new GLTexture2D(textureDesc, subresourceDesc);
}

void GLRenderer::setTexture2D(uint32_t slot, ITexture2D* texture)
{
	GLTexture2D* gltexture = (GLTexture2D*)texture;
	if (gltexture)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, gltexture->getTextureHandle());
	}
	else
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
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