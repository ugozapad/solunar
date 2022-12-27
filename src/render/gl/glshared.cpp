#include "render/gl/glshared.h"

namespace solunar
{

GLenum getBufferType(BufferType type)
{
	switch (type)
	{
	case BufferType_VertexBuffer:
		return GL_ARRAY_BUFFER;
	case BufferType_IndexBuffer:
		return GL_ELEMENT_ARRAY_BUFFER;
	case BufferType_ConstantBuffer:
		return GL_UNIFORM_BUFFER;
	default:
		break;
	}

	return 0;
}

GLenum getBufferAccess(BufferAccess access)
{
	switch (access)
	{
	case BufferAccess_Default:
		return GL_STATIC_DRAW;
	case BufferAccess_Dynamic:
		return GL_STREAM_DRAW;
	default:
		break;
	}

	return 0;
}

GLenum getBufferMapping(BufferMapping mapping)
{
	switch (mapping)
	{
	case BufferMapping_Read:
		return GL_READ_ONLY;
	case BufferMapping_Write:
		return GL_WRITE_ONLY;
	case BufferMapping_WriteDiscard:
		return GL_WRITE_ONLY;
	case BufferMapping_ReadAndWrite:
		return GL_READ_WRITE;
	default:
		break;
	}

	return 0;
}

}