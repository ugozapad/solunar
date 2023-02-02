#include <assert.h>
#include <stdio.h>

#include <vector>

#include "core/filesystem/file.h"
#include "core/filesystem/vfs.h"

#include "render/core/irenderer.h"
#include "render/mesh.h"

namespace solunar
{

Mesh::Mesh() :
	m_shaderProgram(nullptr),
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_vertexBufferCount(0),
	m_indexBufferCount(0)
{
}

Mesh::~Mesh()
{
}

void Mesh::loadObj(const std::string& filename)
{
	//IFile* file = VirtualFileSystem::getInstance()->openFile(filename);
	//assert(file);

	//file->seek(0, FileSeek_End);
	//size_t length = file->tell();
	//file->seek(0, FileSeek_Begin);

	//std::string data;
	//data.resize(length + 1);

	//file->read(&data[0], length);
	//data[length] = '\0';

	//delete file;
	//file = nullptr;

	//char* bufferedData = (char*)malloc(length + 1);
	//strcpy(bufferedData, &data[0]);

	FILE* file = fopen(&filename[0], "r");
	assert(file);

	std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::fvec3> temp_vertices;
	std::vector<glm::fvec2> temp_uvs;
	std::vector<glm::fvec3> temp_normals;

	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
	while (1)
	{
		char lineHeader[128];
		int result = fscanf(file, "%s", lineHeader);
		if (result == EOF)
			break; // EOF = End Of File. Quit the loop.
	
		if (strcmp(lineHeader, "v") == 0) {
			glm::fvec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		} else if (strcmp(lineHeader, "vt") == 0) {
			glm::fvec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
	
		} else if (strcmp(lineHeader, "vn") == 0) {
			glm::fvec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		} else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				break;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	fclose(file);

	std::vector<MeshVertex> finalVertices;

	for (uint32_t i = 0; i < vertexIndices.size(); i++)
	{
		uint32_t vertexIndex = vertexIndices[i];

		glm::fvec3 vertex = temp_vertices[vertexIndex - 1];
		//glm::fvec3 normal = temp_normals[vertexIndex - 1];
		//glm::fvec2 uv = temp_uvs[vertexIndex - 1];

		glm::fvec3 normal = glm::fvec3(0.0f);
		glm::fvec2 uv = glm::fvec3(0.0f);

		finalVertices.push_back(MeshVertex{ vertex, normal, uv });
	}

	// create mesh
	createBuffers(finalVertices);
}

void Mesh::draw()
{
	uint32_t stride = sizeof(MeshVertex);
	uint32_t offset = 0;
	g_renderer->setVertexBuffer(m_vertexBuffer, stride, offset);

	g_renderer->setPrimitiveMode(PrimitiveMode_TriangleList);

	g_renderer->draw(m_vertexBufferCount, 0);
}

void Mesh::createBuffers(const std::vector<MeshVertex>& vertices)
{
	// Create vertex buffer
	BufferDesc bufferDesc = {};
	bufferDesc.m_bufferType = BufferType_VertexBuffer;
	bufferDesc.m_bufferAccess = BufferAccess_Default;
	bufferDesc.m_bufferMemorySize = vertices.size() * sizeof(MeshVertex);

	SubresourceDesc subresourceDesc = {};
	subresourceDesc.m_memory = (void*)vertices.data(); // cast const pointer to pointer is bad :(((

	m_vertexBuffer = g_renderer->createBuffer(bufferDesc, subresourceDesc);
	m_vertexBufferCount = vertices.size();
}

}