#pragma once

#include <fstream>
#include <vector>

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
	unsigned int tmpBuffer[256 * 256];

	Writer() {};

	~Writer() {};

	void write(Extension extension, unsigned int width, unsigned int height, unsigned int* buffer);

	void read(Extension extension, const char* fileName, unsigned int width, unsigned int height, std::vector<unsigned int>& buffer);
	void read(Extension extension, const char* fileName, unsigned int width, unsigned int height, unsigned int* buffer);
};

