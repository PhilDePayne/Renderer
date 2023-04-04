#pragma once

#include "Triangle.h"
#include "Buffer.h"

#include <utility>

class Rasterizer {

private:

	Buffer buffer;

public:

	Rasterizer(Buffer buf) : buffer(buf) {}

	~Rasterizer() {};

	std::pair<unsigned int, float> interpolateColor(Triangle triangle, float x, float y);

	void drawTriangle(Triangle triangle, unsigned int color);
};