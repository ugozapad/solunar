#ifndef RENDER_GL_GLTEXTURE2D_H
#define RENDER_GL_GLTEXTURE2D_H

#include "render/core/itexture.h"
#include "render/core/gl/glshared.h"

namespace solunar
{

class GLTexture2D : public ITexture2D
{
public:
	GLTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc);

	void setInitialFilter();

	~GLTexture2D();

	GLuint getTextureHandle() { return m_textureHandle; }

private:
	GLuint m_textureHandle;
};

}

#endif // !RENDER_GL_GLTEXTURE2D_H
