#include "Sphere.h"

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