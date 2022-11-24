#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int dataSet[], int length) {
	int i = 0, j = 0, temp = 0, cont = 0;
	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - (i + 1); j++) {
			if (dataSet[j] > dataSet[j + 1]) {
				cont = 1;
			}
		}
	}
	if (cont == 1) {
		for (i = 0; i < length - 1; i++) {
			for (j = 0; j < length - (i + 1); j++) {
				if (dataSet[j] > dataSet[j + 1]) {
					temp = dataSet[j + 1];
					dataSet[j + 1] = dataSet[j];
					dataSet[j] = temp;
				}
			}
		}
	}
}