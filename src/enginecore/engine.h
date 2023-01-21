#ifndef ENGINECORE_ENGINE_H
#define ENGINECORE_ENGINE_H

namespace solunar
{

// Forward declaration
class IGameMain;

class Engine
{
public:
	//! Singleton
	static Engine* instance();

public:
	void init(/*IGameMain* gameMain*/);
	void shutdown();
};

}

#endif