#ifndef RENDER_GL_GLSHARED_H
#define RENDER_GL_GLSHARED_H

#include <glad/glad.h>

#include "render/ibuffer.h"
#include "render/itexture.h"

namespace solunar
{

GLenum getBufferType(BufferType type);
GLenum getBufferAccess(BufferAccess access);
GLenum getBufferMapping(BufferMapping mapping);

}

#endif // !RENDER_GL_GLSHARED_H
