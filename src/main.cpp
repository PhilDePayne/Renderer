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
#include "Cone.h"
#include "Cylinder.h"
#include "Torus.h"

unsigned int width = 2048;
unsigned int height = 2048;
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

    Rasterizer* rasterizer = new Rasterizer(*buffer);

    VertexProcessor vp = VertexProcessor();
    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    //vp.rotate(0.0f, vec3f(1.0f, 0.0f, 0.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    vp.translate(vec3f(0.2f, -2.0f, 0.0f));

    Cone testCone = Cone(12, 2.0f, 2.0f);

    for (int i = 0; i < testCone.triangles.size(); i++) {

        Triangle processedTriangle = Triangle(vp.process(testCone.triangles[i].a),
            vp.process(testCone.triangles[i].b),
            vp.process(testCone.triangles[i].c));

        processedTriangle.setColors(0xff0000ff, 0xff00ff00, 0xffff0000);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }

    vp.clear();

    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(45.0f, vec3f(1.0f, 0.0f, 1.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    vp.translate(vec3f(0.2f, -1.0f, 0.0f));

    Cylinder testCylinder = Cylinder(12, 6, 2.0f, 1.0f);

    
    for (int i = 0; i < testCylinder.triangles.size(); i++) {

        Triangle processedTriangle = Triangle(vp.process(testCylinder.triangles[i].a),
            vp.process(testCylinder.triangles[i].b),
            vp.process(testCylinder.triangles[i].c));

        processedTriangle.setColors(0xff0000ff, 0xff00ff00, 0xffff0000);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }

    vp.clear();

    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    //vp.rotate(45.0f, vec3f(1.0f, 0.0f, 1.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    vp.translate(vec3f(0.2f, 3.0f, 0.0f));

    Torus testTorus = Torus();


    for (int i = 0; i < testTorus.triangles.size(); i++) {

        Triangle processedTriangle = Triangle(vp.process(testTorus.triangles[i].a),
            vp.process(testTorus.triangles[i].b),
            vp.process(testTorus.triangles[i].c));

        processedTriangle.setColors(0xff0000ff, 0xff00ff00, 0xffff0000);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }
    

    vp.clear();

    

    writer->write(TGA, width, height, buffer->color);

    delete buffer;

    delete writer;

    delete rasterizer;
}

void test() {

    

}

int main()
{
    //FGK();

    test();

    MiAGK();

    printf("\n %d", color);
}