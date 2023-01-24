#ifndef ENGINECORE_ENTITY_ENTITY_H
#define ENGINECORE_ENTITY_ENTITY_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "core/reflection/itypedobject.h"

namespace solunar
{

class Level;
class Component;

class Entity : public ITypedObject
{
	friend class Level;
public:
	TYPEINFO_DECLARATION_ROOT(Entity);

public:
	Entity();
	~Entity();

	virtual void onLevelSet(Level* level);

	void setRootEntity(Entity* node);

	glm::vec3 getPosition()	const	{ return m_position; }
	glm::vec3 getRotation()	const	{ return m_rotation; }
	glm::vec3 getScale()	const	{ return m_scale; }

	void setPosition(const glm::vec3& pos) { m_position = pos; }
	void setRotation(const glm::vec3 & rot);
	void setScale(const glm::vec3& scale) { m_scale = scale; }

	glm::mat4 getWorldTranslation();
	glm::mat4 getLocalTranslation();

	Entity* createChild();

	Component* createComponentByTypeInfo(const TypeInfo* typeinfo);

	template <typename T>
	T* createComponent();

	Component* getComponentByTypeInfo(const TypeInfo* typeinfo);

	template <typename T>
	T* getComponent();

private:
	typedef std::list<Component*>::iterator ComponentIt;
	std::list<Component*> m_components;

	typedef std::list<Entity*>::iterator EntityIt;
	std::list<Entity*> m_children;

	Level* m_level;

	Entity* m_rootEntity;

	//glm::quat m_rotation;
	glm::vec3 m_rotation;
	glm::vec3 m_position;
	glm::vec3 m_scale;
};

template<typename T>
inline T* Entity::createComponent()
{
	return (T*)createComponentByTypeInfo(get_type_info<T>());
}

template<typename T>
inline T* Entity::getComponent()
{
	return (T*)getComponentByTypeInfo(get_type_info<T>());
}

}

#endif