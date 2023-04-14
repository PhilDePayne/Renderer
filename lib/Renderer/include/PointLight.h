#pragma once

#include "Vec3.h"

class PointLight : public Light {

public:

	float constAtten = 1.0f;
	float linearAtten = 0.7f;
	float quadAtten = 1.8f;

};