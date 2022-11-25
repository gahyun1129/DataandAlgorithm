#include <stdio.h>
#include <stdlib.h>

typedef struct tagPoint {
	int id;
	double point;
} Point;

Point* BinarySearch(Point pointList[], int size, double target) {
	int left, right, mid;

	left = 0;
	right = size - 1;

	while (left <= right) {
		mid = (left + right) / 2;

		if (target == pointList[mid].point) {
			return &(pointList[mid]);
		}
		else if (target > pointList[mid].point) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return NULL;
}