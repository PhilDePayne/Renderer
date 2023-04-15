#pragma once

#include "Vec3.h"

class LightIntensity
{
protected:
	float r, g, b;

public:
	LightIntensity(float R, float G, float B) { r = R; g = G; b = B; }
	LightIntensity(float R, float G) { r = R; g = G; b = 0.0; }
	LightIntensity(float R) { r = R; g = b = 0.0; }
	LightIntensity() { r = g = b = 0.0; }
	float gRed() { return r; }
	float gGreen() { return g; }
	float gBlue() { return b; }
	vec3f gRgb() { return vec3f(r, g, b); }
	void operator()(float R, float G, float B) { r = R; g = G; b = B; }
	void operator()(float R, float G) { r = R; g = G; b = 0.0; }
	void operator()(float R) { r = R; g = b = 0.0; }

	void add(float R, float G, float B);

	LightIntensity operator+(LightIntensity& li);
	LightIntensity operator-(LightIntensity& li);
	LightIntensity operator/(float num);
	void operator+=(LightIntensity& li);
	LightIntensity operator-=(LightIntensity& li);
	LightIntensity operator*=(float num);
	LightIntensity operator/=(float num);
	friend LightIntensity operator*(float num, LightIntensity& li);
	friend LightIntensity operator*(LightIntensity& li, float num);
};