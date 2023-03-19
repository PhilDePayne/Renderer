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
#include "VertexProcessor.h"

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

    vec4f q = vec4f(3.0f, 2.0f, 1.0f, 4.0f);
    vec4f w = vec4f(4.0f, 3.0f, 2.0f, 1.0f);
    vec4f e = vec4f(1.0f, 4.0f, 3.0f, 2.0f);
    vec4f r = vec4f(2.0f, 1.0f, 4.0f, 3.0f);
    Mat4x4 m2 = Mat4x4(q, w, e, r);

    Mat4x4 testMat = m1 * m2;

    //testMat.transpose();
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

    VertexProcessor vp = VertexProcessor();
    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(90.0f, vec3f(0.0f, 0.0f, 1.0f)); //FIX: wont go over 90deg
    vp.scale(vec3f(2.0f, 2.0f, 2.0f));
    vp.translate(vec3f(1.0f, 2.0f, -5.0f));    

    Rasterizer* rasterizer = new Rasterizer(*buffer);

    Vec3<float>* a = new Vec3<float>(0.0f, 1.0f, 0.0f);
    Vec3<float>* b = new Vec3<float>(1.0f, -1.0f, 0.0f);
    Vec3<float>* c = new Vec3<float>(-1.0f, -1.0f, 0.0f);

    Triangle* triangle1 = new Triangle(*a, *b, *c);

    triangle1->setColors(0xff0000ff, 0xff00ff00, 0xffff0000);

    Triangle testTriangle = Triangle(vp.process(triangle1->a),
        vp.process(triangle1->b),
        vp.process(triangle1->c));

    testTriangle.setColors(0xff0000ff, 0xff00ff00, 0xffff0000);
    rasterizer->drawTriangle(testTriangle, 0xff);

    vp.clear();

    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(50.0f, vec3f(0.0f, 1.0f, 0.0f)); //FIX: wont go over 90deg
    vp.scale(vec3f(1.0f, 1.0f, 1.0f));
    vp.translate(vec3f(-1.0f, 0.0f, 5.0f));

    testTriangle = Triangle(vp.process(triangle1->a),
        vp.process(triangle1->b),
        vp.process(triangle1->c));

    testTriangle.setColors(0xff0000ff, 0xff00ff00, 0xffff0000);

    rasterizer->drawTriangle(testTriangle, 0xff);

    writer->write(TGA, width, height, buffer->color);

    delete buffer;

    delete writer;

    delete rasterizer;

    delete triangle1;

    delete a;
    delete b;
    delete c;

}

