#pragma once
class Buffer
{
private:

	unsigned int height;

	unsigned int width;

	unsigned int size;


public:

	Buffer(unsigned int height, unsigned int width, unsigned int color);

	~Buffer();

	unsigned int getSize();

	unsigned int getHeight();

	unsigned int getWidth();

	unsigned int* color;
};

