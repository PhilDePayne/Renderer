#include "Cone.h"
#include "const.h"

Cone::Cone() {

	generate();

}

Cone::Cone(int segments, float height, float radius) : segments(segments), height(height), radius(radius) {

	generate();

}

void Cone::generate() {

	vertices.push_back(center);

	for (float t = 0; t < 2 * PI; t += 2*PI/segments) {

		//printf("\n %f %f %f \n", radius * cos(t) + center.x, center.y, radius * sin(t) + center.z);

		vertices.push_back(vec3f(radius * cos(t) + center.x, center.y, radius * sin(t) + center.z));

	}

	vertices.push_back(center + vec3f(0.0f, height, 0.0f));

	for (int i = 1; i <= segments * 2; i++) {

		if (i < segments) {
			meshVertices.push_back(vertices[i]);
			meshVertices.push_back(vertices[i + 1]);
			meshVertices.push_back(vertices[0]);
			triangles.push_back(Triangle(vertices[i], vertices[i + 1], vertices[0]));

		}

		else {

			meshVertices.push_back(vertices[i - segments]);
			meshVertices.push_back(vertices[i - segments + 1]);
			meshVertices.push_back(vertices.back());
			triangles.push_back(Triangle(vertices[i - segments], vertices[i - segments + 1], vertices.back()));

		}

	}

	for (int k = 0; k < triangles.size(); k++) {

		triangles[k].setColors(colors.x, colors.y, colors.z);

	}

}