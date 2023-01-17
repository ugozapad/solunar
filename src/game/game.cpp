#include "game/game.h"
#include "game/render/gamerenderer.h"

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
};

IGameMain* getGameMain()
{
	static GameMain s_gameMain;
	return &s_gameMain;
}

GameMain::GameMain()
{
}

GameMain::~GameMain()
{
}

void GameMain::init(GLFWwindow* window)
{
	g_gameRenderer = new GameRenderer();
	g_gameRenderer->init(window);
}

void GameMain::shutdown()
{
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