#include "Sphere.h"
#include "const.h"

#include <cmath>
#include <iostream>

Vec3<float> Sphere::getCenter() const {

	return origin;

};

void Sphere::setCenter(float x, float y, float z) {

	origin.x = x;
	origin.y = y;
	origin.z = z;

}

void Sphere::setCenter(Vec3<float> v) {

	origin.x = v.x;
	origin.y = v.y;
	origin.z = v.z;

};

float Sphere::getRadius() const {

	return radius;

};

void Sphere::setRadius(float r) {

	radius = r;

};

IntersectionResult Sphere::hit(Ray ray) {

	IntersectionResult ret;
	ret.type = IntersectionType::MISS;
	ret.intersections = 0;
	ret.intersectionPoint1 = Vec3<float>(0, 0, 0);
	ret.intersectionPoint2 = Vec3<float>(0, 0, 0);
	ret.color = CLEAR_COLOR;

	Vec3<float> oc = ray.getOrigin() - origin;

	float a = ray.getDirection().dot(ray.getDirection());
	float b = oc.dot(ray.getDirection());
	float c = oc.dot(oc) - radius * radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0) {

		float temp = (-b - std::sqrtf(discriminant)) / a;

		if (temp <= INF && temp > 0) {

			ret.type = IntersectionType::HIT;
			ret.intersections += 1;
			ret.intersectionPoint1 = Vec3<float>(ray.getOrigin().x + (temp * ray.getDirection().x),
												 ray.getOrigin().y + (temp * ray.getDirection().y), 
												 ray.getOrigin().z + (temp * ray.getDirection().z));
			ret.color = color;

		}

		temp = (-b + std::sqrtf(discriminant)) / a;

		if (temp <= INF && temp > 0) {

			ret.type = IntersectionType::HIT;
			ret.intersections += 1;

			if (ret.intersections == 1) {
				ret.intersectionPoint1 = Vec3<float>(ray.getOrigin().x + (temp * ray.getDirection().x),
					ray.getOrigin().y + (temp * ray.getDirection().y),
					ray.getOrigin().z + (temp * ray.getDirection().z));
			}
			else {
				ret.intersectionPoint2 = Vec3<float>(ray.getOrigin().x + (temp * ray.getDirection().x),
					ray.getOrigin().y + (temp * ray.getDirection().y),
					ray.getOrigin().z + (temp * ray.getDirection().z));
			}

			ret.color = color;
		}

		return ret;

	}
	else {

		return ret;

	}

}