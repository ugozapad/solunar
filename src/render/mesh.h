#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include <cstddef>
#include <stdint.h>

#include <string>

#include <glm/glm.hpp>

namespace solunar
{

// Forward declaration
class IBuffer;
class IShaderProgram;

struct MeshVertex
{
	glm::fvec3 position;
	glm::fvec3 normal;
	glm::fvec2 texcoord;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void loadObj(const std::string& filename);

	void draw();

private:
	void createBuffers(const std::vector<MeshVertex>& vertices);

private:
	IShaderProgram* m_shaderProgram;
	
	IBuffer* m_vertexBuffer;
	IBuffer* m_indexBuffer;

	uint32_t m_vertexBufferCount;
	uint32_t m_indexBufferCount;

};

}

#endif // !RENDER_MESH_H
