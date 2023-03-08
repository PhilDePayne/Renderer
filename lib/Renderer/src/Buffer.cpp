#include "Buffer.h"

Buffer::Buffer(unsigned int height, unsigned int width, unsigned int color) : height(height), width(width)
{
	size = height * width;

	this->color = new unsigned int[size]();

	this->depth = new unsigned int[size]();

	for (int i = 0; i < size; i++) {
		this->color[i] = color;
	}
}

Buffer::~Buffer()
{
}

unsigned int Buffer::getHeight() {

	return height;

}

unsigned int Buffer::getWidth() {

	return width;

}

unsigned int Buffer::getSize() {

	return size;

}
