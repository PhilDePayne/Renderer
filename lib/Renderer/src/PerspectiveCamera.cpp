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

std::pair<vec3f, float> PerspectiveCamera::reflectRay(Ray& ray, Scene& scene, IntersectionResult& intersection, int& elementIdx, int nr) {
	//CREATE REFLECTED RAY
	vec3f L1 = ray.getDirection();
	L1 = -L1;
	L1.normalize();

	vec3f N1; //TODO: remove dynamic_cast
	if (dynamic_cast<Sphere*>(scene.elements[elementIdx])) {
		N1 = intersection.intersectionPoint1 - dynamic_cast<Sphere*>(scene.elements[elementIdx])->getCenter();
		//N1 = -N1;
	}
	else {
		N1 = dynamic_cast<Plane*>(scene.elements[elementIdx])->getNormal();
	}
	N1.normalize();

	vec3f R1 = (N1 * N1.dot(L1) * 2.0f) - L1;
	R1.normalize();

	Ray reflectedRay = Ray(intersection.intersectionPoint1, R1);

	IntersectionResult secondIntersection;
	float minDistance = INFINITY;
	int reflectedObjIdx = 0;

	for (int recurrentObjNr = 0; recurrentObjNr < scene.elements.size(); recurrentObjNr++) {

		//OMIT REFLECTIVE OBJECT
		if (recurrentObjNr != elementIdx) {

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
	
	if (nr <= maxReps) {
		if (scene.elements[reflectedObjIdx]->material.matType == MaterialType::REFRACTIVE) {
			return refractRay(reflectedRay, scene, secondIntersection, reflectedObjIdx, nr++);
		}
		else if (scene.elements[reflectedObjIdx]->material.matType == MaterialType::REFLECTIVE) {
			return reflectRay(reflectedRay, scene, secondIntersection, reflectedObjIdx, nr++);
		}
		else {
			return std::pair<vec3f, int>(secondIntersection.intersectionPoint1, reflectedObjIdx);
		}
	} else {
		return std::pair<vec3f, int>(secondIntersection.intersectionPoint1, reflectedObjIdx);
	}
}

std::pair<vec3f, float> PerspectiveCamera::refractRay(Ray& ray, Scene& scene, IntersectionResult& intersection, int& elementIdx, int nr) {
	//CREATE REFRACTED RAY
	float refractionIndex = scene.elements[elementIdx]->material.IoR;

	//float n = refractionIndex / AIRIOR;
	float n = AIRIOR / refractionIndex;

	vec3f L1 = ray.getDirection();
	//L1 = -L1;
	L1.normalize();

	vec3f N1; //TODO: remove dynamic_cast
	if (dynamic_cast<Sphere*>(scene.elements[elementIdx])) {
		N1 = intersection.intersectionPoint1 - dynamic_cast<Sphere*>(scene.elements[elementIdx])->getCenter();
	}
	else {
		N1 = dynamic_cast<Plane*>(scene.elements[elementIdx])->getNormal();
	}
	N1.normalize();

	float cosI = N1.dot(L1);

	float cosT2 = 1.0f - n * n * (1.0f - (cosI * cosI));

	if (cosT2 < 0) { //If cosT2 < 0, total internal reflection occured so no refraction
		throw std::logic_error("Total internal reflection");
	}

	vec3f refractedRay1Direction = (L1 * n) + (N1 * (n * cosI - sqrtf(cosT2)));
	refractedRay1Direction.normalize();

	Ray refractedRay1 = Ray(intersection.intersectionPoint1, refractedRay1Direction);

	IntersectionResult second = scene.elements[elementIdx]->hit(refractedRay1, false);

	if (second.intersections < 1) {
		throw std::logic_error("Total internal reflection");
	}

	//SECOND REFRACTION
	/*
	n = refractionIndex / AIRIOR;

	L1 = refractedRay1.getDirection();
	L1.normalize();

	if (dynamic_cast<Sphere*>(scene.elements[closestIdx])) {
		N1 = second.intersectionPoint1 - dynamic_cast<Sphere*>(scene.elements[closestIdx])->getCenter();
		N1 = -N1;
	}
	N1.normalize();

	cosI = N1.dot(L1);

	cosT2 = 1.0f - n * n * (1.0f - (cosI * cosI));

	if (cosT2 < 0) { //If cosT2 < 0, total internal reflection occured so no refraction
		throw std::logic_error("Total internal reflection");
	}

	vec3f refractedRay2Direction = (L1 * n) + (N1 * (n * cosI - sqrtf(cosT2)));
	refractedRay2Direction.normalize();

	Ray refractedRay2 = Ray(second.intersectionPoint1, refractedRay2Direction);
	*/

	IntersectionResult secondIntersection;
	float minDistance = INFINITY;
	int refractedObjIdx = 0;

	for (int recurrentObjNr = 0; recurrentObjNr < scene.elements.size(); recurrentObjNr++) {

		//OMIT REFRACTIVE OBJECT
		if (recurrentObjNr != elementIdx) {

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

	if (nr <= maxReps) {
		if (scene.elements[refractedObjIdx]->material.matType == MaterialType::REFRACTIVE) {
			return refractRay(refractedRay1, scene, secondIntersection, refractedObjIdx, nr++);
		}
		else if (scene.elements[refractedObjIdx]->material.matType == MaterialType::REFLECTIVE) {
			return reflectRay(refractedRay1, scene, secondIntersection, refractedObjIdx, nr++);
		}
		else {
			return std::pair<vec3f, float>(secondIntersection.intersectionPoint1, refractedObjIdx);
		}
	}
	else {
		return std::pair<vec3f, float>(secondIntersection.intersectionPoint1, refractedObjIdx);
	}
	
}

vec3f PerspectiveCamera::calculatePhong(PointLight& currentLight, Ray& ray, Ray& lightRay, vec3f& ambient, Scene& scene, int objIdx) {
	//LIGHTS

	float distanceFromLight = (lightRay.getOrigin() - currentLight.position).length();
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
	N.normalize();

	vec3f diffuse = scene.elements[objIdx]->material.diffuse * (L.dot(N));
	diffuse = clampRGB(diffuse);

	//SPECULAR
	vec3f R = (N * N.dot(L) * 2.0f) - L;
	vec3f V = ray.getOrigin() - lightRay.getOrigin();
	V.normalize();

	float specularStrength;
	float ss = R.dot(V);

	if (ss > 0) {
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

			int closestIdx = 0;
			float distance = INFINITY;
			IntersectionResult intersetion;

			for (int k = 0; k < scene.elements.size(); k++) {

				IntersectionResult tmpIntersetion = scene.elements[k]->hit(ray, false);

				if (tmpIntersetion.type == IntersectionType::HIT) {

					float tmpDistance = (tmpIntersetion.intersectionPoint1 - position).length();
					if (tmpDistance < distance) {
						closestIdx = k;
						intersetion = tmpIntersetion;
						distance = tmpDistance;
					}

				}
			}

			ambient = scene.elements[closestIdx]->material.ambient * 0.1f;

			//LIGHTING
			for (int lightNr = 0; lightNr < scene.pointLights.size(); lightNr++) {

				PointLight& currentLight = *scene.pointLights[lightNr];

				Ray lightRay = Ray(intersetion.intersectionPoint1, 
					currentLight.position.x, currentLight.position.y, currentLight.position.z);

				float distance = (currentLight.position - lightRay.getOrigin()).length();

				//SHADOWS
				bool isObstructed = false;

				IntersectionResult obstruction;

				for (int obstructionNr = 0; obstructionNr < scene.elements.size(); obstructionNr++) {

					if (obstructionNr != closestIdx) {

						//IntersectionResult obstruction = scene.elements[obstructionNr]->hit(lightRay, true); //TODO: ???
						obstruction = scene.elements[obstructionNr]->hit(lightRay, false);

						if (obstruction.type == IntersectionType::HIT) {	

							float obstructionDistance = (lightRay.getOrigin() - obstruction.intersectionPoint1).length();

							if (obstructionDistance < distance) {
								isObstructed = true;
								if (scene.elements[obstructionNr]->material.matType == MaterialType::REFRACTIVE) {
									ambient = scene.elements[closestIdx]->material.ambient;
									ambient = vec3f(changeValue(ambient.x, 0, 1.0f, 0, 255.0f), 
										changeValue(ambient.y, 0, 1.0f, 0, 255.0f), 
										changeValue(ambient.z, 0, 1.0f, 0, 255.0f));
									ambient = clampRGB(ambient);
								}
								break;
							}

						}
					}
				}

				if (!isObstructed) {

					switch (scene.elements[closestIdx]->material.matType) {

					case MaterialType::MAT:
					{
						vec3f color = calculatePhong(currentLight, ray, lightRay, ambient, scene, closestIdx);
						
						buffer.color[buffer.getWidth() * j + i] = hexFromRgb(color);

						break;
					}

					case MaterialType::REFLECTIVE:
					{
						std::pair<vec3f, float> reflectedRayInfo = reflectRay(ray, scene, intersetion, closestIdx, 1);

						Ray secondRay = Ray(reflectedRayInfo.first,
							currentLight.position.x, currentLight.position.y, currentLight.position.z);

						vec3f color = calculatePhong(currentLight, ray, secondRay, ambient, scene, reflectedRayInfo.second);
						
						buffer.color[buffer.getWidth() * j + i] = hexFromRgb(color);

						break; 
					}

					case MaterialType::REFRACTIVE:
					{
						std::pair<vec3f, float> refractedRayInfo = refractRay(ray, scene, intersetion, closestIdx, 1);
						
						Ray secondRay = Ray(refractedRayInfo.first,
							currentLight.position.x, currentLight.position.y, currentLight.position.z);

						vec3f color = calculatePhong(currentLight, ray, secondRay, ambient, scene, refractedRayInfo.second);

						buffer.color[buffer.getWidth() * j + i] = hexFromRgb(color);

						break; 
					}
					}
				}
				else {
					buffer.color[buffer.getWidth() * j + i] = hexFromRgb(ambient);
					ambient = scene.elements[closestIdx]->material.ambient * 0.1f;
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
