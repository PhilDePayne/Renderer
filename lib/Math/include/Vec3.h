#pragma once

template <typename T>
class Vec3 {

private:

public:

	Vec3() {};

	Vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	~Vec3() {};

	T x;
	T y;
	T z;
};