#pragma once

#include "Primitive.h"
#include "Light.h"
#include "PointLight.h"

#include <vector>

class Scene {

public:

	std::vector<Primitive *> elements;

	std::vector<PointLight*> pointLights;
};