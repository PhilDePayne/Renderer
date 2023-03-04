#pragma once

#include "Triangle.h"
#include "Buffer.h"

class Rasterizer {

private:

	Buffer buffer;

public:

	Rasterizer(Buffer buf) : buffer(buf) {};

	~Rasterizer() {};

	void drawTriangle(Triangle triangle, unsigned int color);
};