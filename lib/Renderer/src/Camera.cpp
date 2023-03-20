#include "Camera.h"
#include "Ray.h"
#include "Vec3.h"
#include <stdio.h>

void Camera::renderOrtho(Buffer buffer, Sphere sphere) {

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
			Ray ray = Ray(vec3f(centerX, centerY, 0), 0, 0, 1);
			IntersectionResult intersetion = sphere.hit(ray, 0, 40); //TODO: magic numbers

			if (intersetion.type == IntersectionType::HIT) {
				buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
			}
			else { 
				buffer.color[buffer.getWidth() * j + i] = 0xff0000ff; 
			}
		}
	}

}