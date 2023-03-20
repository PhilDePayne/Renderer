#pragma once

#include "Buffer.h"
#include "Sphere.h"

enum CameraType {

	ORTHO,

	PERSPECTIVE

};

class Camera {

protected:

	CameraType type;

public:

	Camera(CameraType type) : type(type) {};
	~Camera() {};

	void renderOrtho(Buffer buffer, Sphere sphere);
};