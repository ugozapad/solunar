#include "enginecore/engine.h"
#include "enginecore/entity/componentfactory.h"

namespace solunar
{

// Global instance
Engine g_engine;

// Singleton
Engine* Engine::instance()
{
	return &g_engine;
}

void Engine::init(/*IGameMain* gameMain*/)
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