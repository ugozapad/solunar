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

	Entity createEntity();
	Entity getEntity(uint64_t entityId);

	const std::vector<Entity>& getEntities() { return m_entities; }

private:
	std::vector<Entity> m_entities;
	uint64_t m_entitiesCount;

};

}

#endif // !ENGINECORE_ENTITY_ENTITYMANAGER_H
