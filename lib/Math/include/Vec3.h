#pragma once

template <typename T>
class Vec3 {

private:

public:

	Vec3() {};

	Vec3(T x, T y, T z) : x(x), y(y), z(z) {};

	~Vec3() {};

	T x = 0.0f;
	T y = 0.0f;
	T z = 0.0f;

	void operator+=(const Vec3& v);
	void operator-=(const Vec3& v);
	Vec3 operator-(const Vec3& v);
	Vec3 operator+(const Vec3& v);
	Vec3 operator*(const float& v);

	void divide(const float& x);
	void multiply(const float& x);

	float length() const;

	void normalize();

	float dot(const Vec3& v);

	Vec3<float> cross(const Vec3& v);

	//returns the angle between this vector and v in radians
	float angleBetween(const Vec3& v);

	Vec3<float> reflect(Vec3<float> normal);
};

typedef Vec3<float> vec3f;