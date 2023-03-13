#pragma once

#include "Vec3.h"

template <typename T>
class Vec4 {

private:

public:

	Vec4() {};

	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

	Vec4(Vec3<T> v, T w) : x(v.x), y(v.y), z(v.z), w(1) {};

	~Vec4() {};

	T x;
	T y;
	T z;
	T w;
};