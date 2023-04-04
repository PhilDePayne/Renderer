#include "Cylinder.h"
#include "const.h"

Cylinder::Cylinder() {

	generate();

}

Cylinder::Cylinder(int segmentsX, int segmentsY, float height, float radius) 
	: segmentsX(segmentsX), segmentsY(segmentsY), height(height), radius(radius) {

	generate();

}

void Cylinder::generate() {

	vertices.push_back(center);

	//printf("\n %f", vertices[0].y);

	for (int y = 0; y < segmentsY + 1; y++) {
		for (float x = 0; x < 2 * PI; x += 2 * PI / segmentsX) {

			//printf("\n %f %f %f", radius * cos(x) + center.x, y * (height / segmentsY) - (center.y - height / 2), radius * sin(x) + center.z);
			vertices.push_back(vec3f(radius * cos(x) + center.x, y * (height/segmentsY), radius * sin(x) + center.z));

		}
		if(vertices.size() > (y+1) * segmentsX + 1) vertices.pop_back();
		vertices.push_back(vec3f(radius * cos(0) + center.x, y * (height / segmentsY), radius * sin(0) + center.z));
	}

	vertices.push_back(center + vec3f(0.0f, height, 0.0f));

	int index = 0;
	for each (vec3f vertex in vertices)
	{
		printf("\n %d %f %f %f", index, vertex.x, vertex.y, vertex.z);
		index++;
	}	
	
	for (int i = 1; i < segmentsX + 1; i++) {
		faceIndex.push_back(0);
		faceIndex.push_back(i + 1);
		faceIndex.push_back(i);

		triangles.push_back(Triangle(vertices[0], vertices[i + 1], vertices[i]));

		//printf("\n %d %d %d", 0, i + 1, i);
	}
	

	vec3f v1, v2, v3;

	
	for (int j = 0; j < segmentsY; j++) {
		for (int i = 1; i <= segmentsX; i++) {

			v1 = vertices[i + j * (segmentsX + 1)];
			v2 = vertices[i + (j * (segmentsX + 1)) + 1];
			v3 = vertices[i + ((j + 1) * (segmentsX + 1)) + 1];

			faceIndex.push_back(i + j * (segmentsX + 1));
			faceIndex.push_back(i + (j * (segmentsX + 1)) + 1);
			faceIndex.push_back(i + ((j + 1) * (segmentsX + 1)) + 1);

			triangles.push_back(Triangle(v1, v2, v3));

			//printf("\n %d %d %d", i + j * (segmentsX + 1), i + (j * (segmentsX + 1)) + 1, i + ((j+1) * (segmentsX + 1)) + 1);

			v1 = vertices[i + j * (segmentsX + 1)];
			v2 = vertices[i + ((j + 1) * (segmentsX + 1)) + 1];
			v3 = vertices[i  + ((j + 1) * (segmentsX + 1))];

			faceIndex.push_back(i + j * (segmentsX + 1));
			faceIndex.push_back(i + ((j + 1) * (segmentsX + 1)) + 1);
			faceIndex.push_back(i + ((j + 1) * (segmentsX + 1)));

			triangles.push_back(Triangle(v1, v2, v3));

			//printf("\n %d %d %d", i, i + ((j + 1) * (segmentsX + 1)) + 1, i + ((j + 1) * (segmentsX + 1)));

			
		}
	}


	for (int i = 1; i <= segmentsX; i++) {

		v1 = vertices[i + (segmentsY * (segmentsX + 1))];
		v2 = vertices[i + (segmentsY * (segmentsX + 1)) + 1];
		v3 = vertices.back();

		faceIndex.push_back(i + (segmentsY * (segmentsX + 1)));
		faceIndex.push_back(i + (segmentsY * (segmentsX + 1)) + 1);
		faceIndex.push_back(vertices.size() - 1);

		triangles.push_back(Triangle(v1, v2, v3));

	}
	
	for (int i = 0; i < vertices.size(); i++) {
		normals.push_back(vec3f(0, 0, 0));
	}

	for (int i = 0; i < triangles.size(); i++) {

		vec3f a = vertices[faceIndex[i * 3 + 2]] - vertices[faceIndex[i * 3]];
		vec3f b = vertices[faceIndex[i * 3 + 1]] - vertices[faceIndex[i * 3]];

		vec3f normal = a.cross(b);

		normal.normalize();

		normals[faceIndex[i * 3]] += -normal;
		normals[faceIndex[i * 3 + 1]] += -normal;
		normals[faceIndex[i * 3 + 2]] += -normal;

	}

	for (int i = 0; i < normals.size(); i++) {

		normals[i].normalize();

		printf("\n %f %f %f \n END NORMALS", normals[i].x, normals[i].y, normals[i].z);

	}

	triangles.clear();

	for (int i = 1; i < segmentsX + 1; i++) {

		triangles.push_back(Triangle(Vec3<vec3f>(vertices[0], vertices[i + 1], vertices[i]),
								     Vec3<vec3f>(normals[0], normals[i + 1], normals[i])));

		//printf("\n %d %d %d", 0, i + 1, i);
	}

	for (int j = 0; j < segmentsY; j++) {
		for (int i = 1; i <= segmentsX; i++) {

			v1 = vertices[i + j * (segmentsX + 1)];
			v2 = vertices[i + (j * (segmentsX + 1)) + 1];
			v3 = vertices[i + ((j + 1) * (segmentsX + 1)) + 1];

			triangles.push_back(Triangle(Vec3<vec3f>(v1, v2, v3),
				Vec3<vec3f>(normals[i + j * (segmentsX + 1)], normals[i + (j * (segmentsX + 1)) + 1], normals[i + ((j + 1) * (segmentsX + 1)) + 1])));

			//printf("\n %d %d %d", i + j * (segmentsX + 1), i + (j * (segmentsX + 1)) + 1, i + ((j+1) * (segmentsX + 1)) + 1);

			v1 = vertices[i + j * (segmentsX + 1)];
			v2 = vertices[i + ((j + 1) * (segmentsX + 1)) + 1];
			v3 = vertices[i + ((j + 1) * (segmentsX + 1))];

			faceIndex.push_back(i + j * (segmentsX + 1));
			faceIndex.push_back(i + ((j + 1) * (segmentsX + 1)) + 1);
			faceIndex.push_back(i + ((j + 1) * (segmentsX + 1)));

			triangles.push_back(Triangle(Vec3<vec3f>(v1, v2, v3),
				Vec3<vec3f>(normals[i + j * (segmentsX + 1)], normals[i + ((j + 1) * (segmentsX + 1)) + 1], normals[i + ((j + 1) * (segmentsX + 1))])));

			//printf("\n %d %d %d", i, i + ((j + 1) * (segmentsX + 1)) + 1, i + ((j + 1) * (segmentsX + 1)));


		}
	}


	for (int i = 1; i <= segmentsX; i++) {

		v1 = vertices[i + (segmentsY * (segmentsX + 1))];
		v2 = vertices[i + (segmentsY * (segmentsX + 1)) + 1];
		v3 = vertices.back();

		triangles.push_back(Triangle(Vec3<vec3f>(v1, v2, v3),
			Vec3<vec3f>(normals[i + (segmentsY * (segmentsX + 1))], normals[i + (segmentsY * (segmentsX + 1)) + 1], normals.back())));

	}

	for (int k = 0; k < triangles.size(); k++) {

		triangles[k].setColors(colors.x, colors.y, colors.z);

	}
	
}