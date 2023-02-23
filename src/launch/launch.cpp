#include <GLFW/glfw3.h>

#include "core/filesystem/vfs.h"
#include "core/filesystem/ifilesystem.h"

#if defined(_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "core/filesystem/filesystem_win32.h"
#else
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include "core/filesystem/filesystem_unix.h"
#endif // defined(WINDOWS)

// Engine include
#include "enginecore/engine.h"

// Game includes
#include "game/game.h"

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
#else
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

	// Initialize engine
	Engine::instance()->init();

	// Create game instance
	g_gameMain = new GameMain();

	// Initialize game
	g_gameMain->init(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		// Update game
		g_gameMain->update();
	}

	// Shutdown game
	g_gameMain->shutdown();

	// Delete game
	if (g_gameMain)
	{
		delete g_gameMain;
		g_gameMain = nullptr;
	}

	// Shutdown engine
	Engine::instance()->shutdown();

	// Delete filesystem
	delete g_fileSystem;
	g_fileSystem = nullptr;

	glfwTerminate();

	return 0;
}
