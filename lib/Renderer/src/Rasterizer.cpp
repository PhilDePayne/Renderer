#include "Rasterizer.h"
#include <iostream>
#include <algorithm>

void Rasterizer::drawTriangle(Triangle triangle, unsigned int color)
{
	float dx12 = triangle.a.x - triangle.b.x;
	float dx23 = triangle.b.x - triangle.c.x;
	float dx31 = triangle.c.x - triangle.a.x;
	float dy12 = triangle.a.y - triangle.b.y;
	float dy23 = triangle.b.y - triangle.c.y;
	float dy31 = triangle.c.y - triangle.a.y;

	unsigned int minX = std::min(triangle.a.x, std::min(triangle.b.x, triangle.c.x));
	unsigned int maxX = std::max(triangle.a.x, std::max(triangle.b.x, triangle.c.x));
	unsigned int minY = std::min(triangle.a.y, std::min(triangle.b.y, triangle.c.y));
	unsigned int maxY = std::max(triangle.a.y, std::max(triangle.b.y, triangle.c.y));

	unsigned int bufferWidth = buffer.getWidth();

	unsigned int x, y;

	for (int i = 0; i < buffer.getSize(); i++) {

		y = i / bufferWidth;
		x = i % bufferWidth;

		float x1 = 2 * ((float)x) / ((float)bufferWidth)-1; //TODO: static normalize function
		float y1 = 2 * ((float)y) / ((float)buffer.getHeight())-1;

		if ((x <= maxX && x >= minX) &&
			(y <= maxY && y >= minY)) {

			if ((dx12 * (y1 - triangle.a.y)) - (dy12 * (x1 - triangle.a.x)) > 0
				&& (dx23 * (y1 - triangle.b.y)) - (dy23 * (x1 - triangle.b.x)) > 0
				&& (dx31 * (y1 - triangle.c.y)) - (dy31 * (x1 - triangle.c.x)) > 0) {

				buffer.color[i] = color;

			}
		}
	}
}