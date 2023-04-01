#pragma once

#include "Triangle.h"

#include <vector>

class Mesh {

private:

public:

	std::vector<Triangle> triangles;

	std::vector<vec3f> vertices;

	std::vector<int> faceIndex;

	std::vector<vec3f> meshVertices;

	std::vector<vec3f> normals;

	void loadObj(const char* filename);

};