#ifndef RENDER_GL_GLRENDERER_H
#define RENDER_GL_GLRENDERER_H

#include "render/core/irenderer.h"

namespace solunar
{

enum GLRenderFeature
{
	GLRenderFeature_None,
	GLRenderFeature_ARBDSA,
	GLRenderFeature_EXTDSA,
};

enum GLShaderFeature
{
	GLShaderFeature_None,
	GLShaderFeature_EXTSeparated,
	GLShaderFeature_ARBSeparated,
};

class GLRenderer : public IRenderer
{
public:
	GLRenderer(GLFWwindow* window);
	~GLRenderer();

	void init() override;
	void shutdown() override;

	void beginFrame() override;
	void endFrame() override;

	void draw(uint32_t verticesCount, uint32_t startVertexLocation) override;
	void drawIndexed(uint32_t indicesCount, uint32_t startIndexLocation, int32_t baseVertexLocation) override;
	void setPrimitiveMode(PrimitiveMode primitiveMode) override;

	IBuffer* createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc) override;
	void setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset) override;
	void setIndexBuffer(IBuffer* buffer) override;

	IShaderProgram* createShaderProgram(const ShaderCreationDesc& vertexShaderDesc, const ShaderCreationDesc& pixelShaderDesc, const std::vector<ShaderInputLayout>& inputLayouts) override;
	void setShaderProgram(IShaderProgram* shaderProgram) override;
	void setConstantBuffer(uint32_t slot, IBuffer* constantBuffer) override;

	ITexture2D* createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc) override;
	void setTexture2D(uint32_t slot, ITexture2D* texture) override;

	ISamplerState* createSamplerState(const SamplerDesc& samplerDesc) override;
	void setSamplerState(int slot, ISamplerState* samplerState) override;

private:
	void initRenderFeatures();

	bool findExtension(const char* name);

private:
	GLFWwindow* m_window;
	GLRenderFeature m_renderFeature;
	GLShaderFeature m_separatedShaderObjects;
	GLenum m_primitiveMode;

	GLuint m_vertexArraysObject;
};

}

#endif // !RENDER_GL_GLRENDERER_H
