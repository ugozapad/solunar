#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/gl/glrenderer.h"
#include "render/gl/glvertexbuffer.h"
#include "render/gl/glindexbuffer.h"

namespace solunar
{

GLRenderer::GLRenderer(GLFWwindow* window) :
	m_window(window)
{
	glfwMakeContextCurrent(window);

	// Load OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// do something we in trouble :(((
	}
}

GLRenderer::~GLRenderer()
{
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

IBuffer* GLRenderer::createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	switch (bufferDesc.m_bufferType)
	{
	case BufferType_VertexBuffer:
		return new GLVertexBuffer(bufferDesc, subresourceDesc);
	case BufferType_IndexBuffer:
		return new GLIndexBuffer(bufferDesc, subresourceDesc);
	case BufferType_ConstantBuffer:
		break;
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

IRenderer* createGLRenderer(GLFWwindow* window)
{
	return new GLRenderer(window);
}

}