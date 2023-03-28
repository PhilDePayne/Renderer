#pragma once

#include "Buffer.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Scene.h"

class OrthoCamera {

private:

	int maxRepeats = 5;

public:

	OrthoCamera() {};
	~OrthoCamera() {};

	bool aa = false;

	void AAA(float cx, float cy, float pixelWidth, float pixelHeight, 
		std::vector<std::pair<unsigned int, float>>& pixelColorsWeight, int rep, Scene& scene);

	void render(Buffer buffer, Scene scene);
	void render(Buffer buffer, Sphere sphere);
	void render(Buffer buffer, Triangle triangle);
	void render(Buffer buffer, Mesh mesh);

};