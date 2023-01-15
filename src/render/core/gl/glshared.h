#ifndef RENDER_GL_GLSHARED_H
#define RENDER_GL_GLSHARED_H

#include <glad/glad.h>

#include "render/core/ibuffer.h"
#include "render/core/itexture.h"

namespace solunar
{

GLenum getBufferType(BufferType type);
GLenum getBufferAccess(BufferAccess access);
GLenum getBufferMapping(BufferMapping mapping);

}

#endif // !RENDER_GL_GLSHARED_H
