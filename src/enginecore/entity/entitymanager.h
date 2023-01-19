#ifndef ENGINECORE_ENTITY_ENTITYMANAGER_H
#define ENGINECORE_ENTITY_ENTITYMANAGER_H

#include <vector>

#include "enginecore/entity/entity.h"

namespace solunar
{

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* createEntity();

private:
	std::vector<Entity*> m_entities;
};

}

#endif // !ENGINECORE_ENTITY_ENTITYMANAGER_H
