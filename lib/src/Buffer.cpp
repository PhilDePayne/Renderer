#include "Buffer.h"

Buffer::Buffer(unsigned int size, unsigned int color)
{
	this->color = new unsigned int[size];

	for (int i = 0; i < size; i++) {
		this->color[i] = color;
	}
}

Buffer::~Buffer()
{
	delete color;
}
