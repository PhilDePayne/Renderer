#pragma once

#include "Vec3.h"

enum MaterialType {
    MAT,
    REFLECTIVE,
    REFRACTIVE
};

class Material {

public:

    MaterialType matType = MAT;

    vec3f ambient;
    vec3f diffuse;
    vec3f specular;
    float shininess;
    float IoR;

    Material();
    Material(vec3f ambient, vec3f diffuse, vec3f specular, float shininess)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {};
};