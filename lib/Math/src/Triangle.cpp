#include "Triangle.h"

Vec3<unsigned int> Triangle::getColors() {

	return colors;

};

void Triangle::setColors(unsigned int colorA, unsigned int colorB, unsigned int colorC) {

	colors.x = colorA;
	colors.y = colorB;
	colors.z = colorC;

};

IntersectionResult Triangle::hit(Ray ray) {

	IntersectionResult ret;
	ret.type = IntersectionType::MISS;
	ret.intersections = 0;
	ret.intersectionPoint1 = Vec3<float>(0, 0, 0);
	ret.intersectionPoint2 = Vec3<float>(0, 0, 0);

    const float EPSILON = 0.0000001;

    vec3f vertex0 = a;
    vec3f vertex1 = b;
    vec3f vertex2 = c;

    vec3f edge1, edge2, h, s, q;

    float a, f, u, v;

    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;

    h = ray.getDirection().cross(edge2);
    a = edge1.dot(h);

    if (a > -EPSILON && a < EPSILON) {

        return false;    // This ray is parallel to this triangle.

    }
        
    f = 1.0 / a;
    s = ray.getOrigin() - vertex0;
    u = f * s.dot(h);

    if (u < 0.0 || u > 1.0) {

        return false;

    }
        
    q = s.cross(edge1);
    v = f * ray.getDirection().dot(q);

    if (v < 0.0 || u + v > 1.0) {

        return false;

    }
        
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.dot(q);
    if (t > EPSILON) // ray intersection
    {
        outIntersectionPoint = rayOrigin + rayVector * t;
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;

}