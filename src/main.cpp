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
#include "Light.h"
#include "MathHelper.h"

unsigned int width = 2048;
unsigned int height = 2048;
unsigned int color = 0xff7caf31;

bool drawTriangle = false;
bool drawCone = true;
bool drawCylinder = false;

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

    VertexProcessor vp = VertexProcessor();

    Writer* writer = new Writer();

    Rasterizer* rasterizer = new Rasterizer(*buffer, vp);

    writer->read(TGA, "in.tga", 256, 256, rasterizer->tmpTxt);

    Light dirLight;

    dirLight.position = vec3f(-1.0f, 0.0f, -0.5f);
    dirLight.diffuse = vec3f(0.0f, 255.0f, 0.0f);
    dirLight.ambient = vec3f(0.0f, 56.0f, 25.0f);
    dirLight.specular = vec3f(255.0f, 255.0f, 255.0f);
    dirLight.shininess = 128.0f;

    Light pointLight;

    pointLight.position = vec3f(1.0f, 0.0f, 3.0f);
    pointLight.diffuse = vec3f(0.0f, 128.0f, 0.0f);
    pointLight.ambient = vec3f(0.0f, 56.0f, 25.0f);
    pointLight.specular = vec3f(255.0f, 255.0f, 255.0f);
    pointLight.shininess = 255.0f;
    
    
    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    //vp.rotate(0.0f, vec3f(0.0f, 1.0f, 0.0f));
    //vp.rotate(30.0f, vec3f(1.0f, 1.0f, 0.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    //vp.translate(vec3f(-2.0f, 0.0f, 0.0f));

    Cone testCone = Cone(12, 2.0f, 2.0f);
    
    if (drawCone) {
        for (int i = 0; i < testCone.triangles.size(); i++) {

            //processedTriangle.setColors(0xffff0000, 0xff00ff00, 0xff0000ff);

            //rasterizer->drawTriangle(processedTriangle, 0xff00ff00, pointLight, true);
            rasterizer->drawTriangle(testCone.triangles[i], 0xff00ff00, dirLight, true);
            
        }
    }
 
    vp.clear();
    
    vp.setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    if (drawTriangle) {
        Triangle tmpT = Triangle(vec3f(0.0f, 1.0f, 0.0f), vec3f(1.0f, 0.0f, 0.0f), vec3f(-1.0f, 0.0f, 0.0f));

        tmpT.normalsA = vec3f(0, 1.0f, 0);
        tmpT.normalsB = vec3f(0, 1.0f, 0);
        tmpT.normalsC = vec3f(0, 1.0f, 0);

        tmpT.uvA = std::pair<float, float>(0.0f, 2.0f);
        tmpT.uvB = std::pair<float, float>(2.0f, 0.0f);
        tmpT.uvC = std::pair<float, float>(-2.0f, 0.0f);


        rasterizer->drawTriangle(tmpT, 0xffffffff, dirLight, true);
    }
    

    vp.rotate(10.0f, vec3f(0.0f, 1.0f, 1.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    vp.translate(vec3f(2.0f, 0.0f, 0.0f));

    Cylinder testCylinder = Cylinder(12, 3, 2.0f, 1.0f);

    
    if (drawCylinder) {
        for (int i = 0; i < testCylinder.triangles.size(); i++) {

            Triangle processedTriangle = testCylinder.triangles[i];

            //rasterizer->drawTriangle(processedTriangle, 0xff00ff00, pointLight, true);
            rasterizer->drawTriangle(processedTriangle, 0xff00ff00, dirLight, true);

        }
    }
    
    vp.clear();

    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(10.0f, vec3f(0.0f, 1.0f, 1.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    vp.translate(vec3f(2.0f, -2.2f, 0.0f));

    if (drawCylinder) {
        for (int i = 0; i < testCylinder.triangles.size(); i++) {

            Triangle processedTriangle = testCylinder.triangles[i];

            processedTriangle.setColors(vp.calculatePointLight(testCylinder.triangles[i].a, testCylinder.triangles[i].normalsA, pointLight),
                vp.calculatePointLight(testCylinder.triangles[i].b, testCylinder.triangles[i].normalsB, pointLight),
                vp.calculatePointLight(testCylinder.triangles[i].c, testCylinder.triangles[i].normalsC, pointLight));

            rasterizer->drawTriangle(processedTriangle, 0xff00ff00, pointLight, false);

        }
    }

    //writer->read(TGA, "in.tga", 256, 256, buffer->color);
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