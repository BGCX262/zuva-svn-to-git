#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * 507
 */
int main(int argc, char * argv[]) {
	int stop[20005];

	int test, i, j, r, m, n, best, bestI, bestJ, curr;
	for (scanf("%d", &test), r = 1; r <= test; r++) {
		scanf("%d", &n);
		memset(stop, 0, sizeof(int) * (n + 1));
		for (j = 1; j < n; j++) {
			scanf("%d", &stop[j]);
		}
		best = stop[1];
		bestI = 1;
		bestJ = 2;
		curr = 0;
		for (j = 2, i = 1; j <= n; j++) {
			curr += stop[j - 1];
			if (curr > best) {
				bestI = i;
				bestJ = j;
				best = curr;
			} else if (curr == best && (j - i) > (bestJ - bestI)) {
				bestI = i;
				bestJ = j;
			}
			if (curr < 0) {
				i = j;
				curr = 0;
			}
		}
		if (best >= 0) {
			printf("The nicest part of route %d is between stops %d and %d\n", r, bestI, bestJ);
		} else {
			printf("Route %d has no nice parts\n", r);
		}
	}
	return 0;
}
