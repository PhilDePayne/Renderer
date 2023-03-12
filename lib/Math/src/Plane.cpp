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

IntersectionResult Plane::intersection(Ray ray)
{
	IntersectionResult ret;
	ret.type = IntersectionType::MISS;
	ret.intersections = 0;
	ret.intersectionPoint1 = Vec3<float>(0, 0, 0);
	ret.intersectionPoint2 = Vec3<float>(0, 0, 0);

	float denom = normal.dot(ray.getDirection());

	if (std::abs(denom) > 0.0001f)
	{
		float t = (p - ray.getOrigin()).dot(normal) / denom;
		if (t >= 0) {

			ret.type = IntersectionType::HIT;
			ret.intersections += 1;
			ret.intersectionPoint1 = ray.getOrigin() + (ray.getDirection() * t);

			return ret;
		}
	}
	else {

		float check = normal.dot(ray.getOrigin() - p);

		if(check == 0) {

			ret.type = IntersectionType::OVERLAP;
			ret.intersections = 0;
			ret.intersectionPoint1 = Vec3<float>(0, 0, 0);
			ret.intersectionPoint2 = Vec3<float>(0, 0, 0);

			return ret;
		}
		else {

			return ret;

		}
	}
}