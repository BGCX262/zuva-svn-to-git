#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

#define INTER_MAX 11
#define DELAY_MAX 999999

static int dist[INTER_MAX], set[INTER_MAX];
static int numInter;

int getMinDist() {
	int i, minInter = 0, min = DELAY_MAX;
	for (i = 1; i <= numInter; i++) {
		if (set[i] && dist[i] < min) {
			minInter = i;
			min = dist[i];
		}
	}
	return minInter;
}

/**
 * 341
 */
int main(int argc, char * argv[]) {
	int i, j, from, to, testCase = 0;

	while (1) {
		scanf("%d", &numInter);
		if (numInter == 0)
			break;
		int prev[numInter + 1], path[numInter + 1], delay[numInter + 1][numInter + 1], pathSize = 0;
		for (i = 1; i <= numInter; i++) {
			dist[i] = DELAY_MAX;
			prev[i] = i;
			path[i] = i;
			set[i] = 1;
			for (j = 1; j <= numInter; j++) {
				delay[i][j] = DELAY_MAX;
			}
		}

		for (i = 1; i <= numInter; i++) {
			int numLeadAway;
			scanf("%d", &numLeadAway);
			for (j = 0; j < numLeadAway; j++) {
				int interTemp, delayTemp;
				scanf("%d", &interTemp);
				scanf("%d", &delayTemp);
				delay[i][interTemp] = delayTemp;
			}
		}
		scanf("%d", &from);
		scanf("%d", &to);
		dist[from] = 0;
		int minInter;
		while ((minInter = getMinDist()) != 0) {
			set[minInter] = 0;
			if (to == minInter)
				break;

			for (j = 1; j <= numInter; j++) {
				if (delay[minInter][j] != DELAY_MAX) {
					if (dist[j] > dist[minInter] + delay[minInter][j]) {
						dist[j] = dist[minInter] + delay[minInter][j];
						prev[j] = minInter;
					}
				}
			}
		}

		int index = to;
		path[pathSize++] = to;
		while (prev[index] != index) {
			path[pathSize++] = prev[index];
			index = prev[index];
		}
		/*path[pathSize++] = index;*/

		printf("Case %d: Path =", ++testCase);
		for (i = pathSize - 1; i >= 0; i--) {
			printf(" %d", path[i]);
		}
		printf("; %d second delay\n", dist[to]);
	}

	return 0;
}
