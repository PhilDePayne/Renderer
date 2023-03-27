#pragma once

#include "Mesh.h"

class Cylinder : public Mesh {

private:

	float height = 0.0f;
	int segmentsX = 10;
	int segmentsY = 10;
	float radius = 1.0f;
	vec3f center = vec3f(0.0f, 0.0f, 0.0f);

public:

	Cylinder();
	Cylinder(int segmentsX, int segmentsY, float height, float radius);
	~Cylinder() {};

	void generate();

};