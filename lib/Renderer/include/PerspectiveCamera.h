#pragma once

#include "Vec3.h"
#include "Buffer.h" //TODO: forward declaration
#include "Sphere.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Scene.h"

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

	vec3f calculatePhong(PointLight& currentLight, float& distanceFromLight, Ray& ray, Ray& lightRay, vec3f& ambient, Scene& scene, int objIdx);

	void render(Buffer buffer, Scene scene);
	void render(Buffer buffer, Sphere sphere);
	void render(Buffer buffer, Triangle triangle);
	void render(Buffer buffer, Mesh mesh);
};