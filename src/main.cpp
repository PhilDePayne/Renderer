#include <iostream>
#include "Writer.h"
#include "Buffer.h"

int main()
{
    unsigned int width = 56;
    unsigned int height = 56;
    unsigned int color = 0xff00afff;

    Buffer* buffer = new Buffer(width * height, color);

    Writer* writer = new Writer();

    writer->write(TGA, width, height, buffer->color);

    delete writer;

    delete buffer;
}

