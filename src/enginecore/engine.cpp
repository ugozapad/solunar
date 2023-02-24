#include "enginecore/engine.h"
#include "enginecore/entity/componentfactory.h"

namespace solunar
{

// Singleton
Engine* Engine::getInstance()
{
	static Engine engine;
	return &engine;
}

void Engine::init()
{
	// Create component factory
	g_componentFactory = new ComponentFactory();

	// Register some stuff ...
}

void Engine::shutdown()
{
	if (g_componentFactory)
	{
		delete g_componentFactory;
		g_componentFactory = nullptr;
	}
}

}