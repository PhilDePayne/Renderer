#include "PerspectiveCamera.h"

#include "const.h"

#include <stdio.h>
#include <stdexcept>

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

vec3f PerspectiveCamera::calculatePhong(PointLight& currentLight, float& distanceFromLight, Ray& ray, Ray& lightRay, vec3f& ambient, Scene& scene, int objIdx) {
	//LIGHTS
	float attenuation = 1 / (currentLight.constAtten *
		(currentLight.linearAtten * (distanceFromLight)) *
		(currentLight.quadAtten * powf(distanceFromLight, 2.0f)));

	vec3f lightColor = (currentLight.intensity * attenuation).gRgb();

	lightColor = clampRGB(lightColor);

	//PHONG							

		//DIFFUSE
	vec3f L = lightRay.getDirection();
	L.normalize();
	vec3f N; //TODO: remove dynamic_cast
	if (dynamic_cast<Sphere*>(scene.elements[objIdx])) {
		N = lightRay.getOrigin() - dynamic_cast<Sphere*>(scene.elements[objIdx])->getCenter();
	}
	else {
		N = dynamic_cast<Plane*>(scene.elements[objIdx])->getNormal();
	}

	vec3f diffuse = scene.elements[objIdx]->material.diffuse * (L.dot(N));
	diffuse = clampRGB(diffuse);

	//SPECULAR
	vec3f R = L - (N * N.dot(L) * 2.0f);
	vec3f V = ray.getOrigin() - lightRay.getOrigin();
	V.normalize();

	float specularStrength;
	float ss = R.dot(V);

	if (-ss > 0) {
		specularStrength = powf(ss, scene.elements[objIdx]->material.shininess);
	}
	else {
		specularStrength = 0.0f;
	}

	vec3f specular = scene.elements[objIdx]->material.specular * specularStrength;
	specular = clampRGB(specular);

	vec3f finalColor = lightColor * (ambient + diffuse + specular);
	finalColor = clampRGB(finalColor);

	return finalColor;
}

void PerspectiveCamera::render(Buffer buffer, Scene scene) {

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

						//SHADOWS
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

							switch (scene.elements[k]->material.matType) {

							case MaterialType::MAT:
							{
								//LIGHTS

								vec3f color = calculatePhong(currentLight, distance, ray, lightRay, ambient, scene, k);
								
								buffer.color[buffer.getWidth() * j + i] = hexFromRgb(color);

								break;
							}

							case MaterialType::REFLECTIVE:
							{
								//CREATE REFLECTED RAY
								vec3f L1 = ray.getDirection();
								L1.normalize();

								vec3f N1; //TODO: remove dynamic_cast
								if (dynamic_cast<Sphere*>(scene.elements[k])) {
									N1 = ray.getOrigin() - dynamic_cast<Sphere*>(scene.elements[k])->getCenter();
								}
								else {
									N1 = dynamic_cast<Plane*>(scene.elements[k])->getNormal();
								}

								vec3f R1 = L1 - (N1 * N1.dot(L1) * 2.0f);
								R1.normalize();

								Ray reflectedRay = Ray(intersetion.intersectionPoint1, R1);

								IntersectionResult secondIntersection;
								float minDistance = INFINITY;
								int reflectedObjIdx = 0;

								for (int recurrentObjNr = 0; recurrentObjNr < scene.elements.size(); recurrentObjNr++) {

									//OMIT REFLECTIVE OBJECT
									if (recurrentObjNr != k) {

										//CHECK FOR CLOSEST OBJECT IN RAY TRAJECTORY
										IntersectionResult tmp;
										tmp = scene.elements[recurrentObjNr]->hit(reflectedRay, false);

										if (tmp.type == IntersectionType::HIT) {
											float distance = (tmp.intersectionPoint1 - reflectedRay.getOrigin()).length();

											if (distance < minDistance) {
												reflectedObjIdx = recurrentObjNr;
												secondIntersection = tmp;
												minDistance = distance;
											}
										}
									}
								}

								//CALCULATE REFLECTED PHONG
								Ray secondRay = Ray(secondIntersection.intersectionPoint1,
									currentLight.position.x, currentLight.position.y, currentLight.position.z);

								distance = (secondRay.getOrigin() - currentLight.position).length();

								vec3f color = calculatePhong(currentLight, distance, ray, secondRay, ambient, scene, reflectedObjIdx);
								
								buffer.color[buffer.getWidth() * j + i] = hexFromRgb(color);

								break; 
							}

							case MaterialType::REFRACTIVE:
							{
								//CREATE REFRACTED RAY
								float refractionIndex = scene.elements[k]->material.IoR;

								//float n = refractionIndex / AIRIOR;
								float n = AIRIOR / refractionIndex;

								vec3f L1 = ray.getDirection();
								L1.normalize();

								vec3f N1; //TODO: remove dynamic_cast
								if (dynamic_cast<Sphere*>(scene.elements[k])) {
									N1 = ray.getOrigin() - dynamic_cast<Sphere*>(scene.elements[k])->getCenter();
								}
								else {
									N1 = dynamic_cast<Plane*>(scene.elements[k])->getNormal();
								}
								/*
								if (reverseMediums)
									n *= 1.0f;
									*/

								float cosI = N1.dot(L1);

								float cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);

								if (cosT2 < 0) { //If cosT2 < 0, total internal reflection occured so no refraction
									throw std::logic_error("Total internal reflection");
								}

								vec3f refractedRay1Direction = (L1 * n) + (N1 * (n * cosI - sqrtf(cosT2)));
								refractedRay1Direction.normalize();

								Ray refractedRay1 = Ray(intersetion.intersectionPoint1, refractedRay1Direction);

								IntersectionResult secondIntersection;
								float minDistance = INFINITY;
								int refractedObjIdx = 0;

								for (int recurrentObjNr = 0; recurrentObjNr < scene.elements.size(); recurrentObjNr++) {

									//OMIT REFRACTIVE OBJECT
									if (recurrentObjNr != k) {

										//CHECK FOR CLOSEST OBJECT IN RAY TRAJECTORY
										IntersectionResult tmp;
										tmp = scene.elements[recurrentObjNr]->hit(refractedRay1, false);

										if (tmp.type == IntersectionType::HIT) {
											float distance = (tmp.intersectionPoint1 - refractedRay1.getOrigin()).length();

											if (distance < minDistance) {
												refractedObjIdx = recurrentObjNr;
												secondIntersection = tmp;
												minDistance = distance;
											}
										}
									}
								}

								//CALCULATE REFRACTED PHONG
								Ray secondRay = Ray(secondIntersection.intersectionPoint1,
									currentLight.position.x, currentLight.position.y, currentLight.position.z);

								distance = (secondRay.getOrigin() - currentLight.position).length();

								vec3f color = calculatePhong(currentLight, distance, ray, secondRay, ambient, scene, refractedObjIdx);

								buffer.color[buffer.getWidth() * j + i] = hexFromRgb(color);

								break; 
							}
							}
						}
						else {
							buffer.color[buffer.getWidth() * j + i] = hexFromRgb(ambient);
						}
						
						buffer.depth[buffer.getWidth() * j + i] = intersetion.intersectionPoint1.z;
					}
				}
			}
		}
	}
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
