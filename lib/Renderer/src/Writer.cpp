#include "Writer.h"

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
