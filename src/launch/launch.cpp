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
	VFS::getInstance()->mount("/", g_fileSystem);

	// Create window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Solunar Engine", nullptr, nullptr);
	if (!window)
		return -1;

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		// engine and render code here...
	}

	// Delete filesystem
	delete g_fileSystem;

	glfwTerminate();

	return 0;
}