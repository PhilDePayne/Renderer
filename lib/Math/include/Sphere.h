#pragma once

#include "Vec3.h"
#include "Ray.h"

class Sphere {

private:

	Vec3<float> origin;
	float radius;

public:

	Sphere(float r, Vec3<float> o) : radius(r), origin(o) {};
	Sphere(float r, float x, float y, float z) : radius(r), origin(Vec3<float>(x, y, z)) {};
	~Sphere() {};

	Vec3<float> getCenter() const;
	void setCenter(float x, float y, float z);
	void setCenter(Vec3<float> v);

	float getRadius() const;
	void setRadius(float r);

	bool hit(Ray ray, float t_min, float t_max) const;

};