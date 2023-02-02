#include <GLFW/glfw3.h>

#include "enginecore/entity/level.h"
#include "enginecore/entity/entity.h"
#include "enginecore/entity/component.h"
#include "enginecore/entity/componentfactory.h"

#include "game/game.h"
#include "game/render/gamerenderer.h"
#include "game/camera.h"

namespace solunar
{

// Input globals

static bool g_keys[460] = {0};
static float g_mouseX;
static float g_mouseY;
static float g_deltaMouseX;
static float g_deltaMouseY;

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	g_keys[key] = action;
}

void mouseCursorPosCallback(GLFWwindow* window, double x, double y)
{
	g_deltaMouseX = (float)x - g_mouseX;
	g_deltaMouseY = (float)y - g_mouseY;

	g_mouseX = (float)x;
	g_mouseY = (float)y;
}

class GameMain : public IGameMain
{
public:
	GameMain();
	~GameMain();

	void init(GLFWwindow* window);
	void shutdown();
	void update();

private:
	void registerComponents();

private:
	GLFWwindow* m_window;

	Level* m_level;
	Entity* m_cameraEntity;
	CameraComponent* m_cameraComponent;
};

IGameMain* getGameMain()
{
	static GameMain s_gameMain;
	return &s_gameMain;
}

GameMain::GameMain() :
	m_window(nullptr),
	m_level(nullptr),
	m_cameraEntity(nullptr),
	m_cameraComponent(nullptr)
{
}

GameMain::~GameMain()
{
}

void GameMain::init(GLFWwindow* window)
{
	m_window = window;

	// Set window input callbacks
	glfwSetKeyCallback(m_window, keyboardCallback);
	glfwSetCursorPosCallback(m_window, mouseCursorPosCallback);

	// Register game component
	registerComponents();

	// Create game renderer
	g_gameRenderer = new GameRenderer();
	g_gameRenderer->init(m_window);

	// Create level
	m_level = new Level();

	// Create camera entity
	m_cameraEntity = m_level->createEntity();

	// Create camera component
	m_cameraComponent = m_cameraEntity->createComponent<CameraComponent>();
}

void GameMain::shutdown()
{
	// Delete camera component
	if (m_cameraComponent)
	{
		m_cameraComponent = nullptr;
	}

	// Delete camera entity
	if (m_cameraEntity)
	{
		delete m_cameraEntity;
		m_cameraEntity = nullptr;
	}

	// Delete level
	if (m_level)
	{
		delete m_level;
		m_level = nullptr;
	}

	if (g_gameRenderer)
	{
		g_gameRenderer->shutdown();
		delete g_gameRenderer;
		g_gameRenderer = nullptr;
	}

	m_window = nullptr;
}

void GameMain::update()
{
	if (g_keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);

	// update camera
	static float yaw = -90.0f;
	static float pitch = 0.0f;

	yaw += g_deltaMouseX * 0.1f;;
	pitch += g_deltaMouseY * 0.1f;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	//printf("yaw = %f\npitch = %f\n", yaw, pitch);

	glm::vec3 lookAt = glm::vec3(yaw, pitch, 0.0);
	static glm::vec3 eye = glm::vec3(0.0f);

	float speed = 2.0f * 0.002f;

	if (g_keys[GLFW_KEY_W])
		eye += speed * glm::normalize(lookAt);
	if (g_keys[GLFW_KEY_S])
		eye -= speed * glm::normalize(lookAt);

	m_cameraComponent->setLookAt(glm::vec3(yaw, pitch, 0.0f));
	m_cameraComponent->setEye(eye);

	// render stuff
	g_gameRenderer->testRender(m_cameraComponent);
}

void GameMain::registerComponents()
{
	g_componentFactory->registerComponent<CameraComponent>();
}

}