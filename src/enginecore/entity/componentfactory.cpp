#include "enginecore/entity/componentfactory.h"

namespace solunar
{

ComponentFactory* g_componentFactory = nullptr;

void ComponentFactory::registerComponent(const TypeInfo* typeinfo, CreateComponentFunc_t createFunc)
{
	m_factories.emplace(typeinfo, createFunc);
}

ITypedObject* ComponentFactory::createComponentByTypeInfo(const TypeInfo* typeInfo)
{
	for (auto it : m_factories)
	{
		if (it.first->isExactly(typeInfo))
			return it.second();
	}

	return nullptr;
}

}