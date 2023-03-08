#pragma once

#include "Vec3.h"

class Triangle {

private:

	Vec3<unsigned int> colors;

public:

	Triangle(Vec3<Vec3<float>> vertices) : a(vertices.x), b(vertices.y), c(vertices.z) {};

	Triangle(Vec3<float> a, Vec3<float> b, Vec3<float> c) : a(a), b(b), c(c) {};

	~Triangle() {};

	Vec3<float> a;
	Vec3<float> b;
	Vec3<float> c;

	Vec3<unsigned int> getColors();
	void setColors(unsigned int colorA, unsigned int colorB, unsigned int colorC);


};