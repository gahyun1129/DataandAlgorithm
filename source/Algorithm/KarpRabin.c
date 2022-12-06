#include <stdio.h>
#include <math.h>

int karpRabin(char* text, int textSize, int start, char* pattern, int patternSize) {
	int i = 0, j = 0;
	int coefficient = pow(2, patternSize - 1); // 2^(m-1)
	int hashText = hash(text, patternSize);
	int hashPattern = hash(pattern, patternSize);

	for (i = start; i <= textSize - patternSize; i++) {
		hashText = reHash(text, i, patternSize, hashText, coefficient);
		if (hashPattern == hashText) {
			for (j = 0; j < patternSize; j++) {
				if (text[j + i] != pattern[j]) { break; }
			}
			if (j >= patternSize) { return i; }
		}
	}
	return -1;
}

int hash(char* string, int size) {
	int i = 0, hashValue = 0;
	for (i = 0; i < size; i++) {
		hashValue = string[i] + (hashValue * 2);
	}
	return hashValue;
}

int reHash(char* string, int start, int size, int hashPrev, int coefficient) {
	if (start == 0) { return hashPrev; }
	return string[start + size - 1] + ((hashPrev - coefficient * string[start - 1]) * 2);
}