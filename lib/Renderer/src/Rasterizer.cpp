#include "Rasterizer.h"
#include "MathHelper.h"

#include <iostream>
#include <algorithm>

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

	//unsigned int color1 = 255 << 24 | (((unsigned int)(aRgb.x * l1) & 0xff) << 16) | (((unsigned int)(bRgb.x * l1) & 0xff) << 8) | ((unsigned int)(cRgb.x * l1) & 0xff);
	//unsigned int color2 = 255 << 24 | (((unsigned int)(aRgb.y * l2) & 0xff) << 16) | (((unsigned int)(bRgb.y * l2) & 0xff) << 8) | ((unsigned int)(cRgb.y * l2) & 0xff);
	//unsigned int color3 = 255 << 24 | (((unsigned int)(aRgb.z * l3) & 0xff) << 16) | (((unsigned int)(bRgb.z * l3) & 0xff) << 8) | ((unsigned int)(cRgb.z * l3) & 0xff);

	//unsigned int color1 = hexFromRgb(vec3f(aRgb.x * l1, aRgb.y * l2, aRgb.z * l3));
	//unsigned int color2 = hexFromRgb(vec3f(bRgb.x * l1, bRgb.y * l2, bRgb.z * l3));
	//unsigned int color3 = hexFromRgb(vec3f(cRgb.x * l1, cRgb.y * l2, cRgb.z * l3));

	unsigned int color1 = hexFromRgb(vec3f(aRgb.x * l1, aRgb.y * l1, aRgb.z * l1));
	unsigned int color2 = hexFromRgb(vec3f(bRgb.x * l2, bRgb.y * l2, bRgb.z * l2));
	unsigned int color3 = hexFromRgb(vec3f(cRgb.x * l3, cRgb.y * l3, cRgb.z * l3));

	ret.first = color1 + color2 + color3;
	ret.second = (l1 * triangle.a.z + l2 * triangle.b.z + l3 * triangle.c.z);
	return  ret;

}

void Rasterizer::drawTriangle(Triangle triangle, unsigned int color)
{
	printf("\nDraw\n");
	float dx12 = triangle.a.x - triangle.b.x;
	float dx23 = triangle.b.x - triangle.c.x;
	float dx31 = triangle.c.x - triangle.a.x;
	float dy12 = triangle.a.y - triangle.b.y;
	float dy23 = triangle.b.y - triangle.c.y;
	float dy31 = triangle.c.y - triangle.a.y;

	unsigned int bufferWidth = buffer.getWidth();
	unsigned int bufferHeight = buffer.getHeight();

	float minX = std::min(triangle.a.x, std::min(triangle.b.x, triangle.c.x));
	float maxX = std::max(triangle.a.x, std::max(triangle.b.x, triangle.c.x));
	float minY = std::min(triangle.a.y, std::min(triangle.b.y, triangle.c.y));
	float maxY = std::max(triangle.a.y, std::max(triangle.b.y, triangle.c.y));

	minX = std::max(minX, -1.0f);
	maxX = std::min(maxX, 1.0f);
	minY = std::max(minY, -1.0f);
	maxY = std::min(maxY, 1.0f);

	int minX1 = (minX + 1) * bufferWidth * 0.5f;
	int maxX1 = (maxX + 1) * bufferWidth * 0.5f;
	int minY1 = (minY + 1) * bufferHeight * 0.5f;
	int maxY1 = (maxY + 1) * bufferHeight * 0.5f;

	bool tl1 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
	bool tl2 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
	bool tl3 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));

	for (int y = minY1; y < maxY1; y++) {
		for (int x = minX1; x < maxX1; x++) {

			float x1 = 2 * ((float)x) / ((float)bufferWidth) - 1; //TODO: static normalize function
			float y1 = 2 * ((float)y) / ((float)buffer.getHeight()) - 1;

			bool s1 = tl1 ? (dx12 * (y1 - triangle.a.y)) - (dy12 * (x1 - triangle.a.x)) >= 0 : (dx12 * (y1 - triangle.a.y)) - (dy12 * (x1 - triangle.a.x)) > 0;
			bool s2 = tl2 ? (dx23 * (y1 - triangle.b.y)) - (dy23 * (x1 - triangle.b.x)) >= 0 : (dx23 * (y1 - triangle.b.y)) - (dy23 * (x1 - triangle.b.x)) > 0;
			bool s3 = tl3 ? (dx31 * (y1 - triangle.c.y)) - (dy31 * (x1 - triangle.c.x)) >= 0 : (dx31 * (y1 - triangle.c.y)) - (dy31 * (x1 - triangle.c.x)) > 0;

				if (s1 && s2 && s3) {

					std::pair<unsigned int, float> d = interpolateColor(triangle, x1, y1); //TODO: var name

					if (d.second < buffer.depth[bufferWidth * y + x]) {

						buffer.color[bufferWidth * y + x] = d.first;
						buffer.depth[bufferWidth * y + x] = d.second;

					}
					
				}
		}
	}
}