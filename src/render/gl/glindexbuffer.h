#ifndef INDEXOBJECT_H
#define INDEXOBJECT_H

class Render;

class ENGINE_API IndexBuffer
{
	friend class Render;
public:
	~IndexBuffer();

	void bind();

private:
	IndexBuffer(void* data, size_t size, bool isStream = false);

	uint32_t m_buffer;
};

#endif // !INDEXOBJECT_H
