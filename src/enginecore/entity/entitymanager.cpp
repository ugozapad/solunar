#include "enginecore/entity/entitymanager.h"

namespace solunar
{

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

Entity* EntityManager::createEntity()
{
	Entity* entity = new Entity();
	m_entities.push_back(entity);
	return entity;
}

}