#ifndef CORE_REFLECTION_ITYPEDOBJECT_H
#define CORE_REFLECTION_ITYPEDOBJECT_H

#include "core/reflection/typeinfo.h"

namespace solunar
{

class ITypedObject
{
public:
	virtual ~ITypedObject() {}

	virtual TypeInfo* getTypeInfo() = 0;

	template <typename T>
	inline bool isKindOf();

	template <typename T>
	inline bool isExactlyKindOf();
};

template<typename T>
inline bool ITypedObject::isKindOf()
{
	return getTypeInfo()->isDerived(&T::ms_typeInfo);
}

template<typename T>
inline bool ITypedObject::isExactlyKindOf()
{
	return getTypeInfo()->isExactly(&T::ms_typeInfo);
}

// Dynamic cast implementation
template <typename T>
inline T* dynamicCast(const ITypedObject* typedObject)
{
	return typedObject && typedObject->isKindOf<T>() ? (T*)typedObject : nullptr;
}

template <typename T>
inline const T* dynamicCast(const ITypedObject* typedObject)
{
	return typedObject && typedObject->isKindOf<T>() ? (T*)typedObject : nullptr;
}

template <typename T>
inline const TypeInfo* get_type_info()
{
	return &T::ms_typeInfo;
}

}

#endif