#include "enginecore/entity/component.h"
#include "enginecore/entity/entity.h"
#include "enginecore/entity/level.h"

namespace solunar
{

TYPEINFO_IMPLEMENTATION_ROOT(Component);

Component::Component()
{
	setActive(true);
}

Component::~Component()
{
}

void Component::setActive(bool active)
{
	m_isActive.store(active);
}

bool Component::isActive()
{
	return m_isActive.load();
}

void Component::onEntitySet(Entity* entity)
{
	m_entity = entity;
}

void Component::onLevelSet(Level* level)
{
	m_level = level;
}

void Component::onEntityRemove()
{
	m_entity = nullptr;
}

}