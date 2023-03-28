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
		vertices.pop_back();
		vertices.push_back(vec3f(radius * cos(0) + center.x, y * (height / segmentsY), radius * sin(0) + center.z));
	}

	vertices.push_back(center + vec3f(0.0f, height, 0.0f));

	int index = 0;
	for each (vec3f vertex in vertices)
	{
		printf("\n %d %f %f %f", index, vertex.x, vertex.y, vertex.z);
		index++;
	}

	//printf("\n");

	
	
	for (int i = 1; i < segmentsX + 1; i++) {
		meshVertices.push_back(vertices[0]);
		meshVertices.push_back(vertices[i + 1]);
		meshVertices.push_back(vertices[i]);

		triangles.push_back(Triangle(vertices[0], vertices[i + 1], vertices[i]));

		//printf("\n %d %d %d", 0, i + 1, i);
	}
	

	vec3f v1, v2, v3;

	
	for (int j = 0; j < segmentsY; j++) {
		for (int i = 1; i <= segmentsX; i++) {

			v1 = vertices[i + j * (segmentsX + 1)];
			v2 = vertices[i + (j * (segmentsX + 1)) + 1];
			v3 = vertices[i + ((j + 1) * (segmentsX + 1)) + 1];

			triangles.push_back(Triangle(v1, v2, v3));

			//printf("\n %d %d %d", i + j * (segmentsX + 1), i + (j * (segmentsX + 1)) + 1, i + ((j+1) * (segmentsX + 1)) + 1);

			v1 = vertices[i + j * (segmentsX + 1)];
			v2 = vertices[i + ((j + 1) * (segmentsX + 1)) + 1];
			v3 = vertices[i  + ((j + 1) * (segmentsX + 1))];

			triangles.push_back(Triangle(v1, v2, v3));

			//printf("\n %d %d %d", i, i + ((j + 1) * (segmentsX + 1)) + 1, i + ((j + 1) * (segmentsX + 1)));

			
		}
	}


	for (int i = 1; i <= segmentsX; i++) {

		v1 = vertices[i + (segmentsY * (segmentsX + 1))];
		v2 = vertices[i + (segmentsY * (segmentsX + 1)) + 1];
		v3 = vertices.back();

		triangles.push_back(Triangle(v1, v2, v3));

		//printf("\n %f", v3.y);

		//printf("\n %d %d %d", i + (segmentsY * (segmentsX + 1)), i + (segmentsY * (segmentsX + 1)) + 1, 9);

	}
	

	
}