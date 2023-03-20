#pragma once

#include "Vec3.h"
#include "Buffer.h" //TODO: forward declaration
#include "Sphere.h"

class PerspectiveCamera
{
private:

	vec3f position;
	vec3f target;
	vec3f up;
	float nearPlane;
	float farPlane;
	float fov;

public:

	PerspectiveCamera();
	PerspectiveCamera(vec3f position, vec3f target);
	~PerspectiveCamera() {};

	void render(Buffer buffer, Sphere sphere);
};