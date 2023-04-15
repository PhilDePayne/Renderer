#include "Ray.h"

Ray::Ray(Vec3<float> origin, float x, float y, float z) : origin(origin) {

	Vec3<float> point = Vec3<float>(x, y, z);
	point -= origin;
	point.normalize();

	direction.x = point.x;
	direction.y = point.y;
	direction.z = point.z;

	direction.normalize();

};

Vec3<float> Ray::getOrigin() const {

	return origin;

}

void Ray::setOrigin(Vec3<float>& v) {

	origin.x = v.x;
	origin.y = v.y;
	origin.z = v.z;

};

Vec3<float> Ray::getDirection() const {

	return direction;

};

void Ray::setDirection(Vec3<float>& v) {

	direction.x = v.x;
	direction.y = v.y;
	direction.z = v.z;

};

float Ray::getDistance() const {

	return distance;

};

void Ray::setDistance(float d) {

	distance = d;

};