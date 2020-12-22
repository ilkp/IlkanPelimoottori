#pragma once
#include <glm/glm.hpp>

class Mesh
{
public:
	int _verticesLength = 0;
	int _trianglesLength = 0;
	int _uvsLength = 0;
	glm::vec3* _vertices = nullptr;
	int* _triangles = nullptr;
	int* _uvs = nullptr;

	Mesh(const Mesh& other)
	{
		_verticesLength = other._verticesLength;
		_trianglesLength = other._trianglesLength;
		_uvsLength = other._uvsLength;
		_vertices = new glm::vec3[other._verticesLength];
		_triangles = new int[other._trianglesLength];
		_uvs = new int[other._uvsLength];
		for (int i = 0; i < other._verticesLength; ++i)
			_vertices[i] = other._vertices[i];
		for (int i = 0; i < other._trianglesLength; ++i)
			_triangles[i] = other._triangles[i];
		for (int i = 0; i < other._uvsLength; ++i)
			_uvs[i] = other._uvs[i];
	}

	Mesh() {}


};
