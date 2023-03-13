#pragma once

#include "Vec4.h"

class Mat4x4 {

private:

public:

	vec4f columns[4];

	Mat4x4();
	Mat4x4(vec4f a, vec4f b, vec4f c, vec4f d);
	~Mat4x4() {};

	Mat4x4 operator*(Mat4x4& mat);

	void write();

};