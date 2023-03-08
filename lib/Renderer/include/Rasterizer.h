#pragma once

#include "Triangle.h"
#include "Buffer.h"

class Rasterizer {

private:

	Buffer buffer;

public:

	Rasterizer(Buffer buf) : buffer(buf) {};

	~Rasterizer() {};

	Vec3<unsigned int> rgbFromHex(unsigned int hex); //TODO: helper(?)

	unsigned int interpolateColor(Triangle triangle, float x, float y);

	void drawTriangle(Triangle triangle, unsigned int color);
};