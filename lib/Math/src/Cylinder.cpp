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
	uv.push_back(std::pair<float, float>(0, 0));

	for (int y = 0; y <= segmentsY; y++) {
		for (float x = 0; x < 2 * PI; x += 2 * PI / segmentsX) {

			vertices.push_back(vec3f(radius * cos(x) + center.x, y * (height/segmentsY), radius * sin(x) + center.z));
			uv.push_back(std::pair<float, float>(radius * cos(x), y * (height / segmentsY)));

		}
		if (vertices.size() > (y + 1) * segmentsX + 1)
		{
			printf("POPPED");
			vertices.pop_back();
			uv.pop_back();
		}
	}

	vertices.push_back(center + vec3f(0.0f, height, 0.0f));
	uv.push_back(std::pair<float, float>(0, height));

	int index = 0;
	for each (vec3f vertex in vertices)
	{
		printf("\n %d %f %f %f", index, vertex.x, vertex.y, vertex.z);
		index++;
	}	
	
	for (int i = 0; i < vertices.size(); i++) {
		normals.push_back(vec3f(0, 0, 0));
	}

	//START TRIANGLES GENERATION
	for (int i = 1; i < segmentsX; i++) {
		faceIndex.push_back(0);
		faceIndex.push_back(i + 1);
		faceIndex.push_back(i);

		triangles.push_back(Triangle(vertices[0], vertices[i + 1], vertices[i]));

		//printf("\n %d %d %d", 0, i + 1, i);
	}
	
	faceIndex.push_back(0);
	faceIndex.push_back(1);
	faceIndex.push_back(segmentsX);

	triangles.push_back(Triangle(vertices[0], vertices[1], vertices[segmentsX]));

	vec3f v1, v2, v3;
		
	for (int j = 0; j < segmentsY; j++) {
		for (int i = 1; i < segmentsX; i++) {

			v1 = vertices[i + j * (segmentsX)];
			v2 = vertices[i + (j * (segmentsX)) + 1];
			v3 = vertices[i + ((j + 1) * (segmentsX)) + 1];

			faceIndex.push_back(i + j * (segmentsX));
			faceIndex.push_back(i + (j * (segmentsX)) + 1);
			faceIndex.push_back(i + ((j + 1) * (segmentsX)) + 1);

			triangles.push_back(Triangle(v1, v2, v3));

			printf("\n %d %d %d", i + j * (segmentsX), i + (j * (segmentsX)) + 1, i + ((j + 1) * (segmentsX)) + 1);

			v1 = vertices[i + j * (segmentsX)];
			v2 = vertices[i + ((j + 1) * (segmentsX)) + 1];
			v3 = vertices[i  + ((j + 1) * (segmentsX))];

			faceIndex.push_back(i + j * (segmentsX));
			faceIndex.push_back(i + ((j + 1) * (segmentsX)) + 1);
			faceIndex.push_back(i + ((j + 1) * (segmentsX)));

			triangles.push_back(Triangle(v1, v2, v3));

			printf("\n %d %d %d", i + j * (segmentsX), i + ((j + 1) * (segmentsX)) + 1, i + ((j + 1) * (segmentsX)));
		}

		v1 = vertices[(j + 1) * (segmentsX)];
		v2 = vertices[1 + (j * (segmentsX))];
		v3 = vertices[((j + 1) * (segmentsX)) + 1];

		faceIndex.push_back((j + 1) * (segmentsX));
		faceIndex.push_back(1 + (j * (segmentsX)));
		faceIndex.push_back(((j + 1) * (segmentsX)) + 1);

		triangles.push_back(Triangle(v1, v2, v3));

		printf("\n %d %d %d", (j + 1) * (segmentsX), 1 + (j * (segmentsX)), ((j + 1) * (segmentsX)) + 1);

		
		v1 = vertices[(j + 1) * (segmentsX)];
		v2 = vertices[((j + 1) * (segmentsX)) + 1];
		v3 = vertices[((j + 2) * (segmentsX))];

		faceIndex.push_back((j + 1) * (segmentsX));
		faceIndex.push_back(((j + 1) * (segmentsX)) + 1);
		faceIndex.push_back(((j + 2) * (segmentsX)));

		triangles.push_back(Triangle(v1, v2, v3));

		printf("\n %d %d %d", (j + 1) * (segmentsX), ((j + 1) * (segmentsX)) + 1, ((j + 2) * (segmentsX)));
		

		printf("\n");

	}


	for (int i = 1; i < segmentsX; i++) {

		v1 = vertices[i + (segmentsY * (segmentsX))];
		v2 = vertices[i + (segmentsY * (segmentsX)) + 1];
		v3 = vertices.back();

		faceIndex.push_back(i + (segmentsY * (segmentsX)));
		faceIndex.push_back(i + (segmentsY * (segmentsX)) + 1);
		faceIndex.push_back(vertices.size() - 1);

		triangles.push_back(Triangle(v1, v2, v3));

		printf("\n %d %d %d", i + (segmentsY * (segmentsX)), i + (segmentsY * (segmentsX)) + 1, vertices.size() - 1);

	}

	v1 = vertices[((segmentsY + 1) * (segmentsX))];
	v2 = vertices[(segmentsY * (segmentsX)) + 1];
	v3 = vertices.back();

	faceIndex.push_back(((segmentsY + 1) * (segmentsX))); //HERE
	faceIndex.push_back((segmentsY* (segmentsX)) + 1);
	faceIndex.push_back(vertices.size() - 1);

	triangles.push_back(Triangle(v1, v2, v3));

	printf("\n %d %d %d", ((segmentsY + 1) * (segmentsX)), (segmentsY* (segmentsX)) + 1, vertices.size() - 1);
	//END TRIANGLES GENERATION

	for (int i = 0; i < triangles.size(); i++) {

		vec3f tmpA = vertices[faceIndex[i * 3 + 2]];
		vec3f tmpB = vertices[faceIndex[i * 3 + 1]];
		vec3f tmpC = vertices[faceIndex[i * 3]];

		vec3f a = tmpA - tmpC;
		vec3f b = tmpB - tmpC;

		vec3f normal = a.cross(b);

		normal.normalize();

		normals[faceIndex[i * 3]] += normal;
		normals[faceIndex[i * 3 + 1]] += normal;
		normals[faceIndex[i * 3 + 2]] += normal;

	}

	for (int i = 0; i < normals.size(); i++) {

		normals[i].normalize();

		//printf("\n %f %f %f \n END NORMALS", normals[i].x, normals[i].y, normals[i].z);

	}

	triangles.clear();
	Triangle tmp;

	for (int i = 1; i < segmentsX; i++) {

		tmp = Triangle(Vec3<vec3f>(vertices[0], vertices[i + 1], vertices[i]),
			Vec3<vec3f>(normals[0], normals[i + 1], normals[i]));

		tmp.uvA = uv[0];
		tmp.uvB = uv[i + 1];
		tmp.uvC = uv[i];

		triangles.push_back(tmp);

		//printf("\n %d %d %d", 0, i + 1, i);
	}

	tmp = Triangle(Vec3<vec3f>(vertices[0], vertices[1], vertices[segmentsX]),
		Vec3<vec3f>(normals[0], normals[1], normals[segmentsX]));

	tmp.uvA = uv[0];
	tmp.uvB = uv[1];
	tmp.uvC = uv[segmentsX];

	triangles.push_back(tmp);

	v1, v2, v3;
	int i1, i2, i3;

	for (int j = 0; j < segmentsY; j++) {
		for (int i = 1; i < segmentsX; i++) {

			i1 = i + j * (segmentsX);
			i2 = i + (j * (segmentsX)) + 1;
			i3 = i + ((j + 1) * (segmentsX)) + 1;

			v1 = vertices[i1];
			v2 = vertices[i2];
			v3 = vertices[i3];

			tmp = Triangle(Vec3<vec3f>(v1, v2, v3),
				Vec3<vec3f>(normals[i1], normals[i2], normals[i3]));

			tmp.uvA = uv[i1];
			tmp.uvB = uv[i2];
			tmp.uvC = uv[i3];

			triangles.push_back(tmp);

			i1 = i + j * (segmentsX);
			i2 = i + ((j + 1) * (segmentsX)) + 1;
			i3 = i + ((j + 1) * (segmentsX));

			v1 = vertices[i1];
			v2 = vertices[i2];
			v3 = vertices[i3];

			tmp = Triangle(Vec3<vec3f>(v1, v2, v3),
				Vec3<vec3f>(normals[i1], normals[i2], normals[i3]));

			tmp.uvA = uv[i1];
			tmp.uvB = uv[i2];
			tmp.uvC = uv[i3];

			triangles.push_back(tmp);
		}

		i1 = (j + 1) * (segmentsX);
		i2 = 1 + (j * (segmentsX));
		i3 = ((j + 1) * (segmentsX)) + 1;

		v1 = vertices[i1];
		v2 = vertices[i2];
		v3 = vertices[i3];

		tmp = Triangle(Vec3<vec3f>(v1, v2, v3),
			Vec3<vec3f>(normals[i1], normals[i2], normals[i3]));

		tmp.uvA = uv[i1];
		tmp.uvB = uv[i2];
		tmp.uvC = uv[i3];

		triangles.push_back(tmp);

		i1 = (j + 1) * (segmentsX);
		i2 = ((j + 1) * (segmentsX)) + 1;
		i3 = ((j + 2) * (segmentsX));

		v1 = vertices[i1];
		v2 = vertices[i2];
		v3 = vertices[i3];

		tmp = Triangle(Vec3<vec3f>(v1, v2, v3),
			Vec3<vec3f>(normals[i1], normals[i2], normals[i3]));

		tmp.uvA = uv[i1];
		tmp.uvB = uv[i2];
		tmp.uvC = uv[i3];

		triangles.push_back(tmp);

	}


	for (int i = 1; i < segmentsX; i++) {

		i1 = i + (segmentsY * (segmentsX));
		i2 = i + (segmentsY * (segmentsX)) + 1;

		v1 = vertices[i1];
		v2 = vertices[i2];
		v3 = vertices.back();

		tmp = Triangle(Vec3<vec3f>(v1, v2, v3),
			Vec3<vec3f>(normals[i1], normals[i2], normals.back()));

		tmp.uvA = uv[i1];
		tmp.uvB = uv[i2];
		tmp.uvC = uv.back();

		triangles.push_back(tmp);

	}

	i1 = ((segmentsY + 1) * (segmentsX));
	i2 = (segmentsY * (segmentsX)) + 1;

	v1 = vertices[i1];
	v2 = vertices[i2];
	v3 = vertices.back();

	tmp = Triangle(Vec3<vec3f>(v1, v2, v3),
		Vec3<vec3f>(normals[i1], normals[i2], normals.back()));

	tmp.uvA = uv[i1];
	tmp.uvB = uv[i2];
	tmp.uvC = uv.back();

	triangles.push_back(tmp);

	for (int k = 0; k < triangles.size(); k++) {

		triangles[k].setColors(colors.x, colors.y, colors.z);

	}
	
}