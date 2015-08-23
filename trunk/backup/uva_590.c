#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int cost[10][10][1024], n, k;

int compare(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

int getMinCost(int city, int day) {
	if (day == 0) {
		return cost[0][city][day];
	}
	int min = 1 << 16;
	int i;
	for (i = 0; i < n; i++) {
		if (i == city || cost[i][city][day] == 0)
			continue;

		int temp = getMinCost(i, day - 1) + cost[i][city][day];
		if (min > temp) {
			min = temp;
		}
	}
	return (min == (1 << 16)) ? 0 : min;
}

/**
 * 590
 */
int main(int argc, char * argv[]) {
	int test, i, j, d, period;
	for (test = 1;; test++) {
		scanf("%d %d", &n, &k);
		if (n == 0 && k == 0)
			break;

		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				for (d = 0; d < k; d++) {
					cost[i][j][d] = 0;
				}
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (i == j)
					continue;

				scanf("%d", &period);
				for (d = 0; d < (k > period ? k : period); d++) {
					if (d < period) {
						scanf("%d", &cost[i][j][d]);
					} else {
						cost[i][j][d] = cost[i][j][d % period];
					}
				}
			}
		}

		/**
		 * minCost[a][b] means min cost when fly from 1 to a on b day
		 */
		unsigned long long minCost[n][k];
		for (i = 0; i < n; i++) {
			minCost[i][0] = cost[0][i][0];
		}

		for (d = 1; d < k; d++) {
			for (i = 0; i < n; i++) {
				int min = 1 << 30;
				for (j = 0; j < n; j++) {
					if (i == j || cost[j][i][d] == 0 || minCost[j][d - 1] == 0)
						continue;

					int temp = minCost[j][d - 1] + cost[j][i][d];
					if (temp < min) {
						min = temp;
					}
				}
				minCost[i][d] = ((min == (1 << 30)) ? 0 : min);
			}
		}

		if (minCost[n - 1][d - 1]) {
			printf("Scenario #%d\nThe best flight costs %llu.\n\n", test, minCost[n - 1][d - 1]);
		} else {
			printf("Scenario #%d\nNo flight possible.\n\n", test);
		}
	}
	return 0;
}
