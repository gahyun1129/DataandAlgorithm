typedef unsigned long ULONG;

ULONG power(int base, int exponent) {
	if (exponent == 1) { return base; }
	else if (exponent == 0) { return 1; }

	if (exponent % 2 == 0) {
		ULONG newBase = power(base, exponent / 2);
		return newBase * newBase;
	}
	else {
		ULONG newBase = power(base, (exponent - 1) / 2);
		return (newBase * newBase) * base;
	}
}