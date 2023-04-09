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

	std::vector<std::pair<float, float>> uv;

	Vec3<unsigned int> colors = Vec3<unsigned int>(0xffff0000, 0xff00ff00, 0xff0000ff);

	void loadObj(const char* filename);

};