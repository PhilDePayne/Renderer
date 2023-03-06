#include "Sphere.h"
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

bool Sphere::hit(Ray ray, float t_min, float t_max) const {

	Vec3<float> oc = ray.getOrigin() - origin;

	float a = ray.getDirection().dot(ray.getDirection());
	float b = oc.dot(ray.getDirection());
	float c = oc.dot(oc) - radius * radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0) {

		float temp = (-b - std::sqrtf(discriminant)) / a;

		if (temp <= t_max && temp > t_min) {

			std::cout << ray.getOrigin().x + (temp * ray.getDirection().x) << " "
				<< ray.getOrigin().y + (temp * ray.getDirection().y) << " "
				<< ray.getOrigin().z + (temp * ray.getDirection().z) << " " << '\n'; //TODO: return from function

			return true;

		}

		temp = (-b + std::sqrtf(discriminant)) / a;

		if (temp <= t_max && temp > t_min) {

			std::cout << ray.getOrigin().x + (temp * ray.getDirection().x) << " "
				<< ray.getOrigin().y + (temp * ray.getDirection().y) << " "
				<< ray.getOrigin().z + (temp * ray.getDirection().z) << " " << '\n'; //TODO: return from function

			return true;

		}

		return false;

	}
	else {

		return false;

	}

}