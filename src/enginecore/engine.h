#ifndef ENGINECORE_ENGINE_H
#define ENGINECORE_ENGINE_H

namespace solunar
{

class Engine
{
public:
	//! Singleton
	static Engine* getInstance();

public:
	void init();
	void shutdown();
};

}

#endif