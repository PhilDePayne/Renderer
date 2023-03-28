#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Primitive.h"

class Plane : public Primitive {

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

	IntersectionResult hit(Ray ray) override;
};