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


		vertices.push_back(vec3f(radius * cos(t) + center.x, center.y, radius * sin(t) + center.z));

	}

	if (vertices.size() > segments + 1) vertices.pop_back();

	vertices.push_back(center + vec3f(0.0f, height, 0.0f));

	for (int i = 1; i <= segments * 2; i++) {

		if (i < segments) {
			faceIndex.push_back(i);
			faceIndex.push_back(i + 1);
			faceIndex.push_back(0);

			triangles.push_back(Triangle(vertices[i], vertices[i + 1], vertices[0]));

		}

		else if (i == segments) {
			faceIndex.push_back(i);
			faceIndex.push_back(1);
			faceIndex.push_back(0);

			triangles.push_back(Triangle(vertices[i], vertices[1], vertices[0]));
		}

		else if (i == segments * 2) {
			faceIndex.push_back(1);
			faceIndex.push_back(i - segments);
			faceIndex.push_back(vertices.size() - 1);

			triangles.push_back(Triangle(vertices[i - segments], vertices[1], vertices.back()));
		}

		else {
			faceIndex.push_back(i - segments + 1);
			faceIndex.push_back(i - segments);
			faceIndex.push_back(vertices.size() - 1);

			triangles.push_back(Triangle(vertices[i - segments], vertices[i - segments + 1], vertices.back()));

		}

	}

	for (int i = 0; i < vertices.size(); i++) {
		normals.push_back(vec3f(0, 0, 0));
	}

	for (int i = 0; i < triangles.size(); i++) {

		vec3f a = vertices[faceIndex[i * 3 + 2]] - vertices[faceIndex[i * 3]];
		vec3f b = vertices[faceIndex[i * 3 + 1]] - vertices[faceIndex[i * 3]];

		vec3f normal = a.cross(b);

		normal.normalize();

		normals[faceIndex[i * 3]] += normal;
		normals[faceIndex[i * 3 + 1]] += normal;
		normals[faceIndex[i * 3 + 2]] += normal;
		
	}

	for (int i = 0; i < normals.size(); i++) {

		normals[i].normalize();
		normals[i].x = -normals[i].x;

		//printf("\n %f %f %f \n END NORMALS", normals[i].x, normals[i].y, normals[i].z);

	}

	triangles.clear();

	for (int i = 1; i <= segments * 2; i++) {

		if (i < segments) {

			triangles.push_back(Triangle(Vec3<vec3f>(vertices[i], vertices[i + 1], vertices[0]),
				Vec3<vec3f>(normals[i], normals[i + 1], normals[0])));

		}

		
		else if (i == segments) {

			triangles.push_back(Triangle(Vec3<vec3f>(vertices[i], vertices[1], vertices[0]),
				Vec3<vec3f>(normals[i], normals[1], normals[0])));
		}

		else if (i == segments * 2) {

			triangles.push_back(Triangle(Vec3<vec3f>(vertices[1], vertices[i - segments], vertices.back()),
				Vec3<vec3f>(normals[1], normals[i - segments], normals.back())));
		}
		

		else {

			triangles.push_back(Triangle(Vec3<vec3f>(vertices[i - segments + 1], vertices[i - segments], vertices.back()),
				Vec3<vec3f>(normals[i - segments + 1], normals[i - segments], normals.back())));

		}

	}

	for (int k = 0; k < triangles.size(); k++) {

		triangles[k].setColors(colors.x, colors.y, colors.z);

	}

}