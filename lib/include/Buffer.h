#pragma once
class Buffer
{
private:

	unsigned int size;


public:

	Buffer(unsigned int size, unsigned int color);

	~Buffer();

	unsigned int* color;
};

