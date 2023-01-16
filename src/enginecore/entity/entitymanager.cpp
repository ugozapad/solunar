#include "enginecore/entity/entitymanager.h"

namespace solunar
{

EntityManager::EntityManager() :
	m_entitiesCount(0)
{
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::createEntity()
{
	Entity entity(m_entitiesCount++);
	return entity;
}

Entity EntityManager::getEntity(uint64_t entityId)
{
	for (auto& it : m_entities)
		if (it.getHandle() == entityId)
			return it;

	return Entity(kInvalidEntityHandle);
}

}