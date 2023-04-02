#pragma once

#include "Mesh.h"
#include "Vec3.h"

class Cone : public Mesh {

private:

	float height = 0.0f;
	int segments = 10;
	float radius = 1.0f;
	vec3f center = vec3f(0.0f, 0.0f, 0.0f);
	

public:

	Cone();

	Cone(int segments, float height, float radius);

	~Cone() {};

	void generate(); //TODO: override from mesh

};