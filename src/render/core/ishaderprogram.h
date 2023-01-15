#ifndef RENDER_ISHADERPROGRAM_H
#define RENDER_ISHADERPROGRAM_H

#include <stdint.h>

namespace solunar
{

enum ShaderType
{
	ShaderType_Vertex,
	ShaderType_Pixel,
	ShaderType_Compute
};

// Shader creation desc
struct ShaderCreationDesc
{
	ShaderType m_shaderType;
	const void* m_bytecode;
	size_t m_bytecodeLength;
};

enum InputType
{
	InputType_None,
	InputType_Float,
	InputType_Vec2,
	InputType_Vec3,
	InputType_Vec4,
	InputType_MAX,
};

struct ShaderInputLayout
{
	InputType m_semanticType;
	const char* m_semanticName;
	uint32_t m_inputSlot;
	uint32_t m_offset;
};

class IShaderProgram
{
public:
	virtual ~IShaderProgram() {}

	//////////////////////////////////////////////////////////////////////////
	// Applying shader uniforms as slot index
	virtual void setTextureSampler(int slot, const char* name) = 0;

	virtual void setInteger(int slot, int value) = 0;
	virtual void setFloat(int slot, float value) = 0;

	//void setVector3(int slot, const glm::vec3& vector);
	//void setMatrix4(int slot, const glm::mat4& matrix);
	//////////////////////////////////////////////////////////////////////////

	virtual uint32_t getUniformLocation(const char* uniform_name) = 0;
};

}

#endif // !RENDER_ISHADERPROGRAM_H
