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
#include "Scene.h"
#include "PointLight.h"
#include "Material.h"

unsigned int width = 2048;
unsigned int height = 2048;
unsigned int color = 0xff7caf31;

bool drawTriangle = false;
bool drawCone = true;
bool drawCylinder = true;

void FGK() {

    Buffer buffer = Buffer(width, height, color);

    Writer writer = Writer();

    OrthoCamera orthoCamera = OrthoCamera();
    PerspectiveCamera pCam = PerspectiveCamera();

    Sphere* sphere1 = new Sphere(0.5f, 0.2f, 0.5f, 3.0f);
    Sphere* sphere2 = new Sphere(1.0f, -1.0f, -3.0f, 5.0f);
    Sphere* sphere3 = new Sphere(0.3f, 0.0f, 0.0f, 5.0f);

    Plane* p1 = new Plane(vec3f(0.0f, 0.0f, -1.0f), vec3f(0.0f, 0.0f, 7.0f));
    Plane* p6 = new Plane(vec3f(0.0f, 0.0f, 1.0f), vec3f(0.0f, 0.0f, -7.0f));
    Plane* p2 = new Plane(vec3f(0.0f, 1.0f, 0.0f), vec3f(0.0f, -3.0f, 0.0f));
    Plane* p3 = new Plane(vec3f(0.0f, -1.0f, 0.0f), vec3f(0.0f, 3.0f, 0.0f));
    Plane* p4 = new Plane(vec3f(1.0f, 0.0f, 0.0f), vec3f(-3.0f, 0.0f, 0.0f));
    Plane* p5 = new Plane(vec3f(-1.0f, 0.0f, 0.0f), vec3f(3.0f, 0.0f, 0.0f));

    
    Material sphereMat = Material(vec3f(0.5f, 0.3f, 0.1f), vec3f(0.5f, 0.3f, 0.1f), vec3f(0.5f, 0.3f, 0.1f), 64.0f);
    sphereMat.IoR = 1.52f;
    sphereMat.matType = REFRACTIVE;
    Material sphereMat2 = Material(vec3f(0.5f, 0.3f, 0.1f), vec3f(0.5f, 0.3f, 0.1f), vec3f(0.5f, 0.3f, 0.1f), 64.0f);
    sphereMat2.matType = REFLECTIVE;
    Material sphereMat3 = Material(vec3f(0.5f, 0.3f, 0.1f), vec3f(0.5f, 0.3f, 0.1f), vec3f(0.5f, 0.3f, 0.1f), 64.0f);
    sphereMat3.matType = REFLECTIVE;
    Material pbMat = Material(vec3f(0.0f, 0.0f, 0.5f), vec3f(0.0f, 0.0f, 0.5f), vec3f(0.0f, 0.0f, 0.5f), 1.0f);
    Material pfMat = Material(vec3f(0.5f, 0.5f, 0.0f), vec3f(0.5f, 0.5f, 0.0f), vec3f(0.5f, 0.5f, 0.0f), 1.0f);
    Material phMat = Material(vec3f(0.0f, 0.5f, 0.0f), vec3f(0.0f, 0.5f, 0.0f), vec3f(0.0f, 0.5f, 0.0f), 1.0f);
    Material pvMat = Material(vec3f(0.5f, 0.0f, 0.0f), vec3f(0.5f, 0.0f, 0.0f), vec3f(0.5f, 0.0f, 0.0f), 1.0f);

    Material pTestMat = Material(vec3f(0.5f, 0.5f, 0.5f), vec3f(0.5f, 0.5f, 0.5f), vec3f(0.5f, 0.5f, 0.5f), 1.0f);

    sphere1->color = 0xff12a698;
    sphere1->material = sphereMat;

    sphere2->color = 0xff9812a6;
    sphere2->material = sphereMat2;

    sphere3->material = sphereMat3;

    p1->color = 0xff000080;
    p1->material = pbMat;
    p6->material = pfMat;

    p2->color = 0xff008000;
    p3->color = 0xff008000;
    p2->material = pTestMat;
    p3->material = phMat;

    p4->color = 0xff800000;
    p5->color = 0xff800000;
    p4->material = pvMat;
    p5->material = pvMat;

    Scene scene;

    scene.elements.push_back(sphere1);
    scene.elements.push_back(sphere2);
    scene.elements.push_back(sphere3);
    scene.elements.push_back(p1);
    scene.elements.push_back(p2);
    scene.elements.push_back(p3);
    scene.elements.push_back(p4);
    scene.elements.push_back(p5);
    scene.elements.push_back(p6);

    PointLight* pLight = new PointLight();
    pLight->position = vec3f(2.0f, 1.0f, 3.0f);
    pLight->intensity = LightIntensity(255.0f, 255.0f, 255.0f);

    scene.pointLights.push_back(pLight);

    pCam.render(buffer, scene);

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
    dirLight.diffuse = vec3f(128.0f, 128.0f, 128.0f);
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
            rasterizer->drawTriangle(testCone.triangles[i], 0xff00ff00, dirLight, false);
            
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
    

    //vp.rotate(10.0f, vec3f(0.0f, 1.0f, 1.0f));
    //vp.rotate(45.0f, vec3f(0.0f, 1.0f, 0.0f));
    vp.scale(vec3f(0.5f, 0.5f, 0.5f));
    vp.translate(vec3f(-1.0f, -1.0f, 0.0f));

    Cylinder testCylinder = Cylinder(12, 3, 2.0f, 2.0f);

    
    if (drawCylinder) {
        for (int i = 0; i < testCylinder.triangles.size(); i++) {

            Triangle processedTriangle = testCylinder.triangles[i];

            //rasterizer->drawTriangle(processedTriangle, 0xff00ff00, pointLight, true);
            rasterizer->drawTriangle(processedTriangle, 0xff00ff00, dirLight, true);

        }
    }
    
    vp.clear();

    vp.setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.scale(vec3f(0.5f, 0.5f, 0.5f));
    vp.translate(vec3f(1.0f, -1.0f, 0.0f));

    writer->read(TGA, "in2.tga", 512, 512, rasterizer->tmpTxt);

    if (drawCylinder) {
        for (int i = 0; i < testCylinder.triangles.size(); i++) {

            Triangle processedTriangle = testCylinder.triangles[i];

            //rasterizer->drawTriangle(processedTriangle, 0xff00ff00, pointLight, true);
            rasterizer->drawTriangle(processedTriangle, 0xff00ff00, dirLight, true);

        }
    }
    writer->write(TGA, width, height, buffer->color);

    delete buffer;

    delete writer;

    delete rasterizer;
}

void test() {

    Sphere* sphere1 = new Sphere(0.7f, 0.0f, 0.0f, 5.0f);
    Ray ray = Ray(vec3f(0, 0, 4.3f), vec3f(0, 0, 1.0f));
    IntersectionResult h = sphere1->hit(ray,false);
    h.intersectionPoint1.write();
    h.intersectionPoint2.write();
}

int main()
{
    FGK();

    //test();

    //MiAGK();
}