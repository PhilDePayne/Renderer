#pragma once

#include "Triangle.h"
#include "Buffer.h"
#include "VertexProcessor.h"
#include "Light.h"

#include <utility>

class Rasterizer {

private:

	Buffer buffer;
	VertexProcessor& vp;

public:

	Rasterizer(Buffer buf, VertexProcessor& vp) : buffer(buf), vp(vp) {}

	~Rasterizer() {};

	std::pair<unsigned int, float> interpolateColor(Triangle triangle, Triangle rawTriangle, Light l, float x, float y, bool pixelShading);

	void drawTriangle(Triangle triangle, unsigned int color, Light l, bool pixelShading);
};