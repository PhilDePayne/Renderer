#pragma once 

#include <iostream>
#include "Vec3.h" 

inline float changeValue(float v, float nMin, float nMax, float oMin, float oMax) {

	return (((v - oMin) * (nMax - nMin)) / (oMax - oMin)) + nMin;

}

inline Vec3<unsigned int> rgbFromHex(unsigned int hex) {
	return Vec3<unsigned int>((hex & 0x00FF0000) >> 16, (hex & 0x0000FF00) >> 8, (hex & 0x000000FF));
}

inline vec3f rgbFromHexF(unsigned int hex) {

	Vec3<unsigned int> tmp = rgbFromHex(hex);

	return vec3f((float)tmp.x, (float)tmp.y, (float)tmp.z);

}

inline unsigned int hexFromRgb(Vec3<float> rgb) {
	return 255 << 24 | (((unsigned int)(rgb.x) & 0xff) << 16) | (((unsigned int)(rgb.y) & 0xff) << 8) | ((unsigned int)(rgb.z) & 0xff);
}

inline void writeHex(unsigned int hex) {
	std::cout << std::hex << hex << '\n';
}

inline vec3f clampRGB(vec3f rgb) {

	vec3f ret;

	ret.x = rgb.x > 255 ? 255 : rgb.x < 0 ? 0 : rgb.x;
	ret.y = rgb.y > 255 ? 255 : rgb.y < 0 ? 0 : rgb.y;
	ret.z = rgb.z > 255 ? 255 : rgb.z < 0 ? 0 : rgb.z;

	return ret;

}