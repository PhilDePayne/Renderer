#pragma once

#include "Vec3.h"

enum class IntersectionType {

	HIT,

	MISS,

	OVERLAP

};

struct IntersectionResult {

	IntersectionType type;

	int intersections;

	Vec3<float> intersectionPoint1;

	Vec3<float> intersectionPoint2;

	unsigned int color;

};

class Ray {

private:

	Vec3<float> origin;
	Vec3<float> direction;
	float distance;

public:

	Ray(Vec3<float> origin, Vec3<float> direction, float distance) :
		origin(origin), direction(direction), distance(distance) {};

	Ray(Vec3<float> origin, Vec3<float> direction) : origin(origin), direction(direction) {};

	Ray(Vec3<float> origin, float x, float y, float z);

	~Ray() {};

	Vec3<float> getOrigin() const;
	void setOrigin(Vec3<float>& v);

	Vec3<float> getDirection() const;
	void setDirection(Vec3<float>& v);

	float getDistance() const;
	void setDistance(float d);

};