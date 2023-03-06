#include <iostream>
#include "Writer.h"
#include "Buffer.h"
#include "Rasterizer.h"
#include "Vec3.h"
#include "Sphere.h"

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

    Sphere sphere = Sphere(10, 0, 0, 0);

    delete x;
    delete y;
    delete a;
    delete b;

}

int main()
{
    unsigned int width = 256;
    unsigned int height = 256;
    unsigned int color = 0xff7caf31;

    FGK();

    Buffer* buffer = new Buffer(width, height, color);

    Writer* writer = new Writer();

    Rasterizer* rasterizer = new Rasterizer(*buffer);

    Vec3<float>* x = new Vec3<float>(0.0f, 1.0f, 0.0f);
    Vec3<float>* y = new Vec3<float>(1.0f, -1.0f, 0.0f);
    Vec3<float>* z = new Vec3<float>(-1.0f, -1.0f, 0.0f);

    Triangle* triangle = new Triangle(*x, *y, *z);

    rasterizer->drawTriangle(*triangle, 0xff012345);

    writer->write(TGA, width, height, buffer->color);

    delete buffer;

    delete writer;

    delete rasterizer;

    delete triangle;

    delete x;
    delete y;
    delete z;

}
