#pragma once

#include "Vec3.h"
#include "Ray.h"

class Plane {

private:

	Vec3<float> normal;
	Vec3<float> p;

public:

	Plane(Vec3<float> n, Vec3<float> p) : normal(n), p(p) {}
	~Plane() {};

	Vec3<float> getNormal() const;
	void setNormal(Vec3<float> n);

	Vec3<float> getP() const;
	void setP(Vec3<float> p);

	bool intersection(Ray ray);
};