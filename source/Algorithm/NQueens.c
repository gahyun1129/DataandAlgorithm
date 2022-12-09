#include <stdio.h>
#include <stdlib.h>

void findSolutionForQueen(int columns[], int row, int numberOfQueen, int* solutionCount) {
	if (isTreatened(columns, row)) { return; }
	if (row == numberOfQueen - 1) {
	}
	else {
		int i;
		for (i = 0; i < numberOfQueen; i++) {
			columns[row + 1] = i;
			findSolutionForQueen(columns, row + 1, numberOfQueen, solutionCount);
		}
	}
}

int isTreatened(int columns[], int newRow) {
	int currentRow = 0;
	int treatened = 0;

	while (currentRow < newRow) {
		if (columns[newRow] == columns[currentRow] || abs(columns[newRow] - columns[currentRow]) == abs(newRow - currentRow)) {
			treatened = 1;
			break;
		}
		currentRow++;
	}
	return treatened;
}