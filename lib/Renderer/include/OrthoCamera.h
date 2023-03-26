#pragma once

#include "Buffer.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Mesh.h"

class OrthoCamera {

public:

	OrthoCamera() {};
	~OrthoCamera() {};

	void render(Buffer buffer, Sphere sphere);
	void render(Buffer buffer, Triangle triangle);
	void render(Buffer buffer, Mesh mesh);

};