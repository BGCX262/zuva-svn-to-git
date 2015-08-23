#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * 562
 */
int main(int argc, char * argv[]) {
	int cents[50005], coins[100];
	int test, i, j, j2, r, coinsSize, allCents;
	for (scanf("%d", &test); test > 0; test--) {
		allCents = 0;
		coinsSize = 0;
		scanf("%d", &coinsSize);
		for (i = 0; i < coinsSize; i++) {
			scanf("%d", &coins[i]);
			allCents += coins[i];
		}
		memset(cents, -1, sizeof(int) * (allCents + 1));
		cents[0] = 0;
		for (j = 0; j < coinsSize; j++) {
			for (i = 1; i <= allCents; i++) {
				if (i == coins[j] && cents[i] == -1) {
					cents[i] = j;
				} else if (cents[i] != -1 && cents[i] != j && cents[i + coins[j]] == -1) {
					cents[i + coins[j]] = j;
				} else {
					continue;
				}
			}
			if (DEBUG) {
				printf("AllCents %d\n", allCents);
				int k;
				for (k = 0; k <= allCents; k++) {
					if (cents[k] != -1)
						printf("[%d] %d\n", k, cents[k]);
				}
				printf("\n");
			}
		}
		int x;
		for (x = allCents / 2; x > -1; x--) {
			if (cents[x] != -1) {
				break;
			}
		}
		printf("%d\n", allCents - 2 * x);
	}
	return 0;
}
