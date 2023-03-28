#include "Torus.h"
#include "const.h"

Torus::Torus() {

    generate();

}

void Torus::generate() {
    int u, v;
    float r0 = 0.2, r1 = 0.1;
    float theta, phi;
    vec3f p[4];

    for (u = 0; u < 360; u += gDu) {
        //printf("theta = %d\n",u);
        for (v = 0; v < 360; v += gDv) {
            theta = (u)*DTOR;
            phi = (v)*DTOR;
            p[0].x = cos(theta) * (r0 + r1 * cos(phi));
            p[0].y = sin(theta) * (r0 + r1 * cos(phi));
            p[0].z = r1 * sin(phi);

            theta = (u + gDu) * DTOR;
            phi = (v)*DTOR;
            p[1].x = cos(theta) * (r0 + r1 * cos(phi));
            p[1].y = sin(theta) * (r0 + r1 * cos(phi));
            p[1].z = r1 * sin(phi);

            theta = (u + gDu) * DTOR;
            phi = (v + gDv) * DTOR;
            p[2].x = cos(theta) * (r0 + r1 * cos(phi));
            p[2].y = sin(theta) * (r0 + r1 * cos(phi));
            p[2].z = r1 * sin(phi);

            theta = (u)*DTOR;
            phi = (v + gDv) * DTOR;
            p[3].x = cos(theta) * (r0 + r1 * cos(phi));
            p[3].y = sin(theta) * (r0 + r1 * cos(phi));
            p[3].z = r1 * sin(phi);

            vertices.push_back(p[0]);

            vertices.push_back(p[1]);

            vertices.push_back(p[2]);

            vertices.push_back(p[3]);

            faceIndex.push_back(12 * (360 / gDv) / 3 * (u / gDu) + 4 * (v / gDv)); //0
            faceIndex.push_back(12 * (360 / gDv) / 3 * (u / gDu) + 4 * (v / gDv) + 1); //1
            faceIndex.push_back(12 * (360 / gDv) / 3 * (u / gDu) + 4 * (v / gDv) + 3); //3

            faceIndex.push_back(12 * (360 / gDv) / 3 * (u / gDu) + 4 * (v / gDv) + 1); //1
            faceIndex.push_back(12 * (360 / gDv) / 3 * (u / gDu) + 4 * (v / gDv) + 2); //2
            faceIndex.push_back(12 * (360 / gDv) / 3 * (u / gDu) + 4 * (v / gDv) + 3); //3

        }
    }

    printf("\n %d", vertices.size());

    for (int i = 0; i < faceIndex.size() / 6; i++) {
        triangles.push_back(Triangle(vertices[faceIndex[i * 6]], vertices[faceIndex[i * 6 + 1]], vertices[faceIndex[i * 6 + 2]]));
        triangles.push_back(Triangle(vertices[faceIndex[i * 6 + 3]], vertices[faceIndex[i * 6 + 4]], vertices[faceIndex[i * 6 + 5]]));
    }
    
}