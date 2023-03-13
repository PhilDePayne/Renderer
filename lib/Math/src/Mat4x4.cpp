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

vec4f Mat4x4::operator*(vec4f& v) {

	vec4f ret;

	for (int i = 0; i < 4; i++) {

		ret[i] = v[i] * (columns[i][0] + columns[i][1] + columns[i][2] + columns[i][3]);

	}

	return ret;

}

vec4f Mat4x4::operator*(vec3f& v) {

	vec4f tmp = vec4f(v);

	return this->operator*(tmp);

}

vec4f Mat4x4::operator[](const int& idx) {

	return columns[idx];
}

void Mat4x4::transpose() { //TODO: one loop

	vec4f rows[4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rows[i][j] = columns[j][i];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			columns[i][j] = rows[i][j];
		}
	}

}

void Mat4x4::write() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			printf("%f ", columns[i][j]);

		}

		printf("\n");
	}

}

void Mat4x4::identity() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			if (i == j) {
				columns[i][i] = 1;
			}
			else {
				columns[i][j] = 0;
			}

		}
	}
}