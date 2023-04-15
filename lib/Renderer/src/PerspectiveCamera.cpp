#include "PerspectiveCamera.h"
#include "MathHelper.h"
#include "Plane.h"
#include <stdio.h>

PerspectiveCamera::PerspectiveCamera() {
	position = vec3f(0, 0, 0);
	target = vec3f(0, 0, 1);
	nearPlane = 1;
	farPlane = 1000;
	up = vec3f(0, 1, 0);
	fov = 100;
}

PerspectiveCamera::PerspectiveCamera(vec3f position, vec3f target) {

	position = position;
	target = target;
	nearPlane = 1;
	farPlane = 1000;
	up = vec3f(0, 1, 0);
}

void PerspectiveCamera::render(Buffer buffer, Scene scene) {

	int shadows = 0;
	int totals = 0;

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();

	float centerX;
	float centerY;

	vec3f w = target;
	w.normalize();

	vec3f u = up.cross(w);
	u.normalize();

	vec3f v = w.cross(u);
	v = -v;

	for (int i = 0; i < buffer.getWidth(); i++)
	{
		for (int j = 0; j < buffer.getHeight(); j++)
		{
			centerX = -1.0f + (i + 0.5f) * widthPixel;
			centerY = 1.0f - (j + 0.5f) * heightPixel;
			Ray ray = Ray(position, (u * centerX + v * centerY + w));
			vec3f ambient;

			for (int k = 0; k < scene.elements.size(); k++) {

				IntersectionResult intersetion = scene.elements[k]->hit(ray, false);

				if (intersetion.type == IntersectionType::HIT &&
					intersetion.intersectionPoint1.z < buffer.depth[buffer.getWidth() * j + i]) {

					 ambient = scene.elements[k]->material.ambient * 0.1f;

					//LIGHTING
					for (int lightNr = 0; lightNr < scene.pointLights.size(); lightNr++) {

						PointLight& currentLight = *scene.pointLights[lightNr];

						Ray lightRay = Ray(intersetion.intersectionPoint1, 
							currentLight.position.x, currentLight.position.y, currentLight.position.z);

						float distance = (lightRay.getOrigin() - currentLight.position).length();

						bool isObstructed = false;

						IntersectionResult obstruction;

						for (int obstructionNr = 0; obstructionNr < scene.elements.size(); obstructionNr++) {

							if (obstructionNr != k) {

								//IntersectionResult obstruction = scene.elements[obstructionNr]->hit(lightRay, true); //TODO: ???
								obstruction = scene.elements[obstructionNr]->hit(lightRay, false);

								if (obstruction.type == IntersectionType::HIT) {	

									float obstructionDistance = (lightRay.getOrigin() - obstruction.intersectionPoint1).length();

									if (obstructionDistance < distance) {
										isObstructed = true;
										break;
									}

								}
							}
						}

						if (!isObstructed) {

							//LIGHTS
							float attenuation = 1 / (currentLight.constAtten * 
													(currentLight.linearAtten * (distance)) * 
													(currentLight.quadAtten * powf(distance, 2.0f)));

							vec3f lightColor = (currentLight.intensity * attenuation).gRgb();

							lightColor = clampRGB(lightColor);

							//PHONG							

								//DIFFUSE
							vec3f L = lightRay.getDirection();
							L.normalize();
							vec3f N; //TODO: remove dynamic_cast
							if (dynamic_cast<Sphere*>(scene.elements[k])) {
								N = lightRay.getOrigin() - dynamic_cast<Sphere*>(scene.elements[k])->getCenter();
							}
							else {
								N = dynamic_cast<Plane*>(scene.elements[k])->getNormal();
							}

							vec3f diffuse = scene.elements[k]->material.diffuse * (L.dot(N));
							diffuse = clampRGB(diffuse);

								//SPECULAR
							vec3f R = L - (N * N.dot(L) * 2.0f);
							vec3f V = ray.getDirection();

							float specularStrength;
							float ss = R.dot(V);

							if (ss > 0) {
								specularStrength = powf(ss, scene.elements[k]->material.shininess);
							}
							else {
								specularStrength = 0.0f;
							}

							vec3f specular = scene.elements[k]->material.specular * specularStrength;
							specular = clampRGB(specular);

							vec3f finalColor = lightColor * (ambient + diffuse + specular);
							finalColor = clampRGB(finalColor);

							//vec3f itemColor = rgbFromHexF(intersetion.color);

							//vec3f finalColor = lightColor + itemColor;

							//finalColor *= itemColor;

							//finalColor = clampRGB(finalColor);

							buffer.color[buffer.getWidth() * j + i] = hexFromRgb(finalColor);
							//buffer.color[buffer.getWidth() * j + i] = intersetion.color;
						}
						else {
							buffer.color[buffer.getWidth() * j + i] = hexFromRgb(ambient);
							shadows++;
						}
						
						totals++;
						buffer.depth[buffer.getWidth() * j + i] = intersetion.intersectionPoint1.z;
					}
				}
			}
		}
	}
	printf("%d %d", shadows, totals);
}

void PerspectiveCamera::render(Buffer buffer, Sphere sphere) {

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();

	float centerX;
	float centerY;

	vec3f w = target;
	w.normalize();
	//w = -w; //FIX: negative(?)
	
	vec3f u = up.cross(w);
	u.normalize();
	u = -u;

	vec3f v = w.cross(u);

	for (int i = 0; i < buffer.getWidth(); i++)
	{
		for (int j = 0; j < buffer.getHeight(); j++)
		{
			centerX = -1.0f + (i + 0.5f) * widthPixel;
			centerY = 1.0f - (j + 0.5f) * heightPixel;
			Ray ray = Ray(position, (u * centerX + v * centerY + w));
			//printf("\n %f %f %f", (u * centerX + v * centerY + w).x, (u * centerX + v * centerY + w).y, (u * centerX + v * centerY + w).z);
			IntersectionResult intersetion = sphere.hit(ray, false); //TODO: magic numbers

			if (intersetion.type == IntersectionType::HIT) {
				buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
			}
		}
	}

}

void PerspectiveCamera::render(Buffer buffer, Triangle triangle) {

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();

	float centerX;
	float centerY;

	vec3f w = target;
	w.normalize();
	//w = -w; //FIX: negative(?)

	vec3f u = up.cross(w);
	u.normalize();
	u = -u;

	vec3f v = w.cross(u);

	for (int i = 0; i < buffer.getWidth(); i++)
	{
		for (int j = 0; j < buffer.getHeight(); j++)
		{
			centerX = -1.0f + (i + 0.5f) * widthPixel;
			centerY = 1.0f - (j + 0.5f) * heightPixel;
			Ray ray = Ray(position, (u * centerX + v * centerY + w));
			IntersectionResult intersetion = triangle.hit(ray, false); //TODO: magic numbers

			if (intersetion.type == IntersectionType::HIT) {
				buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
			}
		}
	}

}

void PerspectiveCamera::render(Buffer buffer, Mesh mesh) { //TODO: render for primitive abstract

	float widthPixel = 2.0f / buffer.getWidth();
	float heightPixel = 2.0f / buffer.getHeight();

	float centerX;
	float centerY;

	vec3f w = target;
	w.normalize();
	//w = -w; //FIX: negative(?)

	vec3f u = up.cross(w);
	u.normalize();
	u = -u;

	vec3f v = w.cross(u);

	for (int x = 0; x < mesh.triangles.size(); x++) {

		for (int i = 0; i < buffer.getWidth(); i++)
		{
			for (int j = 0; j < buffer.getHeight(); j++)
			{
				centerX = -1.0f + (i + 0.5f) * widthPixel;
				centerY = 1.0f - (j + 0.5f) * heightPixel;
				Ray ray = Ray(position, (u * centerX + v * centerY + w));
				IntersectionResult intersetion = mesh.triangles[x].hit(ray, false);

				if (intersetion.type == IntersectionType::HIT) {
					buffer.color[buffer.getWidth() * j + i] = 0xff00ff00;
				}
			}
		}
	}

}
