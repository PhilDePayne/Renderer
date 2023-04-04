#pragma once

#include "Vec3.h"
#include "Triangle.h"

class Light {

private:

public:

	vec3f position;
	vec3f ambient;
	vec3f diffuse;
	vec3f specular;
	float shininess;

	vec3f calculate(vec3f vertex, vec3f normal);

};