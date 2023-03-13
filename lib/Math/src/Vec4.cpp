#include "Vec4.h"

float Vec4<float>::dot(const Vec4<float>& v) {

	Vec4<float> ret = Vec4<float>();

	ret.x = this->x * v.x;
	ret.y = this->y * v.y;
	ret.z = this->z * v.z;
	ret.w = this->w * v.w;

	return ret.x + ret.y + ret.z;

}