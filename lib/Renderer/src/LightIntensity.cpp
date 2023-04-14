#include "LightIntensity.h"

void LightIntensity::add(float R, float G, float B) {
	r += R;
	g += G;
	b += B;
}

LightIntensity LightIntensity::operator+(LightIntensity& li) {
	return LightIntensity(this->r + li.r, this->g + li.g, this->b + li.b);
}

LightIntensity LightIntensity::operator-(LightIntensity& li) { //TODO: check for negatives
	return LightIntensity(this->r - li.r, this->g - li.g, this->b - li.b);
}

LightIntensity LightIntensity::operator/(float num) {
	return LightIntensity(this->r / num, this->g / num, this->b / num);
}

void LightIntensity::operator+=(LightIntensity& li) { //TODO: ret type(?)
	r += li.r;
	g += li.g;
	b += li.b;
}

LightIntensity LightIntensity::operator-=(LightIntensity& li) { //TODO: ret type(?)
	r -= li.r;
	g -= li.g;
	b -= li.b;
	return *this;
}

LightIntensity LightIntensity::operator*=(float num) {
	r *= num;
	g *= num;
	b *= num;
	return *this;
}

LightIntensity LightIntensity::operator/=(float num) {
	r /= num;
	g /= num;
	b /= num;
	return *this;
}

LightIntensity operator*(float num, LightIntensity& li) {
	return LightIntensity(num * li.r, num * li.g, num * li.b);
}

LightIntensity operator*(LightIntensity& li, float num)
{
	return LightIntensity(li.r * num, li.g * num, li.b * num);
}
