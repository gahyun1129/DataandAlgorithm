#include <stdio.h>

typedef unsigned long ULONG;

typedef struct tagMatrix2x2 {
	ULONG data[2][2];
}matrix2x2;

matrix2x2 matrix2x2_multiply(matrix2x2 a, matrix2x2 b) {
	matrix2x2 c;

	c.data[0][0] = a.data[0][0] * b.data[0][0] + a.data[0][1] * b.data[1][0];
	c.data[0][1] = a.data[0][0] * b.data[1][0] + a.data[0][1] * b.data[1][1];
	c.data[1][0] = a.data[1][0] * b.data[0][0] + a.data[1][1] * b.data[1][0];
	c.data[1][1] = a.data[1][0] * b.data[1][0] + a.data[1][1] * b.data[1][1];

	return c;
}

matrix2x2 matrix2x2_Power(matrix2x2 a, int n) {
	if (n > 1) {
		a = matrix2x2_Power(a, n / 2);
		a = matrix2x2_multiply(a, a);

		if (n & 1) {
			matrix2x2 b;
			b.data[0][0] = 1; b.data[0][1] = 1;
			b.data[1][0] = 1; b.data[1][1] = 0;

			a = matrix2x2_multiply(a, b);
		}
	}

	return a;
}

ULONG fibonacci(int n) {
	matrix2x2 a;
	a.data[0][0] = 1; a.data[0][1] = 1;
	a.data[1][0] = 1; a.data[1][1] = 0;

	a = matrix2x2_Power(a, n);

	return a.data[0][1];
}