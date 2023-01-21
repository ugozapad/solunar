#include "game/game.h"
#include "game/render/gamerenderer.h"

#include "enginecore/entity/level.h"
#include "enginecore/entity/entity.h"
#include "enginecore/entity/component.h"

namespace solunar
{

class GameMain : public IGameMain
{
public:
	GameMain();
	~GameMain();

	void init(GLFWwindow* window);
	void shutdown();
	void update();

private:
	Level* m_level;
	Entity* m_cameraEntity;
};

IGameMain* getGameMain()
{
	static GameMain s_gameMain;
	return &s_gameMain;
}

GameMain::GameMain() :
	m_level(nullptr),
	m_cameraEntity(nullptr)
{
}

GameMain::~GameMain()
{
}

void GameMain::init(GLFWwindow* window)
{
	g_gameRenderer = new GameRenderer();
	g_gameRenderer->init(window);

	// Create level
	m_level = new Level();

	// Create camera entity
	m_cameraEntity = m_level->createEntity();
}

void GameMain::shutdown()
{
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
		delete g_gameRenderer;
		g_gameRenderer = nullptr;
	}
}

void GameMain::update()
{
	// render stuff
	g_gameRenderer->testRender();
}

}