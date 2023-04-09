#pragma once

#include "Triangle.h"
#include "Buffer.h"
#include "VertexProcessor.h"
#include "Light.h"

#include <utility>
#include <vector>

class Rasterizer {

private:

	Buffer buffer;
	VertexProcessor& vp;

public:

	std::vector<unsigned int> tmpTxt;

	Rasterizer(Buffer buf, VertexProcessor& vp) : buffer(buf), vp(vp) {
		tmpTxt.resize(256 * 256);
	}

	~Rasterizer() {};

	std::pair<unsigned int, float> interpolateColor(Triangle triangle, Triangle rawTriangle, Light l, float x, float y, bool pixelShading);

	void drawTriangle(Triangle triangle, unsigned int color, Light l, bool pixelShading);
};