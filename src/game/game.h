#ifndef GAME_GAME_H
#define GAME_GAME_H

struct GLFWwindow;

namespace solunar
{

// Forward declaration
class Level;
class Entity;
class CameraComponent;

class GameMain
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

extern GameMain* g_gameMain;

}

#endif // !GAME_GAME_H
