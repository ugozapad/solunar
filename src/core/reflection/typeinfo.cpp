#include "core/reflection/typeinfo.h"

namespace solunar
{

TypeInfo::TypeInfo(const char* name, const TypeInfo* baseTypeInfo) :
	m_name(name),
	m_baseTypeInfo(baseTypeInfo)
{
}

TypeInfo::~TypeInfo()
{
}

const char* TypeInfo::getName() const
{
	return m_name;
}

bool TypeInfo::isExactly(const TypeInfo* typeinfo) const
{
	return typeinfo == this;
}

bool TypeInfo::isDerived(const TypeInfo* typeinfo) const
{
	const TypeInfo* search = this;
	while (search)
	{
		if (search == typeinfo)
			return true;

		search = search->m_baseTypeInfo;
	}

	return false;
}

}