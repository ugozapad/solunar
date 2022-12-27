#include "render/gl/glrenderer.h"

#include <Windows.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")

namespace solunar
{

GLRenderer::GLRenderer(GLFWwindow* window) :
	m_window(window)
{
	glfwMakeContextCurrent(window);
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
	return nullptr;
}

void GLRenderer::setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset)
{
}

void GLRenderer::setIndexBuffer(IBuffer* buffer)
{
}

IRenderer* createGLRenderer(GLFWwindow* window)
{
	return new GLRenderer(window);
}

}