#include "game/render/gamerenderer.h"

namespace solunar
{

GameRenderer* g_gameRenderer = nullptr;

void GameRenderer::init(GLFWwindow* window)
{
	// create render backend
	g_renderer = createGLRenderer(window);
	g_renderer->init();
}

void GameRenderer::shutdown()
{
	if (g_renderer)
	{
		g_renderer->shutdown();
		delete g_renderer;
		g_renderer = nullptr;
	}
}

void GameRenderer::testRender()
{
	g_renderer->beginFrame();

	// end frame (present)
	g_renderer->endFrame();
}

void GameRenderer::renderLevel(Level& level)
{
	EntityManager& entityManager = level.getEntityManager();
	const std::vector<Entity>& entities = entityManager.getEntities();

	for (auto& it : entities)
	{
		if (it.isValidHandle())
		{

		}
	}
}

}