#include "Rasterizer.h"
#include "MathHelper.h"

#include <iostream>
#include <algorithm>

std::pair<unsigned int, float> Rasterizer::interpolateColor(Triangle triangle, Triangle rawTriangle, Light l, float x, float y, bool pixelShading) {

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

	Vec3<unsigned int> fColor = Vec3<unsigned int>(0, 0, 0);

	if (pixelShading) {
		vec3f p1 = rawTriangle.a * l1;
		vec3f p2 = rawTriangle.b * l2;
		vec3f p3 = rawTriangle.c * l3;

		vec3f fp = p1 + p2 + p3;

		vec3f n1 = rawTriangle.normalsA * l1;
		vec3f n2 = rawTriangle.normalsB * l2;
		vec3f n3 = rawTriangle.normalsC * l3;

		vec3f fn = n1 + n2 + n3;

		fn.normalize();

		//ret.first = vp.calculatePointLight(fp, fn, l);
		//ret.first = vp.calculateDirLight(fp, fn, l);
		fColor = rgbFromHex(vp.calculateDirLight(fp, fn, l));
		

	}
	else {

		
		Vec3<unsigned int> aRgb = rgbFromHex(rawTriangle.getColors().x);
		Vec3<unsigned int> bRgb = rgbFromHex(rawTriangle.getColors().y);
		Vec3<unsigned int> cRgb = rgbFromHex(rawTriangle.getColors().z);

		unsigned int color1 = hexFromRgb(vec3f(aRgb.x * l1, aRgb.y * l1, aRgb.z * l1));
		unsigned int color2 = hexFromRgb(vec3f(bRgb.x * l2, bRgb.y * l2, bRgb.z * l2));
		unsigned int color3 = hexFromRgb(vec3f(cRgb.x * l3, cRgb.y * l3, cRgb.z * l3));

		ret.first = color1 + color2 + color3;
		

	}

	float u1 = rawTriangle.uvA.first * l1;
	float u2 = rawTriangle.uvB.first * l2;
	float u3 = rawTriangle.uvC.first * l3;

	float fu = u1 + u2 + u3;

	int tmpu = changeValue(fu, 0, 256, -2, 2);

	float v1 = rawTriangle.uvA.second * l1;
	float v2 = rawTriangle.uvB.second * l2;
	float v3 = rawTriangle.uvC.second * l3;

	float fv = v1 + v2 + v3;

	int tmpv = changeValue(fv, 0, 256, -2, 2);

	int txtIdx = (tmpv * 256) + tmpu;

	fColor += rgbFromHex(tmpTxt[txtIdx]);

	fColor.x = fColor.x > 255 ? 255 : fColor.x < 0 ? 0 : fColor.x;
	fColor.y = fColor.y > 255 ? 255 : fColor.y < 0 ? 0 : fColor.y;
	fColor.z = fColor.z > 255 ? 255 : fColor.z < 0 ? 0 : fColor.z;

	ret.first = hexFromRgb(vec3f((float)fColor.x, (float)fColor.y, (float)fColor.z));
	ret.second = (l1 * triangle.a.z + l2 * triangle.b.z + l3 * triangle.c.z);
	return  ret;

}

void Rasterizer::drawTriangle(Triangle rawTriangle, unsigned int color, Light l, bool pixelShading)
{
	Triangle triangle = Triangle(vp.process(rawTriangle.a), vp.process(rawTriangle.b), vp.process(rawTriangle.c));

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

					std::pair<unsigned int, float> d = interpolateColor(triangle, rawTriangle, l, x1, y1, pixelShading); //TODO: var name

					if (d.second < buffer.depth[bufferWidth * y + x]) {

						buffer.color[bufferWidth * y + x] = d.first;
						buffer.depth[bufferWidth * y + x] = d.second;
					}
					
				}
		}
	}
}