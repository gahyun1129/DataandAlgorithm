#include <stdio.h>
#include <string.h>

void swap(int* A, int* B) {
	int Temp = *A;
	*A = *B;
	*B = Temp;
}

int Partition(int dataSet[], int left, int right) {
	int first = left;
	int pivot = dataSet[first];

	++left;

	while (left <= right) {
		while (dataSet[left] <= pivot && left < right) {
			++left;
		}
		while (dataSet[right] <= pivot && left <= right) {
			--right;
		}
		if (left < right) {
			swap(&dataSet[left], &dataSet[right]);
		}
		else {
			break;
		}
	}

	swap(&dataSet[first], &dataSet[right]);

	return right;
}

void QuickSort(int dataSet[], int left, int right) {
	if (left < right) {
		int index = Partition(dataSet, left, right);

		QuickSort(dataSet, left, index - 1);
		QuickSort(dataSet, index + 1, right);
	}
}