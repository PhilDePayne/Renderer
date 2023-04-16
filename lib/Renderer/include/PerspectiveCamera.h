#pragma once

#include "Vec3.h"
#include "Buffer.h" //TODO: forward declaration
#include "Sphere.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Scene.h"
#include "MathHelper.h"
#include "Plane.h"

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

	vec3f calculatePhong(PointLight & currentLight, Ray & ray, Ray & lightRay, vec3f & ambient, Scene & scene, int objIdx);

	std::pair<vec3f, float> reflectRay(Ray& ray, Scene& scene, IntersectionResult& intersection, int& elementIdx);
	std::pair<vec3f, float> refractRay(Ray& ray, Scene& scene, IntersectionResult& intersection, int& elementIdx);

	void render(Buffer buffer, Scene scene);
	void render(Buffer buffer, Sphere sphere);
	void render(Buffer buffer, Triangle triangle);
	void render(Buffer buffer, Mesh mesh);
};