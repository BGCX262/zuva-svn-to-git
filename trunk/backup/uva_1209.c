#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

/**
 * uva 1209
 */
static int unSize;
static char un[21][20];

void fillPrevPermutation(int curr) {
	int i, j, k;
	for (i = unSize - 2; i >= 0; i--) {
		char maxLessC = 'A' - 1;
		int maxLessI = -1;
		for (j = i + 1; j < unSize; j++) {
			if (un[curr][j] < un[curr][i] && un[curr][j] > maxLessC) {
				maxLessI = j;
				maxLessC = un[curr][j];
			}
		}
		if (maxLessI != -1) {
			char temp = un[curr][i];
			un[curr][i] = maxLessC;
			un[curr][maxLessI] = temp;
			/**
			 * sort rest chars desc
			 */
			for (j = i + 1; j < unSize - 1; j++) {
				for (k = j + 1; k < unSize; k++) {
					if (un[curr][k] > un[curr][j]) {
						temp = un[curr][k];
						un[curr][k] = un[curr][j];
						un[curr][j] = temp;
					}
				}
			}
			return;
		}
	}
}

void fillNextPermutation(int curr) {
	int i, j, k;
	for (i = unSize - 2; i >= 0; i--) {
		char minLargC = 'Z' + 1;
		int minLargI = 1000;
		for (j = i + 1; j < unSize; j++) {
			if (un[curr][j] > un[curr][i] && un[curr][j] < minLargC) {
				minLargI = j;
				minLargC = un[curr][j];
			}
		}
		if (minLargI != 1000) {
			char temp = un[curr][i];
			un[curr][i] = minLargC;
			un[curr][minLargI] = temp;
			/**
			 * sort rest chars asc
			 */
			for (j = i + 1; j < unSize - 1; j++) {
				for (k = j + 1; k < unSize; k++) {
					if (un[curr][k] < un[curr][j]) {
						temp = un[curr][k];
						un[curr][k] = un[curr][j];
						un[curr][j] = temp;
					}
				}
			}
			return;
		}
	}
}

int main() {
	int i, j;
	char line[256];
	while (fgets(line, 256, stdin) != NULL) {
		unSize = 0;
		for (i = 0; i < strlen(line); i++) {
			if (line[i] >= 'A' && line[i] <= 'Z') {
				un[10][unSize++] = line[i];
			}
		}

		for (i = 9; i >= 0; i--) {
			for (j = 0; j < unSize; j++) {
				un[i][j] = un[i + 1][j];
			}

			fillPrevPermutation(i);
		}
		for (i = 11; i < 21; i++) {
			for (j = 0; j < unSize; j++) {
				un[i][j] = un[i - 1][j];
			}
			fillNextPermutation(i);
		}
		int largestMinDist = -1, largestMinDistI;
		for (i = 0; i < 21; i++) {
			int minDist = 1000;
			for (j = 0; j < unSize - 1; j++) {
				int dist = abs(un[i][j] - un[i][j + 1]);
				if (dist < minDist) {
					minDist = dist;
				}
			}
			if (minDist > largestMinDist) {
				largestMinDist = minDist;
				largestMinDistI = i;
			}
		}
		for (j = 0; j < unSize; j++) {
			printf("%c", un[largestMinDistI][j]);
		}
		printf("%d\n", largestMinDist);
	}

	return 0;
}

