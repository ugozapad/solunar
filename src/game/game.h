#ifndef GAME_GAME_H
#define GAME_GAME_H

struct GLFWwindow;

namespace solunar
{

class IGameMain
{
public:
	virtual void init(GLFWwindow* window) = 0;
	virtual void shutdown() = 0;
	virtual void update() = 0;
};

IGameMain* getGameMain();

}

#endif // !GAME_GAME_H
