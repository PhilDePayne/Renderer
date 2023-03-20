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
#include "Camera.h"

unsigned int width = 256;
unsigned int height = 256;
unsigned int color = 0xff7caf31;

void FGK() {

    Buffer buffer = Buffer(width, height, color);

    Writer writer = Writer();

    Camera orthoCamera = Camera(CameraType::ORTHO);

    Sphere sphere = Sphere(10.0f, 0.0f, 0.0f, 20.0f);

    orthoCamera.renderOrtho(buffer, sphere);

    writer.write(Extension::TGA, width, height, buffer.color);

}

void MiAGK() {
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

void test() {

    Ray ray = Ray(vec3f(0, 0, 0), vec3f(0, 0, 1));
    Sphere sphere = Sphere(10.0f, 0.0f, 0.0f, 0.0f);

    if (sphere.hit(ray, 0, 11.0f).intersections > 0) {
        printf("HIT");
    }

}

int main()
{
    FGK();

    test();

    //MiAGK();

}