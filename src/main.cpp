#include <iostream>
#include "Writer.h"
#include "Buffer.h"
#include "Rasterizer.h"

int main()
{
    unsigned int width = 256;
    unsigned int height = 256;
    unsigned int color = 0xff7caf31;

    Buffer* buffer = new Buffer(width, height, color);

    Writer* writer = new Writer();

    Rasterizer* rasterizer = new Rasterizer(*buffer);

    Vec3<float>* x = new Vec3<float>(0.0f, 1.0f, 1.0f);
    Vec3<float>* y = new Vec3<float>(1.f, -1.0f, 1.0f);
    Vec3<float>* z = new Vec3<float>(-1.0f, -1.0f, 1.0f);

    Triangle* triangle = new Triangle(*x, *y, *z);

    Vec3<float>* a = new Vec3<float>(0.5f, 1.0f, 0.0f);
    Vec3<float>* b = new Vec3<float>(1.f, -1.0f, 0.0f);
    Vec3<float>* c = new Vec3<float>(-1.0f, -1.0f, 0.0f);

    Triangle* triangle1 = new Triangle(*a, *b, *c);

    triangle->setColors(0xff0000ff, 0xff00ff00, 0xffff0000);
    triangle1->setColors(0xff000fff, 0xff00fff0, 0xffff00f0);

    rasterizer->drawTriangle(*triangle, 0xff012345);
    rasterizer->drawTriangle(*triangle1, 0xff012345);

    writer->write(TGA, width, height, buffer->color);

    delete buffer;

    delete writer;

    delete rasterizer;

    delete triangle;

    delete x;
    delete y;
    delete z;

    delete triangle1;

    delete a;
    delete b;
    delete c;

}

