#include "enginecore/entity/entity.h"

namespace solunar
{

Entity::Entity(const uint64_t handle) :
	m_handle(handle)
{
}

Entity::~Entity()
{
}

}