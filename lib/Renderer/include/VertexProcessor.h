#pragma once

#include "Mat4x4.h"

class VertexProcessor {

private:

	

public:

	//TODO: private
	Mat4x4 obj2World;
	Mat4x4 world2View;
	Mat4x4 view2Proj;

	VertexProcessor();

	void setPerspective(float fovy, float aspect,
		float near, float far);
	void setLookAt(vec3f eye, vec3f center, vec3f up);
	void setIdentity();
	void clear();
	void translate(vec3f v);
	void scale(vec3f v);
	void rotate(float a, vec3f v);

	vec3f process(vec3f& v);
	
};