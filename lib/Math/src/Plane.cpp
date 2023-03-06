#include "Plane.h"
#include <cmath>
#include <iostream>

Vec3<float> Plane::getNormal() const {

	return normal;

}

void Plane::setNormal(Vec3<float> n) {
	
	normal.x = n.x;
	normal.y = n.y;
	normal.z = n.z;

}

Vec3<float> Plane::getP() const {

	return p;

}

void Plane::setP(Vec3<float> p) {

	this->p.x = p.x;
	this->p.y = p.y;
	this->p.z = p.z;

}

bool Plane::intersection(Ray ray)
{
	float denom = normal.dot(ray.getDirection());

	if (std::abs(denom) > 0.0001f)
	{
		float t = (p - ray.getOrigin()).dot(normal) / denom;
		if (t >= 0) {
			Vec3<float> result = ray.getOrigin() + (ray.getDirection() * t);
			std::cout << result.x << " " << result.y << " " << result.z << '\n';
			return true;
		}
	}
	return false;
}