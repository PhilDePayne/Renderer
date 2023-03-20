#pragma once

#include "Buffer.h"
#include "Sphere.h"

class OrthoCamera {

public:

	OrthoCamera() {};
	~OrthoCamera() {};

	void render(Buffer buffer, Sphere sphere);
};