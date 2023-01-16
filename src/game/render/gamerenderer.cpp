#include "game/render/gamerenderer.h"

namespace solunar
{

void GameRenderer::init(GLFWwindow* window)
{
	// create render backend
	g_renderer = createGLRenderer(window);
}

void GameRenderer::shutdown()
{
	if (g_renderer)
	{
		delete g_renderer;
		g_renderer = nullptr;
	}
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