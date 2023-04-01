#pragma once

#include "Primitive.h"
#include "Ray.h"
#include "Vec3.h"

class Triangle : public Primitive{

private:

	Vec3<unsigned int> colors;

public:

	Triangle(Vec3<Vec3<float>> vertices) : a(vertices.x), b(vertices.y), c(vertices.z) {};

	Triangle(Vec3<Vec3<float>> vertices, Vec3<Vec3<float>> normals) 
		: a(vertices.x), b(vertices.y), c(vertices.z), normalsA(normals.x), normalsB(normals.y), normalsC(normals.z) {};

	Triangle(Vec3<float> a, Vec3<float> b, Vec3<float> c) : a(a), b(b), c(c) {};

	~Triangle() {};

	Vec3<float> a;
	Vec3<float> b;
	Vec3<float> c;

	Vec3<float> normalsA;
	Vec3<float> normalsB;
	Vec3<float> normalsC;

	Vec3<unsigned int> getColors();
	void setColors(unsigned int colorA, unsigned int colorB, unsigned int colorC);

	IntersectionResult hit(Ray ray);

	void vMethod() override {};


};