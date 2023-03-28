#pragma once

#include "Ray.h"

class Primitive {

public:

	unsigned int color;

	Primitive() {};

	~Primitive() {};

	virtual IntersectionResult hit(Ray ray) = 0;

};