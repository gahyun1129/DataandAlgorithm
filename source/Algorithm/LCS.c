#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct srtuctLCSTable {
	int** data;
}LCSTable;

int LCS(char* X, char* Y, int i, int j, LCSTable* table) {
	int m = 0, n = 0;

	for (m = 0; m <= i; m++) {
		table->data[m][0] = 0;
	}
	for (n = 0; n <= j; n++) {
		table->data[0][n] = 0;
	}

	for (m = 1; m <= i; m++) {
		for (n = 1; n <= j; n++) {
			if (X[m - 1] == Y[n - 1]) { table->data[m][n] = table->data[m - 1][n - 1] + 1; }
			else {
				if (table->data[m][n - 1] >= table->data[m - 1][n]) { table->data[m][n] = table->data[m][n - 1]; }
				else { table->data[m][n] = table->data[m - 1][n]; }
			}
		}
	}
	return table->data[i][j];
}

void LCS_traceBack(char* X, char* Y, int m, int n, LCSTable* table, char* LCS) {
	if (m == 0 || n == 0) { return; }

	if (table->data[m][n] > table->data[m][n - 1]
		&& table->data[m][n] > table->data[m-1][n-1]
		&& table->data[m][n] > table->data[m-1][n]) {
		char tempLCS[100];
		strcpy(tempLCS, LCS);
		sprintf(LCS, "%c%s", X[m - 1], tempLCS);

		LCS_traceBack(X, Y, m - 1, n - 1, table, LCS);
	}
	else if (table->data[m][n] > table->data[m][n - 1]
		&& table->data[m][n] == table->data[m][n-1]) 
	{

		LCS_traceBack(X, Y, m, n - 1, table, LCS);
	}
	else {
		LCS_traceBack(X, Y, m - 1, n, table, LCS);
	}
}