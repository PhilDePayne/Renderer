#include "OrthoCamera.h"
#include "Ray.h"
#include "Vec3.h"
#include "const.h"
#include "MathHelper.h"
#include <stdio.h>
#include <utility>
#include <vector>

void OrthoCamera::render(Buffer buffer, Scene scene) {

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();
	float halfWidth = widthPixel * 0.5f;
	float halfHeight = heightPixel * 0.5f;

	float centerX;
	float centerY;
	int reps = 0;

	std::vector<std::pair<unsigned int, float>> pixelColorWeights;

	float probeDepths[4]{10000};
	unsigned int probeColor[4]{CLEAR_COLOR};

	for (int i = 0; i < buffer.getWidth(); i++)
	{
		for (int j = 0; j < buffer.getHeight(); j++)
		{
			centerX = -1.0f + (i + 0.5f) * widthPixel;
			centerY = 1.0f - (j + 0.5f) * heightPixel;

			if (aa) {

				AAA(centerX, centerY, widthPixel, heightPixel, pixelColorWeights, 1, scene);

				vec3f partialResultColors = vec3f(0, 0, 0);

				for each (auto color in pixelColorWeights)
				{
					Vec3<unsigned int> rgb = rgbFromHex(color.first);
					float r = rgb.x * color.second;
					float g = rgb.y * color.second;
					float b = rgb.z * color.second;
					partialResultColors.x += r;
					partialResultColors.y += g;
					partialResultColors.z += b;
				}

				buffer.color[buffer.getWidth() * j + i] = hexFromRgb(Vec3<float>(partialResultColors.x, partialResultColors.y, partialResultColors.z));

				pixelColorWeights.clear();

				for (int i = 0; i < 4; i++) {
					probeColor[i] = CLEAR_COLOR;
					probeDepths[i] = 10000;
				}
			}
			else {
				Ray ray = Ray(vec3f(centerX, centerY, 0), vec3f(0, 0, 1));

				for (int k = 0; k < scene.elements.size(); k++) {
					IntersectionResult intersetion = scene.elements[k]->hit(ray, false);

					if (intersetion.type == IntersectionType::HIT &&
						intersetion.intersectionPoint1.z < buffer.depth[buffer.getWidth() * j + i]) {
						buffer.color[buffer.getWidth() * j + i] = intersetion.color;
						buffer.depth[buffer.getWidth() * j + i] = intersetion.intersectionPoint1.z;
					}
				}
					
			}
		}
		printf("\n %d", i);
	}
}

void OrthoCamera::AAA(float cx, float cy, float pixelWidth, float pixelHeight, 
	std::vector<std::pair<unsigned int, float>>& pixelColorsWeight, int rep, Scene& scene)
{
	float probeDepths[4]{ 10000, 10000, 10000, 10000 };
	unsigned int probeColor[4]{ CLEAR_COLOR, CLEAR_COLOR, CLEAR_COLOR, CLEAR_COLOR }; //TODO: pass by reference

	float halfPixelWidth = pixelWidth * 0.5f;
	float halfPixelHeight = pixelHeight * 0.5f;

	Ray r1 = Ray(vec3f(cx - halfPixelWidth, cy - halfPixelHeight, 0), vec3f(0, 0, 1));
	Ray r2 = Ray(vec3f(cx + halfPixelWidth, cy - halfPixelHeight, 0), vec3f(0, 0, 1));
	Ray r4 = Ray(vec3f(cx - halfPixelWidth, cy + halfPixelHeight, 0), vec3f(0, 0, 1));
	Ray r5 = Ray(vec3f(cx + halfPixelWidth, cy + halfPixelHeight, 0), vec3f(0, 0, 1));

	for (int k = 0; k < scene.elements.size(); k++) {

		IntersectionResult ir1 = scene.elements[k]->hit(r1, false);
		if (ir1.type == IntersectionType::HIT && ir1.intersectionPoint1.z < probeDepths[0]) {
			probeColor[0] = ir1.color;
			probeDepths[0] = ir1.intersectionPoint1.z;
		}
		IntersectionResult ir2 = scene.elements[k]->hit(r2, false);
		if (ir2.type == IntersectionType::HIT && ir2.intersectionPoint1.z < probeDepths[1]) {
			probeColor[1] = ir2.color;
			probeDepths[1] = ir2.intersectionPoint1.z;
		}
		IntersectionResult ir4 = scene.elements[k]->hit(r4, false);
		if (ir4.type == IntersectionType::HIT && ir4.intersectionPoint1.z < probeDepths[2]) {
			probeColor[2] = ir4.color;
			probeDepths[2] = ir4.intersectionPoint1.z;
		}
		IntersectionResult ir5 = scene.elements[k]->hit(r5, false);
		if (ir5.type == IntersectionType::HIT && ir5.intersectionPoint1.z < probeDepths[3]) {
			probeColor[3] = ir5.color;
			probeDepths[3] = ir5.intersectionPoint1.z;
		}

	}

	if (probeColor[0] == probeColor[1] == probeColor[2] == probeColor[3] || rep >= maxRepeats) {

		if (probeColor[0] == probeColor[1] == probeColor[2] == probeColor[3]) {

			pixelColorsWeight.push_back(std::pair<unsigned int, float>(probeColor[0], 1 / pow(4, rep)));
			return;
		}
		else {
			pixelColorsWeight.push_back(std::pair<unsigned int, float>(probeColor[0], 1 / pow(4, rep)));
			pixelColorsWeight.push_back(std::pair<unsigned int, float>(probeColor[1], 1 / pow(4, rep)));
			pixelColorsWeight.push_back(std::pair<unsigned int, float>(probeColor[2], 1 / pow(4, rep)));
			pixelColorsWeight.push_back(std::pair<unsigned int, float>(probeColor[3], 1 / pow(4, rep)));
			
			return;

		}
	}
	else {
		AAA(cx - (halfPixelWidth), cy - (halfPixelHeight), halfPixelWidth, halfPixelHeight, pixelColorsWeight, rep + 1, scene);
		AAA(cx + (halfPixelWidth), cy - (halfPixelHeight), halfPixelWidth, halfPixelHeight, pixelColorsWeight, rep + 1, scene);
		AAA(cx - (halfPixelWidth), cy + (halfPixelHeight), halfPixelWidth, halfPixelHeight, pixelColorsWeight, rep + 1, scene);
		AAA(cx + (halfPixelWidth), cy + (halfPixelHeight), halfPixelWidth, halfPixelHeight, pixelColorsWeight, rep + 1, scene);
		return;
	}

}

void OrthoCamera::render(Buffer buffer, Mesh mesh) { //TODO: render for primitive abstract

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();

	float centerX;
	float centerY;

	for (int x = 0; x < mesh.triangles.size(); x++) {

		for (int i = 0; i < buffer.getWidth(); i++)
		{
			for (int j = 0; j < buffer.getHeight(); j++)
			{
				centerX = -1.0f + (i + 0.5f) * widthPixel;
				centerY = 1.0f - (j + 0.5f) * heightPixel;
				Ray ray = Ray(vec3f(centerX, centerY, 0), vec3f(0, 0, 1));
				IntersectionResult intersetion = mesh.triangles[x].hit(ray, false);

				if (intersetion.type == IntersectionType::HIT) {
					buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
				}
			}
		}
	}

}