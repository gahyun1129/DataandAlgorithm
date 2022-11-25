#include <stdio.h>
#include <string.h>

void InsertionSort(int dataSet[], int length) {
	int i = 0, j = 0, value = 0;

	for (i = 1; i < length; i++) {
		if (dataSet[i - 1] <= dataSet[i]) {
			continue;
		}
		value = dataSet[i];
		for (j = 0; j < i; j++) {
			if (dataSet[j] > value) {
				memmove(&dataSet[j + 1], &dataSet[j], sizeof(dataSet[0]) * (i - j));
				dataSet[j] = value;
				break;
			}
		}
	}
}