#ifndef ENGINECORE_ENTITY_COMPONENTFACTORY_H
#define ENGINECORE_ENTITY_COMPONENTFACTORY_H

#include <unordered_map>

#include "enginecore/entity/component.h"

namespace solunar
{

//! Callback type for component creation
typedef ITypedObject* (*CreateComponentFunc_t)();

//! Template component creation function
template <typename T>
ITypedObject* createComponentTempated()
{
	return (ITypedObject*)new T();
}

/**
	Component factory class.
*/
class ComponentFactory
{
public:
	//! Register component
	void registerComponent(const TypeInfo* typeinfo, CreateComponentFunc_t createFunc);

	//! Template wrapper on registerComponent
	template <typename T>
	void registerComponent();

	//! Create component by TypeInfo
	ITypedObject* createComponentByTypeInfo(const TypeInfo* typeInfo);

	//! Template wrapper on createComponentByTypeInfo
	template <typename T>
	T* createComponent();

private:
	std::unordered_map<const TypeInfo*, CreateComponentFunc_t> m_factories;

};

extern ComponentFactory* g_componentFactory;

template<typename T>
void ComponentFactory::registerComponent()
{
	// our typeinfo
	const TypeInfo* typeInfo = getTypeInfo<T>();

	// our function
	CreateComponentFunc_t createComponentFunc = (CreateComponentFunc_t)createComponentTempated<T>();

	// register component
	registerComponent(typeInfo, createComponentFunc);
}

template <typename T>
T* ComponentFactory::createComponent()
{
	// our typeinfo
	const TypeInfo* typeInfo = getTypeInfo<T>();

	auto factory = m_factories.find(typeInfo);
	if (factory == m_factories.end())
		return nullptr;

	return (T*)(*factory).second();
}

}

#endif // !ENTITY_COMPONENTFACTORY_H
