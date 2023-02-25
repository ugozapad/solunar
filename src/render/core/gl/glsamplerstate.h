#ifndef RENDER_CORE_GL_GLSAMPLERSTATE_H
#define RENDER_CORE_GL_GLSAMPLERSTATE_H

#include "render/core/itexture.h"

namespace solunar
{

class GLSamplerState : public ISamplerState
{
public:
	GLSamplerState(const SamplerDesc& samplerDesc);
	~GLSamplerState();

	uint32_t getHandle() { return m_handle; }

private:
	uint32_t m_handle;
};

}

#endif // !RENDER_CORE_GL_GLSAMPLERSTATE_H
