#include "Writer.h"

#define STB_IMAGE_IMPLEMENTATION

void Writer::write(Extension extension, unsigned int width, unsigned int height, unsigned int* buffer)
{
	if (extension == TGA) {

		FILE* f;

		headerTGA[6] = width;
		headerTGA[7] = height;

		errno_t err = fopen_s(&f, "out.tga", "wb+");
		if (err == 0) {

			fwrite(headerTGA, 2, 9, f);
			fwrite(buffer, 4, width * height, f);
			fclose(f);
		}
		else {
			return;
		}

	}
}

void Writer::read(Extension extension, const char* fileName, unsigned int width, unsigned int height, std::vector<unsigned int>& buffer) {

	if (extension == TGA) {

		FILE* f;

		unsigned int* tmpHeader[9];

		errno_t err = fopen_s(&f, fileName, "rb+");
		if (err == 0) {
			printf("READING");

			fread(tmpHeader, 2, 9, f);
			fread(&buffer[0], sizeof(buffer[0]), buffer.size(), f);
			fclose(f);
		}
		else {
			return;
		}

	}

}

void Writer::read(Extension extension, const char* fileName, unsigned int width, unsigned int height, unsigned int* buffer) {

	if (extension == TGA) {

		FILE* f;

		unsigned int* tmpHeader[9];

		errno_t err = fopen_s(&f, fileName, "rb+");
		if (err == 0) {
			printf("READING");

			fread(tmpHeader, 2, 9, f);
			fread(buffer, 4, width * height, f);
			fclose(f);
		}
		else {
			return;
		}

	}

}