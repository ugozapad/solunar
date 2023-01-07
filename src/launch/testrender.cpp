#define TESTRENDER

#ifdef TESTRENDER
#include <GLFW/glfw3.h>

#include "core/filesystem/vfs.h"
#include "core/filesystem/file.h"
#include "core/filesystem/ifilesystem.h"

#if defined(_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "core/filesystem/filesystem_win32.h"
#elif defined(__unix__)
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include "core/filesystem/filesystem_unix.h"
#endif // defined(WINDOWS)

#include "render/irenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace solunar
{

// Global variables
IShaderProgram* g_shaderProgram = nullptr;
IBuffer* g_vertexBuffer = nullptr;
IBuffer* g_indexBuffer = nullptr;
ITexture2D* g_texture = nullptr;
IBuffer* g_constantBuffer = nullptr;

void createShaderProg()
{
	IFile* shaderFile = VirtualFileSystem::getInstance()->openFile("/data/shaders/test.glsl");
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
		{ InputType_Vec2, "TEXCOORD", 0, 12 },
	};

	g_shaderProgram = g_renderer->createShaderProgram(vertexShaderCD, pixelShaderCD, inputLayouts);
}

}

struct GlobalData
{
	float modelMatrix[4][4];
};

int main(int argc, char* argv[])
{
	using namespace solunar;

	if (!glfwInit())
		return -1;

	// Initialize file system for platform
#if defined(_WINDOWS)
	char currentDirectory[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDirectory);

	g_fileSystem = new FileSystemWin32(currentDirectory);
#elif defined(__unix__)
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return -1; // failed to get current working directory

	g_fileSystem = new FileSystemUnix(cwd);
#endif // defined(WINDOWS)

	// Mount root filesystem
	VirtualFileSystem::getInstance()->mount("/", g_fileSystem);

	// Set up window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// Disable window resize
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Solunar Engine", nullptr, nullptr);
	if (!window)
		return -1;

	// Initialize renderer
	g_renderer = createGLRenderer(window);

	// Create shader program from file
	createShaderProg();
	
	float vertices[] = {
		// positions           // texture coords
		 0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,    0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	GlobalData globalData = { 
		{ 1.0f, 0.0f, 0.0f, 0.0f,
		  0.0f, 1.0f, 0.0f, 0.0f,
		  0.0f, 0.0f, 1.0f, 0.0f,
		  0.0f, 0.0f, 0.0f, 1.0f }
	};

	// Create vertex buffer
	BufferDesc bd = {};
	bd.m_bufferType = BufferType_VertexBuffer;
	bd.m_bufferAccess = BufferAccess_Default;
	bd.m_bufferMemorySize = sizeof(vertices);

	SubresourceDesc sd = {};
	sd.m_memory = vertices;

	g_vertexBuffer = g_renderer->createBuffer(bd, sd);

	// Create indices buffer
	BufferDesc indicesBD = {};
	indicesBD.m_bufferType = BufferType_IndexBuffer;
	indicesBD.m_bufferAccess = BufferAccess_Default;
	indicesBD.m_bufferMemorySize = sizeof(indices);

	SubresourceDesc indicesSD = {};
	indicesSD.m_memory = indices;

	g_indexBuffer = g_renderer->createBuffer(indicesBD, indicesSD);

	// Create constant buffer
	BufferDesc constantBD = {};
	constantBD.m_bufferType = BufferType_ConstantBuffer;
	constantBD.m_bufferAccess = BufferAccess_Dynamic;
	constantBD.m_bufferMemorySize = sizeof(globalData);

	SubresourceDesc constantSD = {};
	constantSD.m_memory = &globalData;

	g_constantBuffer = g_renderer->createBuffer(constantBD, constantSD);

	int width = 0, height = 0, channels = 0;
	uint8_t* imageData = stbi_load("data/textures/test.png", &width, &height, &channels, STBI_rgb);
	if (!imageData) return -1;

	TextureDesc textureDesc = {};
	textureDesc.m_textureType = TextureType_Texture2D;
	textureDesc.m_width = width;
	textureDesc.m_height = height;
	textureDesc.m_mipmapLevel = 1;
	textureDesc.m_format = PixelFormat_RGB8;

	SubresourceDesc textureSD = {};
	textureSD.m_memory = imageData;

	g_texture = g_renderer->createTexture2D(textureDesc, textureSD);
	
	// free loaded texture
	stbi_image_free(imageData);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		g_renderer->beginFrame();

		uint32_t stride = sizeof(float);
		uint32_t offset = 0;
		g_renderer->setVertexBuffer(g_vertexBuffer, stride, offset);

		g_renderer->setShaderProgram(g_shaderProgram);

		g_renderer->setIndexBuffer(g_indexBuffer);

		g_renderer->setConstantBuffer(0, g_constantBuffer);
		g_renderer->setTexture2D(0, g_texture);

		g_renderer->setPrimitiveMode(PrimitiveMode_TriangleList);
		g_renderer->drawIndexed(6, 0, 0);

		g_renderer->endFrame();
	}

	// Delete renderer
	delete g_renderer;
	g_renderer = nullptr;

	// Delete filesystem
	delete g_fileSystem;
	g_fileSystem = nullptr;

	glfwTerminate();

	return 0;
}
#endif // TESTRENDER
