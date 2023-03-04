#pragma once

#include <fstream>

enum Extension {
	TGA
};

class Writer
{
private:

	unsigned short headerTGA[9] = {
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0064, 0x0064,
		0x0820 };



public:

	Writer() {};

	~Writer() {};

	void write(Extension extension, unsigned int width, unsigned int height, unsigned int* buffer);
};

