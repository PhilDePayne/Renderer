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

    Light dirLight;

    dirLight.position = vec3f(-1.0f, 0.0f, 0.0f);
    dirLight.diffuse = vec3f(0.0f, 255.0f, 0.0f);
    dirLight.ambient = vec3f(0.0f, 56.0f, 25.0f);
    dirLight.specular = vec3f(0.0f, 0.0f, 1.0f);
    dirLight.shininess = 0.2f;

    VertexProcessor vp = VertexProcessor();
    vp.setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
    vp.setLookAt(vec3f(0.0f, 0.0f, 10.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(0.0f, 1.0f, 0.0f));

    vp.rotate(0.0f, vec3f(1.0f, 0.0f, 0.0f));
    //vp.rotate(30.0f, vec3f(1.0f, 1.0f, 0.0f));
    //vp.scale(vec3f(0.1f, 0.1f, 0.1f));
    //vp.translate(vec3f(0.2f, -2.0f, 0.0f));

    Cone testCone = Cone(12, 2.0f, 2.0f);
    
    printf("\n %f %f %f", dirLight.position.x, dirLight.position.y, dirLight.position.z);

    for (int i = 0; i < testCone.triangles.size(); i++) {

        Triangle processedTriangle = Triangle(Vec3<vec3f>(vp.process(testCone.triangles[i].a),
                                                            vp.process(testCone.triangles[i].b),
                                                            vp.process(testCone.triangles[i].c)),
            Vec3<vec3f>(testCone.triangles[i].normalsA, testCone.triangles[i].normalsB, testCone.triangles[i].normalsC));


        vec4f tmpA = vp.obj2World * processedTriangle.normalsA;
        processedTriangle.normalsA = vec3f(tmpA.x, tmpA.y, tmpA.z);
        vec4f tmpB = vp.obj2World * processedTriangle.normalsB;
        processedTriangle.normalsB = vec3f(tmpB.x, tmpB.y, tmpB.z);
        vec4f tmpC = vp.obj2World * processedTriangle.normalsC;
        processedTriangle.normalsC = vec3f(tmpC.x, tmpC.y, tmpC.z);

        processedTriangle.normalsA.normalize();
        processedTriangle.normalsB.normalize();
        processedTriangle.normalsC.normalize();

        printf("\n %f %f %f", processedTriangle.normalsA.x, processedTriangle.normalsA.y, processedTriangle.normalsA.z);
        printf("\n %f %f %f", processedTriangle.normalsB.x, processedTriangle.normalsB.y, processedTriangle.normalsB.z);
        printf("\n %f %f %f", processedTriangle.normalsC.x, processedTriangle.normalsC.y, processedTriangle.normalsC.z);

        //CALCULATE

        float intensityA = std::max(processedTriangle.normalsA.dot(dirLight.position), 0.0f);
        float intensityB = std::max(processedTriangle.normalsB.dot(dirLight.position), 0.0f);
        float intensityC = std::max(processedTriangle.normalsC.dot(dirLight.position), 0.0f);

        vec3f colorA = dirLight.diffuse * intensityA;
        vec3f colorB = dirLight.diffuse * intensityB;
        vec3f colorC = dirLight.diffuse * intensityC;

        colorA = colorA.max(dirLight.ambient);
        colorB = colorB.max(dirLight.ambient);
        colorC = colorC.max(dirLight.ambient);

        writeHex(hexFromRgb(colorA));
        writeHex(hexFromRgb(colorB));
        writeHex(hexFromRgb(colorC));

        processedTriangle.setColors(hexFromRgb(colorA), hexFromRgb(colorB), hexFromRgb(colorC));
        //processedTriangle.setColors(0xffff0000, 0xff00ff00, 0xff0000ff);

        writeHex(processedTriangle.getColors().x);
        writeHex(processedTriangle.getColors().y);
        writeHex(processedTriangle.getColors().z);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }

    /*
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

        processedTriangle.setColors(0xff000000, 0xff000000, 0xff000000);

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

        processedTriangle.setColors(0xff000000, 0xff000000, 0xff000000);

        rasterizer->drawTriangle(processedTriangle, 0xff00ff00);

    }
    

    vp.clear();
    */

    

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