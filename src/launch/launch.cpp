#include <GLFW/glfw3.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // WIN32

#include "core/filesystem/vfs.h"
#include "core/filesystem/ifilesystem.h"

#ifdef WIN32
#include "core/filesystem/filesystem_win32.h"
#endif // WIN32

#include "render/irenderer.h"

int main(int argc, char* argv[])
{
	using namespace solunar;

	if (!glfwInit())
		return -1;

	// Initialize file system for platform
#ifdef WIN32
	char currentDirectory[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentDirectory);

	g_fileSystem = new FileSystemWin32(currentDirectory);
#endif // WIN32

	// Mount root filesystem
	VirtualFileSystem::getInstance()->mount("/", g_fileSystem);

	// Set up window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// Create window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Solunar Engine", nullptr, nullptr);
	if (!window)
		return -1;

	// Initialize renderer
	g_renderer = createGLRenderer(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		// engine and render code here...
		g_renderer->beginFrame();
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