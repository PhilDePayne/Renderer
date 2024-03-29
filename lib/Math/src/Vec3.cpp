#include "Vec3.h"
#include <stdexcept>

void Vec3<float>::operator+=(const Vec3<float>& v) {

	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

}

void Vec3<unsigned int>::operator+=(const Vec3<unsigned int>& v) {

	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

}

void Vec3<float>::operator-=(const Vec3<float>& v) {

	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;

}

void Vec3<float>::operator*=(const Vec3<float>& v) {

	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;

}

Vec3<float> Vec3<float>::operator-(const Vec3<float>& v) {

	return Vec3<float>(x - v.x, y - v.y, z - v.z);

}

Vec3<float> Vec3<float>::operator-() {

	return Vec3<float>(-x, -y, -z);

}

Vec3<float> Vec3<float>::operator+(const Vec3<float>& v) {

	return Vec3<float>(x + v.x, y + v.y, z + v.z);

}

Vec3<float> Vec3<float>::operator*(const float& v) {

	return Vec3<float>(x * v, y * v, z * v);

}

Vec3<float> Vec3<float>::operator*(const Vec3<float>& v) {

	return Vec3<float>(x * v.x, y * v.y, z * v.z);

}

void Vec3<float>::multiply(const float& x) {

	this->x *= x;
	this->y *= y;
	this->z *= z;

}

void Vec3<float>::divide(const float& x) {

	if (x != 0) {

		this->x /= x;
		this->y /= x;
		this->z /= x;

	}
	else {
		throw std::invalid_argument("Divisor can't be 0");
	}

}

float Vec3<float>::length() const{

	return (float)sqrt(pow(this->x, 2) +
					   pow(this->y, 2) +
					   pow(this->z, 2));

}

void Vec3<float>::normalize() {

	float n = this->length();
	
	if (n != 0) {

		this->divide(n);

	} else {
		printf("ERROR");
		throw std::invalid_argument("Divisor can't be 0");
	}

}

float Vec3<float>::dot(const Vec3<float>& v) {

	Vec3<float> ret = Vec3<float>();

	ret.x = this->x * v.x;
	ret.y = this->y * v.y;
	ret.z = this->z * v.z;

	return ret.x + ret.y + ret.z;

}

Vec3<float> Vec3<float>::cross(const Vec3<float>& v) {

	return Vec3<float>(this->y * v.z - this->z * v.y,
		this->z * v.x - this->x * v.z,
		this->x * v.y - this->y * v.x);

}

float Vec3<float>::angleBetween(const Vec3<float>& v) {

	return acos(this->dot(v) / (this->length() * v.length()));

}

Vec3<float> Vec3<float>::reflect(Vec3<float> normal) {

	Vec3<float> tmpNormal = normal;

	tmpNormal.normalize();

	return this->operator-((tmpNormal * this->dot(tmpNormal) * 2.0f));

}

Vec3<float> Vec3<float>::max(Vec3<float> v)
{
	Vec3<float> ret;

	ret.x = this->x > v.x ? this->x : v.x;
	ret.y = this->y > v.y ? this->y : v.y;
	ret.z = this->z > v.z ? this->z : v.z;

	return ret;
}
