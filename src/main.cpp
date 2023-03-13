#include <iostream>
#include "Writer.h"
#include "Buffer.h"
#include "Rasterizer.h"
#include "Vec3.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Vec4.h"
#include "Mat4x4.h"

void FGK() {

    Vec3<float>* x = new Vec3<float>(0.0f, 3.0f, 0.0f);
    Vec3<float>* y = new Vec3<float>(5.0f, 5.0f, 0.0f);

    *x += *y;

    std::cout << x->x << " " << x->y << " " << x->z << '\n';

    *x -= *y;

    *y += *x;

    std::cout << y->x << " " << y->y << " " << y->z << '\n';

    *y -= *x;

    std::cout << x->angleBetween(*y) << '\n';

    Vec3<float>* a = new Vec3<float>(4.0f, 5.0f, 1.0f);
    Vec3<float>* b = new Vec3<float>(4.0f, 1.0f, 3.0f);
    Vec3<float> c = a->cross(*b);

    std::cout << c.x << " " << c.y << " " << c.z << '\n';

    c.normalize();

    std::cout << c.x << " " << c.y << " " << c.z << '\n';

    Vec3<float> sCenter = Vec3<float>(0, 0, 0);

    Sphere S = Sphere(10, sCenter);

    Vec3<float> r1Origin = Vec3<float>(0, 0, -20);

    Ray R1 = Ray(r1Origin, sCenter.x, sCenter.y, sCenter.z);

    std::cout << R1.getDirection().x << " " << R1.getDirection().y << " " << R1.getDirection().z << '\n';

    Ray R2 = Ray(r1Origin, Vec3<float>(0, 1, 0));

    //std::cout << S.hit(R1, 0, 10) << " " << S.hit(R2, 0, 11) << '\n';

    Ray R3 = Ray(Vec3<float>(0, 0, 0), Vec3<float>(1, 0, 0));

    //std::cout << S.hit(R3, 0, 20) << '\n';

    Plane P = Plane(Vec3<float>(0, 0.5f, 0.5f), Vec3<float>(0, 0, 0));

    //std::cout << P.intersection(R2);

    delete x;
    delete y;
    delete a;
    delete b;

}

void test() {

    vec4f a = vec4f(1.0f, 1.0f, 1.0f, 1.0f);
    vec4f b = vec4f(2.0f, 2.0f, 2.0f, 2.0f);
    vec4f c = vec4f(3.0f, 3.0f, 3.0f, 3.0f);
    vec4f d = vec4f(4.0f, 4.0f, 4.0f, 4.0f);

    Mat4x4 m1 = Mat4x4(a, b, c, d);
    Mat4x4 m2 = Mat4x4(d, c, b, a);

    Mat4x4 testMat = m1 * m2;

    testMat.transpose();
    testMat.write();

}

int main()
{
    unsigned int width = 256;
    unsigned int height = 256;
    unsigned int color = 0xff7caf31;

    //FGK();

    test();

    Buffer* buffer = new Buffer(width, height, color);

    Writer* writer = new Writer();

    Rasterizer* rasterizer = new Rasterizer(*buffer);

    Vec3<float>* x = new Vec3<float>(1.0f, 1.0f, -0.1f);
    Vec3<float>* y = new Vec3<float>(1.f, -1.0f, -0.1f);
    Vec3<float>* z = new Vec3<float>(-1.0f, -1.0f, 0.1f);

    Triangle* triangle = new Triangle(*x, *y, *z);

    Vec3<float>* a = new Vec3<float>(0.0f, 1.0f, 0.0f);
    Vec3<float>* b = new Vec3<float>(1.f, -1.0f, 0.0f);
    Vec3<float>* c = new Vec3<float>(-1.0f, -1.0f, 0.0f);

    Triangle* triangle1 = new Triangle(*a, *b, *c);

    Vec3<float>* q = new Vec3<float>(-1.0f, 1.0f, 0.0f);
    Vec3<float>* w = new Vec3<float>(0.0f, 1.0f, 0.0f);
    Vec3<float>* e = new Vec3<float>(-1.0f, -1.0f, 0.0f);

    Triangle* triangle2 = new Triangle(*q, *w, *e);

    triangle->setColors(0xff0000ff, 0xff00ff00, 0xffff0000);
    triangle1->setColors(0xff000fff, 0xff00fff0, 0xffff00f0);
    triangle2->setColors(0xfffffff, 0xfffffff, 0xfffffff);

    rasterizer->drawTriangle(*triangle, 0xff012345);
    rasterizer->drawTriangle(*triangle1, 0xff012345);
    rasterizer->drawTriangle(*triangle2, 0xff012345);

    writer->write(TGA, width, height, buffer->color);

    delete buffer;

    delete writer;

    delete rasterizer;

    delete triangle;

    delete x;
    delete y;
    delete z;

    delete triangle1;

    delete a;
    delete b;
    delete c;

    delete triangle2;

    delete q;
    delete w;
    delete e;

}

