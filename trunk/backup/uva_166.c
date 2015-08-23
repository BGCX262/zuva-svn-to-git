#include<stdio.h>
#include<string.h>
#define DEBUG 0
/**
 * denomanation is den
 */
static int coins[6], minReturnChange[2048], target, min, den[6] = { 1, 2, 4, 10, 20, 40 };

int initMinReturnChange() {
	int i, j;
	minReturnChange[0] = 0;
	for (i = 1; i <= 1005; i++) {
		minReturnChange[i] = 2048;
	}

	for (i = 1; i <= 1005; i++) {
		for (j = 0; j < 6; j++) {
			if (den[j] <= i && 1 + minReturnChange[i - den[j]] < minReturnChange[i]) {
				minReturnChange[i] = 1 + minReturnChange[i - den[j]];
			}
		}
	}
}

void dfs(int num, int value) {
	int i, j;
	if (DEBUG) {
		printf("num:%d, value:%d, [%d,%d,%d,%d,%d,%d]\n", num, value, coins[0], coins[1], coins[2], coins[3], coins[4], coins[5]);
	}
	if (value < target) {
		for (i = 0; i < 6; i++) {
			if (coins[i] != 0) {
				coins[i]--;
				dfs(num + 1, value + den[i]);
				coins[i]++;
			}
		}
		return;
	} else {
		/*
		 * calculate how many coins are needed
		 */
		int returnNum = minReturnChange[value - target];
		if (returnNum + num < min) {
			if (DEBUG) {
				printf("return:%d + num:%d < %d\n", returnNum, num, min);
			}
			min = returnNum + num;
		}
	}
}

int main() {
	int r;
	float value;
	initMinReturnChange();
	while (1) {
		r = scanf("%d%d%d%d%d%d", &coins[0], &coins[1], &coins[2], &coins[3], &coins[4], &coins[5]);
		if (coins[0] == 0 && coins[1] == 0 && coins[2] == 0 && coins[3] == 0 && coins[4] == 0 && coins[5] == 0)
			break;
		r = scanf("%f", &value);
		value = value / 0.05;
		target = value;
		if (DEBUG) {
			printf("value is %f, target %d\n", value, target);
		}
		min = 2064;
		dfs(0, 0);
		printf("%3d\n", min);
	}
	return 0;
}

