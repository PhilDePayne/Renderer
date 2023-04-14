#pragma once

#include "Vec3.h"
#include "Triangle.h"
#include "LightIntensity.h"

class Light {

private:

public:

	LightIntensity intensity;
	vec3f position;
	vec3f ambient;
	vec3f diffuse;
	vec3f specular;
	float shininess;


};