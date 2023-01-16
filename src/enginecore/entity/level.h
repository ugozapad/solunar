#ifndef ENGINECORE_ENTITY_LEVEL_H
#define ENGINECORE_ENTITY_LEVEL_H

#include "core/reflection/itypedobject.h"

#include "enginecore/entity/entity.h"
#include "enginecore/entity/entitymanager.h"

namespace solunar
{

class Level : public ITypedObject
{
public:
	TYPEINFO_DECLARATION_ROOT(Level);

public:
	Level();
	~Level();

	Entity createEntity();

	EntityManager& getEntityManager() { return m_entityManager; }

private:
	EntityManager m_entityManager;
};

}

#endif // !ENGINECORE_ENTITY_LEVEL_H
