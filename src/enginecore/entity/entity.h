#ifndef ENGINECORE_ENTITY_ENTITY_H
#define ENGINECORE_ENTITY_ENTITY_H

#include <stdint.h>

namespace solunar
{

const int kInvalidEntityHandle = -1;

class Entity
{
public:
	Entity(const uint64_t handle);
	~Entity();

	const uint64_t getHandle() const { return m_handle; }

	bool isValidHandle() const { return m_handle != kInvalidEntityHandle; }

private:
	uint64_t m_handle;

};

}

#endif // !ENGINECORE_ENTITY_ENTITY_H
