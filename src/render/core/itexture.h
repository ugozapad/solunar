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

enum TextureWrap
{
	TextureWrap_Repeat,
	TextureWrap_MirroredRepeat,
	TextureWrap_ClampToEdge,
	TextureWrap_ClampToBorder
};

enum TextureFilter
{
	TextureFilter_Nearest,
	TextureFilter_Linear,
	TextureFilter_NearestMipmapNearest,
	TextureFilter_LinearMipmapNearest,
	TextureFilter_NearestMipmapLinear,
	TextureFilter_LinearMipmapLinear
};

struct SamplerDesc
{
	TextureFilter m_minFilter;
	TextureFilter m_magFilter;
	TextureWrap m_wrapS;
	TextureWrap m_wrapT;
	TextureWrap m_wrapRepeat;
	float m_anisotropyLevel;
};

class ISamplerState
{
public:
	virtual ~ISamplerState() {}

	//virtual SamplerDesc& getSamplerDesc() = 0;
};

class ITexture2D
{
public:
	virtual ~ITexture2D() {}
};

}

#endif // !RENDER_TEXTURE_H
