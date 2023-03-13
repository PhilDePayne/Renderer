#include "Mat4x4.h"

Mat4x4::Mat4x4() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//columns[i] = vec4f(0, 0, 0, 0);
			columns[i][j] = 0;
		}
	}

}

//[a1, b1, c1, d1]
//[a2, b2, c2, d2]
//[a3, b3, c3, d3]
//[a4, b4, c4, d4]

Mat4x4::Mat4x4(vec4f a, vec4f b, vec4f c, vec4f d) {

	columns[0] = a; 
	columns[1] = b;
	columns[2] = c; 
	columns[3] = d; 
}

Mat4x4 Mat4x4::operator*(Mat4x4& mat) {

	Mat4x4 ret;
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {

			ret.columns[i][j] = 0;

			for (k = 0; k < 4; k++)
				ret.columns[i][j] += columns[i][k] * mat.columns[k][j]; //TODO: const Mat4x4& mat
		}
	}

	return ret;
}

void Mat4x4::write() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			printf("%f ", columns[i][j]);

		}

		printf("\n");
	}

}