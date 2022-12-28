#ifndef RENDER_GL_GLSHARED_H
#define RENDER_GL_GLSHARED_H

#include <glad/glad.h>

#include "render/buffer.h"
#include "render/texture.h"

namespace solunar
{

GLenum getBufferType(BufferType type);
GLenum getBufferAccess(BufferAccess access);
GLenum getBufferMapping(BufferMapping mapping);

class IGLBufferBase : public IBuffer
{
public:
	virtual ~IGLBufferBase() {}

	virtual void bind() = 0;
};

}

#endif // !RENDER_GL_GLSHARED_H
