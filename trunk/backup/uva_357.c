#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

int compare(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

int coins[5] = { 1, 5, 10, 25, 50 };

/**
 * 357
 */
int main(int argc, char * argv[]) {
	unsigned long long ways[30005];
	memset(ways, 0, sizeof(unsigned long long) * 30005);
	int money, i, j, change, coin;
	ways[0] = 1;
	for (i = 0; i < 5; i++) {
		coin = coins[i];
		for (j = coin; j < 30005; j++) {
			ways[j] += ways[j - coin];
		}
	}

	if (DEBUG) {
		for (i = 0; i < 30001; i++) {
			printf("ways[%d] %llu\n", i, ways[i]);
		}
	}

	while (scanf("%d", &money) == 1) {
		if (ways[money] > 1) {
			printf("There are %llu ways to produce %d cents change.\n", ways[money], money);
		} else {
			printf("There is only 1 way to produce %d cents change.\n", money);
		}
	}
	return 0;
}
