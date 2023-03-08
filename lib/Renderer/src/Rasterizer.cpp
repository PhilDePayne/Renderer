#include "Rasterizer.h"
#include <iostream>
#include <algorithm>

Vec3<unsigned int> Rasterizer::rgbFromHex(unsigned int hex) {

	return Vec3<unsigned int>((hex & 0x00FF0000) >> 16, (hex & 0x0000FF00) >> 8, (hex & 0x000000FF));

}

std::pair<unsigned int, float> Rasterizer::interpolateColor(Triangle triangle, float x, float y) {

	std::pair<unsigned int, float> ret;

	float dx12 = triangle.a.x - triangle.b.x;
	float dx23 = triangle.b.x - triangle.c.x;
	float dx31 = triangle.c.x - triangle.a.x;
	float dy12 = triangle.a.y - triangle.b.y;
	float dy23 = triangle.b.y - triangle.c.y;
	float dy31 = triangle.c.y - triangle.a.y; //TODO: DRY

	float l1 = (((dy23) * (x - triangle.c.x)) + ((triangle.c.x - triangle.b.x) * (y - triangle.c.y))) / 
			   (((dy23) * (triangle.a.x - triangle.c.x)) + ((triangle.c.x - triangle.b.x) * (triangle.a.y - triangle.c.y)));
	
	float l2 = (((dy31) * (x - triangle.c.x)) + ((triangle.a.x - triangle.c.x) * (y - triangle.c.y))) /
			   (((dy31) * (dx23)) + ((triangle.a.x - triangle.c.x) * (dy23)));;
	
	float l3 = 1 - l1 - l2;

	Vec3<unsigned int> aRgb = rgbFromHex(triangle.getColors().x);
	Vec3<unsigned int> bRgb = rgbFromHex(triangle.getColors().y);
	Vec3<unsigned int> cRgb = rgbFromHex(triangle.getColors().z);

	unsigned int color1 = 255 << 24 | (((unsigned int)(l1 * aRgb.x) & 0xff) << 16) | (((unsigned int)(l1 * bRgb.x) & 0xff) << 8) | ((unsigned int)(l1 * cRgb.x) & 0xff);
	unsigned int color2 = 255 << 24 | (((unsigned int)(l2 * aRgb.y) & 0xff) << 16) | (((unsigned int)(l2 * bRgb.y) & 0xff) << 8) | ((unsigned int)(l2 * cRgb.y) & 0xff);
	unsigned int color3 = 255 << 24 | (((unsigned int)(l3 * aRgb.z) & 0xff) << 16) | (((unsigned int)(l3 * bRgb.z) & 0xff) << 8) | ((unsigned int)(l3 * cRgb.z) & 0xff);

	ret.first = color1 + color2 + color3;
	ret.second = (l1 * triangle.a.z + l2 * triangle.b.z + l3 * triangle.c.z);
	return  ret;

}

void Rasterizer::drawTriangle(Triangle triangle, unsigned int color)
{
	float dx12 = triangle.a.x - triangle.b.x;
	float dx23 = triangle.b.x - triangle.c.x;
	float dx31 = triangle.c.x - triangle.a.x;
	float dy12 = triangle.a.y - triangle.b.y;
	float dy23 = triangle.b.y - triangle.c.y;
	float dy31 = triangle.c.y - triangle.a.y;

	unsigned int bufferWidth = buffer.getWidth();
	unsigned int bufferHeight = buffer.getHeight();

	int minX = std::min(triangle.a.x, std::min(triangle.b.x, triangle.c.x));
	int maxX = std::max(triangle.a.x, std::max(triangle.b.x, triangle.c.x));
	int minY = std::min(triangle.a.y, std::min(triangle.b.y, triangle.c.y));
	int maxY = std::max(triangle.a.y, std::max(triangle.b.y, triangle.c.y));

	minX = std::min(minX, -1);
	maxX = std::min(maxX, 1);
	minY = std::min(minY, -1);
	maxY = std::min(maxY, 1);

	minX = (minX + 1) * bufferWidth * 0.5f;
	maxX = (maxX + 1) * bufferWidth * 0.5f;
	minY = (minY + 1) * bufferHeight * 0.5f;
	maxY = (maxY + 1) * bufferHeight * 0.5f;

	bool tl1 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
	bool tl2 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
	bool tl3 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));

	for (int y = minY; y < maxY; y++) {
		for (int x = minX; x < maxX; x++) {

			float x1 = 2 * ((float)x) / ((float)bufferWidth) - 1; //TODO: static normalize function
			float y1 = 2 * ((float)y) / ((float)buffer.getHeight()) - 1;

			bool s1 = tl1 ? (dx12 * (y1 - triangle.a.y)) - (dy12 * (x1 - triangle.a.x)) >= 0 : (dx12 * (y1 - triangle.a.y)) - (dy12 * (x1 - triangle.a.x)) > 0;
			bool s2 = tl2 ? (dx23 * (y1 - triangle.b.y)) - (dy23 * (x1 - triangle.b.x)) >= 0 : (dx23 * (y1 - triangle.b.y)) - (dy23 * (x1 - triangle.b.x)) > 0;
			bool s3 = tl3 ? (dx31 * (y1 - triangle.c.y)) - (dy31 * (x1 - triangle.c.x)) >= 0 : (dx31 * (y1 - triangle.c.y)) - (dy31 * (x1 - triangle.c.x)) > 0;

				if (s1 && s2 && s3) {

					std::pair<unsigned int, float> d = interpolateColor(triangle, x1, y1); //TODO: var name
					std::cout << d.second;

					if (d.second >= buffer.depth[bufferWidth * y + x]) {

						buffer.color[bufferWidth * y + x] = d.first;
						buffer.depth[bufferWidth * y + x] = d.second;

					}
					
				}
		}
	}
}