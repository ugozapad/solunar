#ifndef CORE_REFLECTION_H
#define CORE_REFLECTION_H

namespace solunar
{

typedef void* (*CreateObject_t)();

class TypeInfo
{
public:
	TypeInfo(const char* name, const TypeInfo* baseTypeInfo);
	~TypeInfo();

	const char* getName() const;

	bool isExactly(const TypeInfo* typeinfo) const;
	bool isDerived(const TypeInfo* typeinfo) const;

	template <typename T>
	inline bool isKindOf();

private:
	const TypeInfo* m_baseTypeInfo;
	const char* m_name;
};

template<typename T>
inline bool TypeInfo::isKindOf()
{
	return isDerived(&T::ms_typeInfo);
}

// Type info implementation
#define TYPEINFO_DECLARATION_ROOT(CLASS) \
	static TypeInfo ms_typeInfo; \
	virtual TypeInfo* getTypeInfo() { return &ms_typeInfo; }

#define TYPEINFO_IMPLEMENTATION_ROOT(CLASS) \
	TypeInfo CLASS::ms_typeInfo(#CLASS, nullptr)

#define TYPEINFO_DECLARATION(CLASS, INHERITCLASS) \
	static TypeInfo ms_typeInfo; \
	virtual TypeInfo* getTypeInfo() { return &ms_typeInfo; }

#define TYPEINFO_IMPLEMENTATION(CLASS, INHERITCLASS) \
	TypeInfo CLASS::ms_typeInfo(#CLASS, &INHERITCLASS::ms_typeInfo)

}

#endif