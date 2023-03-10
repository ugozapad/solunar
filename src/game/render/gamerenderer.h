#ifndef GAME_RENDER_GAMERENDERER_H
#define GAME_RENDER_GAMERENDERER_H

#include "enginecore/entity/level.h"

#include "render/core/irenderer.h"

namespace solunar
{

class CameraComponent;

class GameRenderer
{
public:
	void init(GLFWwindow* window);
	void shutdown();

	void testRender(CameraComponent* cameraComponent);

	void renderLevel(Level& level);
};

extern GameRenderer* g_gameRenderer;

}

#endif // !GAME_RENDER_GAMERENDERER_H
