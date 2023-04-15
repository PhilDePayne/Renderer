#pragma once

#include "Ray.h"
#include "Vec3.h"
#include "Material.h"

class Primitive {

public:

	unsigned int color;
	Material material = Material(vec3f(1.0f, 1.0f, 1.0f), vec3f(1.0f, 1.0f, 1.0f), vec3f(1.0f, 1.0f, 1.0f), 1.0f);

	Primitive() {};

	~Primitive() {};

	virtual IntersectionResult hit(Ray ray, bool debug) = 0;

};