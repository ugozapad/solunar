#include "enginecore/entity/level.h"

namespace solunar
{

TYPEINFO_IMPLEMENTATION_ROOT(Level);

Level::Level()
{
}

Level::~Level()
{
}

Entity* Level::createEntity()
{
	return m_entityManager.createEntity();
}

}