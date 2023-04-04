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
#include "Cone.h"
#include "Cylinder.h"
#include "Torus.h"
#include "Light.h"
#include "MathHelper.h"

unsigned int width = 2048;
unsigned int height = 2048;
unsigned int color = 0xff7caf31;

void FGK() {

    Buffer buffer = Buffer(width, height, color);

    Writer writer = Writer();

    OrthoCamera orthoCamera = OrthoCamera();
    PerspectiveCamera pCam = PerspectiveCamera();

    Sphere sphere1 = Sphere(0.1f, 0.0f, 0.0f, 50.0f);
    Sphere sphere2 = Sphere(0.1f, 1.0f, 0.0f, 40.0f);

    Sphere sphere3 = Sphere(10.0f, 0.0f, 0.0f, 50.0f);
    Sphere sphere4 = Sphere(10.0f, 10.0f, 0.0f, 40.0f);

    Triangle triangle = Triangle(vec3f(0.0f, 1.0f, 1.0f), vec3f(1.0f, 0.0f, 1.0f), vec3f(-1.0f, 0.0f, 1.0f));

    Mesh mesh;

    mesh.loadObj("Top_Hat_0.obj");

    //orthoCamera.render(buffer, sphere1);
    //orthoCamera.render(buffer, sphere2);
    //orthoCamera.render(buffer, triangle);
    orthoCamera.render(buffer, mesh);

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

    Light dirLight;

    dirLight.position = vec3f(1.0f, 0.0f, 0.0f);
    dirLight.diffuse = vec3f(0.0f, 255.0f, 0.0f);
    dirLight.ambient = vec3f(0.0f, 56.0f, 25.0f);
    dirLight.specular = vec3f(0.0f, 0.0f, 1.0f);
    dirLight.shininess = 128.0f;

    Light pointLight;

    pointLight.position = vec3f(0.0f, 0.0f, -3.0f);
    pointLight.diffuse = vec3f(0.0f, 255.0f, 0.0f);
    pointLight.ambient = vec3f(0.0f, 56.0f, 25.0f);
    pointLight.specular = vec3f(0.0f, 0.0f, 1.0f);
    pointLight.shininess = 128.0f;
    
    
    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(90.0f, vec3f(0.0f, 0.0f, 1.0f));
    //vp.rotate(30.0f, vec3f(1.0f, 1.0f, 0.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    //vp.translate(vec3f(-0.5f, 1.0f, 0.0f));

    Cone testCone = Cone(4, 2.0f, 2.0f);

    for (int i = 0; i < testCone.triangles.size(); i++) {

        Triangle processedTriangle = Triangle(Vec3<vec3f>(vp.process(testCone.triangles[i].a),
                                                            vp.process(testCone.triangles[i].b),
                                                            vp.process(testCone.triangles[i].c)),
            Vec3<vec3f>(testCone.triangles[i].normalsA, testCone.triangles[i].normalsB, testCone.triangles[i].normalsC));

        /*
        processedTriangle.setColors(vp.calculateDirLight(testCone.triangles[i].a, testCone.triangles[i].normalsA, dirLight),
                                    vp.calculateDirLight(testCone.triangles[i].b, testCone.triangles[i].normalsB, dirLight), 
                                    vp.calculateDirLight(testCone.triangles[i].c, testCone.triangles[i].normalsC, dirLight));
                                    */
                                    
        
        processedTriangle.setColors(vp.calculatePointLight(testCone.triangles[i].a, testCone.triangles[i].normalsA, pointLight),
                                    vp.calculatePointLight(testCone.triangles[i].b, testCone.triangles[i].normalsB, pointLight),
                                    vp.calculatePointLight(testCone.triangles[i].c, testCone.triangles[i].normalsC, pointLight));
                                    
                                    

        //processedTriangle.setColors(0xffff0000, 0xff00ff00, 0xff0000ff);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }
    vp.clear();
    
    

    /*
    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(20.0f, vec3f(1.0f, 0.0f, 1.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    //vp.translate(vec3f(1.2f, -1.0f, 0.0f));

    Cylinder testCylinder = Cylinder(12, 3, 2.0f, 1.0f);

    
    for (int i = 0; i < testCylinder.triangles.size(); i++) {

        Triangle processedTriangle = Triangle(vp.process(testCylinder.triangles[i].a),
            vp.process(testCylinder.triangles[i].b),
            vp.process(testCylinder.triangles[i].c));

        processedTriangle.setColors(vp.calculateLight(testCylinder.triangles[i].a, testCylinder.triangles[i].normalsA, dirLight),
            vp.calculateLight(testCylinder.triangles[i].b, testCylinder.triangles[i].normalsB, dirLight),
            vp.calculateLight(testCylinder.triangles[i].c, testCylinder.triangles[i].normalsC, dirLight));
        //processedTriangle.setColors(0xffff0000, 0xff00ff00, 0xff0000ff);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }
    vp.clear();
    */

    /*
    vp.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(45.0f, vec3f(1.0f, 0.0f, 1.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    //vp.translate(vec3f(0.2f, 3.0f, 0.0f));

    Torus testTorus = Torus();


    for (int i = 0; i < testTorus.triangles.size(); i++) {

        Triangle processedTriangle = Triangle(vp.process(testTorus.triangles[i].a),
            vp.process(testTorus.triangles[i].b),
            vp.process(testTorus.triangles[i].c));

        processedTriangle.setColors(vp.calculateDirLight(testTorus.triangles[i].a, testTorus.triangles[i].normalsA, dirLight),
            vp.calculateDirLight(testTorus.triangles[i].b, testTorus.triangles[i].normalsB, dirLight),
            vp.calculateDirLight(testTorus.triangles[i].c, testTorus.triangles[i].normalsC, dirLight));

        //processedTriangle.setColors(0xff000000, 0xff000000, 0xff000000);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }
    */
    

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

}