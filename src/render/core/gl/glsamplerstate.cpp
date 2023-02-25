#include "render/core/gl/glsamplerstate.h"

#include "glad/glad.h"

namespace solunar
{

extern GLint getGlWrap(TextureWrap wrap);
extern GLint getGlTexFilter(TextureFilter filter);

#define  GL_TEXTURE_MAX_ANISOTROPY_EXT          0x84FE
#define  GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT      0x84FF

GLSamplerState::GLSamplerState(const SamplerDesc& samplerDesc)
{
	glGenSamplers(1, &m_handle);
	glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_S, getGlWrap(samplerDesc.m_wrapS));
	glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_T, getGlWrap(samplerDesc.m_wrapT));
	glSamplerParameteri(m_handle, GL_TEXTURE_WRAP_R, getGlWrap(samplerDesc.m_wrapRepeat));
	glSamplerParameteri(m_handle, GL_TEXTURE_MIN_FILTER, getGlTexFilter(samplerDesc.m_minFilter));
	glSamplerParameteri(m_handle, GL_TEXTURE_MAG_FILTER, getGlTexFilter(samplerDesc.m_magFilter));
	glSamplerParameterf(m_handle, GL_TEXTURE_MAX_ANISOTROPY_EXT, samplerDesc.m_anisotropyLevel);
}

GLSamplerState::~GLSamplerState()
{
	glDeleteSamplers(1, &m_handle);
}

}