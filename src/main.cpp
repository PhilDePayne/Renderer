#include <iostream>
#include "Writer.h"
#include "Buffer.h"
#include "Rasterizer.h"
#include "Vec3.h"

int main()
{
    unsigned int width = 256;
    unsigned int height = 256;
    unsigned int color = 0xff7caf31;

    Buffer* buffer = new Buffer(width, height, color);

    Writer* writer = new Writer();

    Rasterizer* rasterizer = new Rasterizer(*buffer);

    Vec3<float>* x = new Vec3<float>(0.0f, 1.0f, 0.0f);
    Vec3<float>* y = new Vec3<float>(1.0f, -1.0f, 0.0f);
    Vec3<float>* z = new Vec3<float>(-1.0f, -1.0f, 0.0f);

    Triangle* triangle = new Triangle(*x, *y, *z);

    *x += *y;

    std::cout << x->x << " " << x->y << " " << x->z << '\n';

    *x -= *y;

    *y += *x;

    std::cout << y->x << " " << y->y << " " << y->z << '\n';

    *y -= *x;

    std::cout << x->angleBetween(*y) << '\n';

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

