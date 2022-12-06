#include <stdio.h>

//최대 경계의 너비 보관용 테이블
void preprocess(char* pattern, int patternSize, int* border) {
	int i = 0, j = -1;

	border[0] = -1;

	while (i < patternSize) {
		while (j > -1 && pattern[i] != pattern[j]) { j = border[j]; }
		i++;
		j++;

		border[i] = j;
	}
}int knuthMorrisPratt(char* text, int textSize, int start, char* pattern, int patternSize) {
	int i = start;
	int j = 0;
	int position = -1;

	int* border = (int*)calloc(patternSize + 1, sizeof(int));
	preprocess(pattern, patternSize, border);

	while (i < textSize) {
		while (j >= 0 && text[i] != pattern[j]) { j = border[j]; }
		i++;
		j++;

		if (j == patternSize) {
			position = i - j;
			break;
		}
	}
	free(border);
	return position;
}