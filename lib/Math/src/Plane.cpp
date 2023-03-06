#include "Plane.h"

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