#include "OrthoCamera.h"
#include "Ray.h"
#include "Vec3.h"
#include <stdio.h>

void OrthoCamera::render(Buffer buffer, Sphere sphere) {

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();

	float centerX;
	float centerY;

	for (int i = 0; i < buffer.getWidth(); i++)
	{
		for (int j = 0; j < buffer.getHeight(); j++)
		{
			centerX = -1.0f + (i + 0.5f) * widthPixel;
			centerY = 1.0f - (j + 0.5f) * heightPixel;
			Ray ray = Ray(vec3f(centerX, centerY, 0), vec3f(0, 0, 1));
			IntersectionResult intersetion = sphere.hit(ray, 0, 100); //TODO: magic numbers

			if (intersetion.type == IntersectionType::HIT) {
				buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
			}
		}
	}

}

void OrthoCamera::render(Buffer buffer, Triangle triangle) { //TODO: render for primitive abstract

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();

	float centerX;
	float centerY;

	for (int i = 0; i < buffer.getWidth(); i++)
	{
		for (int j = 0; j < buffer.getHeight(); j++)
		{
			centerX = -1.0f + (i + 0.5f) * widthPixel;
			centerY = 1.0f - (j + 0.5f) * heightPixel;
			Ray ray = Ray(vec3f(centerX, centerY, 0), vec3f(0, 0, 1));
			IntersectionResult intersetion = triangle.hit(ray);

			if (intersetion.type == IntersectionType::HIT) {
				buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
			}
		}
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
				IntersectionResult intersetion = mesh.triangles[x].hit(ray);

				if (intersetion.type == IntersectionType::HIT) {
					buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
				}
			}
		}
	}

}