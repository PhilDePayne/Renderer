#include "Mesh.h"

#include "Vec3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void Mesh::loadObj(const char* filename)
{
    std::ifstream in(filename, std::ios::in);
    if (!in)
    {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(1);

    }
    std::string line;
    while (std::getline(in, line))
    {
        //check v for vertices
        if (line.substr(0, 2) == "v ") {
            std::istringstream v(line.substr(2));
            vec3f vert;
            double x, y, z;
            v >> x; v >> y; v >> z;
            vert = vec3f(x, y, z);
            vertices.push_back(vert);
        }

        //check for faces
        else if (line.substr(0, 2) == "f ") {
            int a, b, c; //to store mesh index
            int A, B, C; //to store normal index
            int u, v, w; //to store texture index

            const char* chh = line.c_str();
            sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &a, &u, &A, &b, &v, &B, &c, &w, &C); //here it read the line start with f and store the corresponding values in the variables

            a--; b--; c--;
            A--; B--; C--;

            std::cout << a << b << c << std::endl;

            faceIndex.push_back(a); //textureIndex.push_back(A);
            faceIndex.push_back(b); //textureIndex.push_back(B);
            faceIndex.push_back(c); //textureIndex.push_back(C);
        }
    }

    for (unsigned int i = 0; i < faceIndex.size(); i++)
    {
        vec3f meshData;
        meshData = vec3f(vertices[faceIndex[i]].x, vertices[faceIndex[i]].y, vertices[faceIndex[i]].z);
        meshVertices.push_back(meshData);
    }

    for (int z = 0; z < meshVertices.size()/3; z++) {

        triangles.push_back(Triangle(meshVertices[z * 3], meshVertices[z * 3 +1], meshVertices[z * 3 + 2]));

    }

    

}