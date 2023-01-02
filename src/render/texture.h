#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include <stdint.h>

namespace solunar
{

enum PixelFormat
{
	PixelFormat_Unknown,

	// Usigned char formats
	PixelFormat_R8,
	PixelFormat_RGB8,
	PixelFormat_RGBA8,

	PixelFormat_Max
};

enum TextureType
{
	TextureType_Unknown,
	TextureType_Texture2D
};

struct TextureDesc
{
	TextureType m_textureType;
	uint32_t m_width = 1;
	uint32_t m_height = 1;
	uint32_t m_mipmapLevel = 0;
	PixelFormat m_format;
};

class ITexture2D
{
public:
	virtual ~ITexture2D() {}
};

}

#endif // !RENDER_TEXTURE_H
