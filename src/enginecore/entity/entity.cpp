#include "enginecore/entity/entity.h"
#include "enginecore/entity/component.h"
#include "enginecore/entity/level.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace solunar
{

TYPEINFO_IMPLEMENTATION_ROOT(Entity);

Entity::Entity() 
{
	m_rootEntity = nullptr;
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Entity::~Entity()
{
	for (auto& it : m_components)
	{
		it->onEntityRemove();
		it = nullptr;
	}

	m_components.clear();

	m_children.clear();

	m_level = nullptr;

	m_rootEntity = nullptr;
}

void Entity::setRotation(glm::vec3& rot)
{
	m_rotation = rot;
}

glm::mat4 Entity::getWorldTranslation()
{
	glm::mat4 tranlation = glm::mat4(1.0f);
	return tranlation;
}

glm::mat4 Entity::getLocalTranslation()
{
	glm::mat4 tranlation = glm::mat4(1.0f);
	return tranlation;
}

Component* Entity::getComponentByTypeInfo(const TypeInfo* typeinfo)
{
	for (ComponentIt it = m_components.begin(); it != m_components.end(); ++it)
	{
		std::shared_ptr<Component> component = *it;

		if (component)
		{
			const TypeInfo* typeInfo = component->getTypeInfo();
			if (typeInfo && typeInfo->isExactly(typeInfo))
				return component.get();
		}
	}

	return nullptr;
}

void Entity::setRootEntity(Entity* Entity)
{
	m_rootEntity = Entity;
}

void Entity::onLevelSet(Level* level)
{
	m_level = level;
}

Entity* Entity::createChild()
{
	Entity* entity = m_level->createEntity();
	entity->setRootEntity(this);
	return entity;
}


}