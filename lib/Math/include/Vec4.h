#pragma once

#include <stdexcept>

#include "Vec3.h"

template <typename T>
class Vec4 {

private:

public:

	Vec4() {};

	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

	Vec4(Vec3<T> v, T w) : x(v.x), y(v.y), z(v.z), w(w) {};

	Vec4(Vec3<T> v) : x(v.x), y(v.y), z(v.z), w(1) {};


	~Vec4() {};

	T x;
	T y;
	T z;
	T w;

	T& operator[](const int& x) {

		switch (x) {
		case 0:
			return this->x;
			break;
		case 1:
			return this->y;
			break;
		case 2:
			return this->z;
			break;
		case 3:
			return this->w;
			break;
		default:
			throw std::out_of_range("Index out of range, must be 0-3");
			break;
		}
	}

	float dot(const Vec4& v);
};

typedef Vec4<float> vec4f; //TODO: typedefs.h