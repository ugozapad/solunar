#ifndef ENGINECORE_ENTITY_ICOMPONENTSYSTEM_H
#define ENGINECORE_ENTITY_ICOMPONENTSYSTEM_H

namespace solunar
{

class IComponentSystem
{
public:
	virtual ~IComponentSystem() {}

	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void update() = 0;
};

}

#endif // !ENGINECORE_ENTITY_ICOMPONENTSYSTEM_H
