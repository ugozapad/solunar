#ifndef ENGINECORE_ENTITY_COMPONENT_H
#define ENGINECORE_ENTITY_COMPONENT_H

#include <atomic>

#include "core/reflection/itypedobject.h"

namespace solunar
{

class Entity;
class Level;

// Base class for entity component
class Component : public ITypedObject
{
	friend class Entity;
	friend class Level;
public:
	TYPEINFO_DECLARATION_ROOT(Component);

public:
	Component();
	virtual ~Component();

	void setActive(bool active);
	bool isActive();

	virtual void onEntitySet(Entity* entity);
	virtual void onLevelSet(Level* level);

	virtual void onEntityRemove();

	Entity* getEntity() { return m_entity; }

private:
	Entity* m_entity;
	Level* m_level;

	std::atomic<bool> m_isActive;
};

}

#endif // !COMPONENT_H
