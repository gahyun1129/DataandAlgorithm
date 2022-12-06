#include <stdio.h>
#include <stdlib.h>

int boyreMoore(char* text, int textSize, int start, char* pattern, int patternSize) {
	int badCharTable[128];
	int* goodSuffTable = (int*)calloc(patternSize + 1, sizeof(int));
	int* posOfBorder = (int*)calloc(patternSize + 1, sizeof(int));
	int i = start;
	int j = 0;

	int position = -1;

	buildBST(pattern, patternSize, badCharTable);
	buildGST(pattern, patternSize, posOfBorder, goodSuffTable);

	while (i <= textSize - patternSize) {
		j = patternSize - 1;
		while (j >= 0 && pattern[j] == text[i + j]) {
			j--;
		}

		if (j < 0) {
			position = i;
			break;
		}
		else {
			i += Max(goodSuffTable[j + 1], j - badCharTable[text[i + j]]);
		}
	}
	free(posOfBorder);
	free(goodSuffTable);

	return position;
}

void buildBST(char* pattern, int patternSize, int* badCharTable) {
	int i, j;
	for (i = 0; i < 128; i++) {
		badCharTable[i] = -1;
	}

	for (j = 0; j < patternSize; j++) {
		badCharTable[pattern[j]] = j;
	}
}
void buildGST(char* pattern, int patternSize, int* posOfBorder, int* goodSuffTable) {
	int i = patternSize;
	int j = patternSize + 1;

	posOfBorder[i] = j;

	while (i > 0) {
		while (j <= patternSize && pattern[i - 1] != pattern[j - 1]) {
			if (goodSuffTable[j] == 0) {
				goodSuffTable[j] = j - i;
			}
			j = posOfBorder[j];
		}
		i--;
		j--;

		posOfBorder[i] = j;
	}

	j = posOfBorder[0];

	for (i = 0; i <= patternSize; i++) {
		if (goodSuffTable[i] == 0) {
			goodSuffTable[i] = j;
		}
		if (i == j) { j = posOfBorder[j]; }
	}
}

int Max(int a, int b) {
	if (a > b) { return a; }
	else return b;
}