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
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "Mesh.h"
#include "Scene.h"

unsigned int width = 256;
unsigned int height = 256;
unsigned int color = 0xff7caf31;

void FGK() {

    Buffer buffer = Buffer(width, height, color);

    Writer writer = Writer();

    OrthoCamera orthoCamera = OrthoCamera();
    PerspectiveCamera pCam = PerspectiveCamera();

    Sphere* sphere1 = new Sphere(0.7f, 0.0f, 0.0f, 50.0f);
    Sphere* sphere2 = new Sphere(0.1f, 0.0f, 0.0f, 40.0f);

    sphere1->color = 0xff12ff98;
    sphere2->color = 0xff9812ff;

    Sphere sphere3 = Sphere(10.0f, 0.0f, 0.0f, 50.0f);
    Sphere sphere4 = Sphere(10.0f, 10.0f, 0.0f, 40.0f);

    Triangle triangle = Triangle(vec3f(0.0f, 1.0f, 1.0f), vec3f(1.0f, 0.0f, 1.0f), vec3f(-1.0f, 0.0f, 1.0f));

    Mesh mesh;

    mesh.loadObj("Alpaca_1.obj");

    Scene scene;

    scene.elements.push_back(sphere1);
    scene.elements.push_back(sphere2);

    orthoCamera.aa = false;

    //orthoCamera.render(buffer, sphere1);
    //orthoCamera.render(buffer, sphere2);
    //orthoCamera.render(buffer, triangle);
    //orthoCamera.render(buffer, mesh);
    //orthoCamera.render(buffer, scene);

    //pCam.render(buffer, triangle);
    //pCam.render(buffer, sphere3);
    //pCam.render(buffer, sphere4);
    //pCam.render(buffer, mesh);

    writer.write(TGA, width, height, buffer.color);

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

    Ray ray = Ray(vec3f(0.863281f, 0.003906f, 0), vec3f(0, 0, 1));
    Sphere sphere = Sphere(10.0f, 0.0f, 0.0f, 0.0f);
    Triangle triangle = Triangle(vec3f(0.0f, 1.0f, 1.0f), vec3f(1.0f, 0.0f, 1.0f), vec3f(-1.0f, 0.0f, 1.0f));

    if (triangle.hit(ray).type == IntersectionType::HIT) {
        printf("HIT");
    }

}

int main()
{
    FGK();

    test();

    //MiAGK();

    printf("\n %d", color);
}