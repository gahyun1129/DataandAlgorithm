#include <stdlib.h>
typedef unsigned long ULONG;
ULONG fibonacci(int n) {
	int i;
	ULONG result;
	ULONG* fibonacciTable;

	if (n == 0 || n == 1) {
		result n;
	}

	fibonacciTable = (ULONG*)malloc(sizeof(ULONG) * (n + 1));

	fibonacciTable[0] = 1;
	fibonacciTable[1] = 1;

	for (i = 2; i <= n; i++) {
		fibonacciTable[i] = fibonacciTable[i - 1] + fibonacciTable[i - 2];
	}

	result = fibonacciTable[n];

	free(fibonacciTable);

	return result;
}
