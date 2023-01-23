#include "game/render/gamerenderer.h"

#include "render/core/ibuffer.h"
#include "render/core/ishaderprogram.h"
#include "render/core/itexture.h"

#include "game/camera.h"

#include <glm/glm.hpp>

namespace solunar
{

extern void gameRendererTestInit();
extern void gameRendererTestShutdown();
extern void gameRendererTestRender(CameraComponent* cameraComponent);

GameRenderer* g_gameRenderer = nullptr;

void GameRenderer::init(GLFWwindow* window)
{
	// create render backend
	g_renderer = createGLRenderer(window);
	g_renderer->init();

	// Create some little test stuff...
	gameRendererTestInit();
}

void GameRenderer::shutdown()
{
	// Destroy test stuff...
	gameRendererTestShutdown();

	if (g_renderer)
	{
		g_renderer->shutdown();
		delete g_renderer;
		g_renderer = nullptr;
	}
}

void GameRenderer::testRender(CameraComponent* cameraComponent)
{
	g_renderer->beginFrame();

	// draw the test
	gameRendererTestRender(cameraComponent);

	// end frame (present)
	g_renderer->endFrame();
}

void GameRenderer::renderLevel(Level& level)
{
	
}

/////////////////////////////////////////////////////////////////////
// Test

// Data
struct GlobalData
{
	glm::fmat4 modelMatrix;
	glm::fmat4 viewMatrix;
	glm::fmat4 projectionMatrix;
};

// Globals
IBuffer* g_testVertexBuffer = nullptr;
IBuffer* g_testConstantBuffer = nullptr;
IShaderProgram* g_testShaderProg = nullptr;
GlobalData g_testGlobalData = {};

void gameRendererTestInit()
{
	// Vertex data
	float vertices[] = {
		// positions        // texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
	};

	// Create vertex buffer...
	BufferDesc vertexDesc = {};
	vertexDesc.m_bufferType = BufferType_VertexBuffer;
	vertexDesc.m_bufferAccess = BufferAccess_Default;
	vertexDesc.m_bufferMemorySize = sizeof(vertices);

	SubresourceDesc vertexResource = {};
	vertexResource.m_memory = vertices;

	g_testVertexBuffer = g_renderer->createBuffer(vertexDesc, vertexResource);

	// Create constant buffer...
	BufferDesc constantDesc = {};
	constantDesc.m_bufferType = BufferType_ConstantBuffer;
	constantDesc.m_bufferAccess = BufferAccess_Dynamic;
	constantDesc.m_bufferMemorySize = sizeof(g_testGlobalData);

	SubresourceDesc constantResource = {};
	constantResource.m_memory = &g_testGlobalData;

	g_testConstantBuffer = g_renderer->createBuffer(constantDesc, constantResource);
}

void gameRendererTestShutdown()
{
	if (g_testConstantBuffer)
	{
		delete g_testConstantBuffer;
		g_testConstantBuffer = nullptr;
	}

	if (g_testVertexBuffer)
	{
		delete g_testVertexBuffer;
		g_testVertexBuffer = nullptr;
	}
}

void gameRendererTestRender(CameraComponent* cameraComponent)
{
	uint32_t stride = sizeof(float) * 5;
	uint32_t offset = 0;
	g_renderer->setVertexBuffer(g_testVertexBuffer, stride, offset);

	g_renderer->setPrimitiveMode(PrimitiveMode_TriangleList);

	g_renderer->setShaderProgram(g_testShaderProg);
	g_renderer->setConstantBuffer(0, g_testConstantBuffer);

	// update constant buffer
	g_testGlobalData.modelMatrix = glm::fmat4(1.0f);
	g_testGlobalData.viewMatrix = glm::fmat4(1.0f);
	g_testGlobalData.projectionMatrix = glm::fmat4(1.0f);

	// push to gpu
	GlobalData* globalDataGPU = (GlobalData*)g_testConstantBuffer->map(BufferMapping_WriteDiscard);
	memcpy(globalDataGPU, &g_testGlobalData, sizeof(g_testGlobalData));
	g_testConstantBuffer->unmap();

	g_renderer->draw(4, 0);
}

}