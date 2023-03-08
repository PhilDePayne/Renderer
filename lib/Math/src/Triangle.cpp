#include "Triangle.h"

Vec3<unsigned int> Triangle::getColors() {

	return colors;

};

void Triangle::setColors(unsigned int colorA, unsigned int colorB, unsigned int colorC) {

	colors.x = colorA;
	colors.y = colorB;
	colors.z = colorC;

};