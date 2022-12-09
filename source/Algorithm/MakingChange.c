#include <stdio.h>

void getChange(int price, int pay, int coinUnits[], int change[], int size) {
	int i = 0;
	int changeAmount = pay - price;

	for (i = 0; i < size; i++) {
		change[i] = countCoins(changeAmount, coinUnits[i]);
		changeAmount = changeAmount - (coinUnits[i] * change[i]);
	}
}

int countCoins(int amount, int coinUnit) {
	int coinCount = 0;
	int currentAmount = amount;
	while (currentAmount >= coinUnit) {
		coinCount++;
		currentAmount = currentAmount - coinUnit;
	}

	return coinCount;
}
