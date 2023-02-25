#include "render/core/gl/gltexture2d.h"

namespace solunar
{

GLenum getGLFormat(PixelFormat format)
{
	switch (format)
	{
	case PixelFormat_R8:
		return GL_RED;
	case PixelFormat_RGB8:
		return GL_RGB;
	case PixelFormat_RGBA8:
		return GL_RGBA;
	default:
		break;
	}

	return 0;
}

GLenum getGLInternalFormat(PixelFormat format)
{
	switch (format)
	{
	case PixelFormat_R8:
		return GL_RED;
	case PixelFormat_RGB8:
		return GL_RGB;
	case PixelFormat_RGBA8:
		return GL_RGBA;
	default:
		break;
	}

	return 0;
}

GLenum getGLTextureDataType(PixelFormat format)
{
	switch (format)
	{

	case PixelFormat_R8:
	case PixelFormat_RGB8:
	case PixelFormat_RGBA8:
		return GL_UNSIGNED_BYTE;

	// #TODO: Float-point texture formats
	//case PixelFormat_RGBA32F:
		//return GL_FLOAT;

	default:
		break;
	}

	return 0;
}

GLint getComponentsFromFormat(PixelFormat format)
{
	switch (format)
	{
	case PixelFormat_R8:
		return 1;
	case PixelFormat_RGB8:
		return 3;
	case PixelFormat_RGBA8:
		return 4;
	default:
		break;
	}

	return 0;
}

GLint getGlWrap(TextureWrap wrap)
{
	GLint param = 0;

	if (wrap == TextureWrap_Repeat)
		param = GL_REPEAT;
	else if (wrap == TextureWrap_MirroredRepeat)
		param = GL_MIRRORED_REPEAT;
	else if (wrap == TextureWrap_ClampToEdge)
		param = GL_CLAMP_TO_EDGE;
	else if (wrap == TextureWrap_ClampToBorder)
		param = GL_CLAMP_TO_BORDER;

	return param;
}

GLint getGlTexFilter(TextureFilter filter)
{
	GLint param = 0;

	if (filter == TextureFilter_Linear)
		param = GL_LINEAR;
	else if (filter == TextureFilter_Nearest)
		param = GL_NEAREST;
	else if (filter == TextureFilter_LinearMipmapLinear)
		param = GL_LINEAR_MIPMAP_LINEAR;
	else if (filter == TextureFilter_LinearMipmapNearest)
		param = GL_LINEAR_MIPMAP_NEAREST;
	else if (filter == TextureFilter_NearestMipmapLinear)
		param = GL_NEAREST_MIPMAP_LINEAR;
	else if (filter == TextureFilter_NearestMipmapNearest)
		param = GL_NEAREST_MIPMAP_NEAREST;

	return param;
}

GLTexture2D::GLTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc)
{
	glGenTextures(1, &m_textureHandle);
	glBindTexture(GL_TEXTURE_2D, m_textureHandle);

	// Because due DX11 support targeting, we need to set up mipmap level to 1, but OpenGL
	// expect for zero value, because we don't have any mipmap
	int mipmapLevel = (textureDesc.m_mipmapLevel == 1) ? 0 : textureDesc.m_mipmapLevel;
	
	glTexImage2D(GL_TEXTURE_2D, mipmapLevel, getGLInternalFormat(textureDesc.m_format),
		textureDesc.m_width, textureDesc.m_height, 0, getGLFormat(textureDesc.m_format),
		getGLTextureDataType(textureDesc.m_format), subresourceDesc.m_memory);
	
	setInitialFilter();

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture2D::~GLTexture2D()
{
	if (m_textureHandle != 0)
		glDeleteTextures(1, &m_textureHandle);
}

void GLTexture2D::setInitialFilter()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

}