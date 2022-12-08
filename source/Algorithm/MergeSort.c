#include <stdio.h>
#include <stdlib.h>

void mergeSort (int dataSet[], int startIndex, int endIndex) {
	int middleIndex;
	if (endIndex - startIndex < 1) {
		return;
	}

	middleIndex = (startIndex + endIndex) / 2;

	mergeSort(dataSet, startIndex, middleIndex);
	mergeSort(dataSet, middleIndex + 1, endIndex);

	merge(dataSet, startIndex, middleIndex, endIndex);
}

void merge(int dataSet[], int startIndex, int middleIndex, int endIndex) {
	int i, leftIndex = startIndex, rightIndex = middleIndex + 1, destIndex = 0;
	int* destination = (int*)malloc(sizeof(int) * (endIndex - startIndex + 1));

	while (leftIndex <= middleIndex && rightIndex <= endIndex) {
		if (dataSet[leftIndex] < dataSet[rightIndex]) {
			destination[destIndex] = dataSet[leftIndex];
			leftIndex++;
		}
		else {
			destination[destIndex] = dataSet[rightIndex];
			rightIndex++;
		}
		destIndex++;
	}

	while (leftIndex <= middleIndex) {
		destination[destIndex++] = dataSet[leftIndex++];
	}
	while (rightIndex <= endIndex) {
		destination[destIndex++] = dataSet[rightIndex++];
	}

	destIndex = 0;

	for (i = startIndex; i < endIndex; i++) {
		dataSet[i] = destination[destIndex++];
	}

	free(destination);
}