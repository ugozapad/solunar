#include <cstring>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/filesystem/file.h"
#include "core/filesystem/ifilesystem.h"
#include "core/filesystem/vfs.h"

#include "render/core/ibuffer.h"
#include "render/core/ishaderprogram.h"
#include "render/core/itexture.h"

#include "render/mesh.h"

#include "game/render/gamerenderer.h"
#include "game/camera.h"

namespace solunar
{

extern void gameRendererTestInit();
extern void gameRendererTestShutdown();
extern void gameRendererTestRender(CameraComponent* cameraComponent);

GameRenderer* g_gameRenderer = nullptr;

Mesh* g_testMesh = nullptr;

GLFWwindow* g_renderWindow = nullptr;

void GameRenderer::init(GLFWwindow* window)
{
	g_renderWindow = window;

	// create render backend
	// #TODO: Proper selection of renderer, for Windows only DX11
#ifdef WIN32
	g_renderer = createDX11Renderer(window);
#else
	g_renderer = createGLRenderer(window);
#endif // WIN32

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
IBuffer* g_testIndexBuffer = nullptr;
IBuffer* g_testConstantBuffer = nullptr;
IShaderProgram* g_testShaderProg = nullptr;
GlobalData g_testGlobalData = {};

void createGLShaderProg()
{
	IFile* shaderFile = VirtualFileSystem::getInstance()->openFile("/data/shaders/gl/test.glsl");
	if (!shaderFile) exit(-1);

	shaderFile->seek(0, FileSeek_End);
	size_t length = shaderFile->tell();
	shaderFile->seek(0, FileSeek_Begin);

	std::string shaderText;
	shaderText.resize(length + 1);
	shaderFile->read((void*)shaderText.data(), length);

	delete shaderFile;
	shaderFile = nullptr;

	std::string vertexShaderText = "#version 330 core\n";
	vertexShaderText += "#define VERTEX_SHADER\n";
	vertexShaderText += shaderText;

	ShaderCreationDesc vertexShaderCD = {};
	vertexShaderCD.m_shaderType = ShaderType_Vertex;
	vertexShaderCD.m_bytecode = vertexShaderText.c_str();
	vertexShaderCD.m_bytecodeLength = vertexShaderText.length();

	std::string pixelShaderText = "#version 330 core\n";
	pixelShaderText += "#define PIXEL_SHADER\n";
	pixelShaderText += shaderText;

	ShaderCreationDesc pixelShaderCD = {};
	pixelShaderCD.m_shaderType = ShaderType_Pixel;
	pixelShaderCD.m_bytecode = pixelShaderText.c_str();
	pixelShaderCD.m_bytecodeLength = pixelShaderText.length();

	std::vector<ShaderInputLayout> inputLayouts =
	{
		{ InputType_Vec3, "POSITION", 0, 0 },
		{ InputType_Vec3, "NORMAL", 0, 12 },
		{ InputType_Vec2, "TEXCOORD", 0, 24 }
	};

	g_testShaderProg = g_renderer->createShaderProgram(vertexShaderCD, pixelShaderCD, inputLayouts);
}

void createDX11ShaderProg()
{
	IFile* shaderFile = VirtualFileSystem::getInstance()->openFile("/data/shaders/dx11/test.hlsl");
	if (!shaderFile) exit(-1);

	shaderFile->seek(0, FileSeek_End);
	size_t length = shaderFile->tell();
	shaderFile->seek(0, FileSeek_Begin);

	std::string shaderText;
	shaderText.resize(length + 1);
	shaderFile->read((void*)shaderText.data(), length);

	delete shaderFile;
	shaderFile = nullptr;

	ShaderCreationDesc vertexShaderCD = {};
	vertexShaderCD.m_shaderType = ShaderType_Vertex;
	vertexShaderCD.m_bytecode = shaderText.c_str();
	vertexShaderCD.m_bytecodeLength = shaderText.length();

	ShaderCreationDesc pixelShaderCD = {};
	pixelShaderCD.m_shaderType = ShaderType_Pixel;
	pixelShaderCD.m_bytecode = shaderText.c_str();
	pixelShaderCD.m_bytecodeLength = shaderText.length();

	std::vector<ShaderInputLayout> inputLayouts =
	{
		{ InputType_Vec3, "POSITION", 0, 0 },
		{ InputType_Vec3, "NORMAL", 0, 12 },
		{ InputType_Vec2, "TEXCOORD", 0, 24 }
	};

	g_testShaderProg = g_renderer->createShaderProgram(vertexShaderCD, pixelShaderCD, inputLayouts);
}

void gameRendererTestInit()
{
	// Vertex data
	float vertices[] = {
		// positions           // texture coords
		 0.5f,  0.5f, 0.0f,    1.0f, -1.0f, // top right
		 0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,    0.0f, -1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Create vertex buffer...
	BufferDesc vertexDesc = {};
	vertexDesc.m_bufferType = BufferType_VertexBuffer;
	vertexDesc.m_bufferAccess = BufferAccess_Default;
	vertexDesc.m_bufferMemorySize = sizeof(vertices);

	SubresourceDesc vertexResource = {};
	vertexResource.m_memory = vertices;

	g_testVertexBuffer = g_renderer->createBuffer(vertexDesc, vertexResource);

	// Create index buffer...
	BufferDesc indicesBD = {};
	indicesBD.m_bufferType = BufferType_IndexBuffer;
	indicesBD.m_bufferAccess = BufferAccess_Default;
	indicesBD.m_bufferMemorySize = sizeof(indices);

	SubresourceDesc indicesSD = {};
	indicesSD.m_memory = indices;

	g_testIndexBuffer = g_renderer->createBuffer(indicesBD, indicesSD);

	// Create constant buffer...
	BufferDesc constantDesc = {};
	constantDesc.m_bufferType = BufferType_ConstantBuffer;
	constantDesc.m_bufferAccess = BufferAccess_Default;
	constantDesc.m_bufferMemorySize = sizeof(g_testGlobalData);

	SubresourceDesc constantResource = {};
	constantResource.m_memory = &g_testGlobalData;

	g_testConstantBuffer = g_renderer->createBuffer(constantDesc, constantResource);

	// Create shader program...

	// #TODO: REMOVE THIS AWFUL HACK
#ifdef WIN32
	createDX11ShaderProg();
#else
	createGLShaderProg();
#endif // WIN32 

	g_testMesh = new Mesh();
	g_testMesh->loadObj("data/models/test.obj");
}

void gameRendererTestShutdown()
{
	if (g_testMesh)
	{
		delete g_testMesh;
		g_testMesh = nullptr;
	}

	if (g_testShaderProg)
	{
		delete g_testShaderProg;
		g_testShaderProg = nullptr;
	}

	if (g_testConstantBuffer)
	{
		delete g_testConstantBuffer;
		g_testConstantBuffer = nullptr;
	}

	if (g_testIndexBuffer)
	{
		delete g_testIndexBuffer;
		g_testIndexBuffer = nullptr;
	}

	if (g_testVertexBuffer)
	{
		delete g_testVertexBuffer;
		g_testVertexBuffer = nullptr;
	}
}

void gameRendererTestRender(CameraComponent* cameraComponent)
{
	// set shader program and constant buffer
	g_renderer->setShaderProgram(g_testShaderProg);
	g_renderer->setConstantBuffer(0, g_testConstantBuffer);

	GlobalData globalData = {};
	globalData.modelMatrix = glm::mat4(1.0f);
	globalData.viewMatrix = cameraComponent->getViewMatrix();

	int width = 0, height = 0;
	glfwGetWindowSize(g_renderWindow, &width, &height);

	float aspect = (float)width / (float)height;
	globalData.projectionMatrix = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);

	// push to gpu
	g_testConstantBuffer->updateSubresource(&globalData, sizeof(globalData));

	// draw test mesh
	g_testMesh->draw();
}

}