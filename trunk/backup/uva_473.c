#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int dp[1028][128][128], songs[1028], songsSize, disksSize, diskLen;

int max2(int a, int b) {
	return a > b ? a : b;
}

int max3(int a, int b, int c) {
	int t = max2(a, b);
	return c > t ? c : t;
}

int burn(int currSong, int leftTime, int leftDisk) {
	if (currSong > songsSize)
		return 0;
	if (dp[currSong][leftTime][leftDisk] != -1)
		return dp[currSong][leftTime][leftDisk];

	if (leftTime >= songs[currSong]) {
		if (leftDisk > 0) {
			return dp[currSong][leftTime][leftDisk] = max3(1 + burn(currSong + 1, leftTime - songs[currSong], leftDisk),
					1 + burn(currSong + 1, diskLen - songs[currSong], leftDisk - 1), burn(currSong + 1, leftTime, leftDisk));
		} else {
			return dp[currSong][leftTime][leftDisk] = max2(1 + burn(currSong + 1, leftTime - songs[currSong], leftDisk), burn(currSong + 1, leftTime, leftDisk));
		}
	} else {
		if (leftDisk > 0) {
			return dp[currSong][leftTime][leftDisk] = max2(1 + burn(currSong + 1, diskLen - songs[currSong], leftDisk - 1),
					burn(currSong + 1, leftTime, leftDisk));
		} else {
			return dp[currSong][leftTime][leftDisk] = burn(currSong + 1, leftTime, leftDisk);
		}
	}
}

void printDP() {
	int i, j, k;
	printf("songs ...\n");
	for (i = 0; i <= songsSize; i++) {
		printf("%d ", songs[i]);
	}
	printf("\n");
	printf("dp ...\n");
	for (i = 0; i <= songsSize; i++) {
		for (j = 0; j <= diskLen; j++) {
			for (k = 0; k <= disksSize; k++) {
				printf("[%d][%d][%d]%d ", i, j, k, dp[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

/**
 * 473
 */
int main(int argc, char * argv[]) {

	int test, i, j, k;
	char c;
	for (scanf("%d", &test); test > 0; test--) {
		scanf("%d %d %d", &songsSize, &diskLen, &disksSize);
		for (i = 1; i <= songsSize; i++) {
			scanf("%d%c", &songs[i], &c);
		}
		for (i = 0; i <= songsSize; i++) {
			for (j = 0; j <= diskLen; j++) {
				for (k = 0; k <= disksSize; k++) {
					dp[i][j][k] = -1;
				}
			}
		}

		if (DEBUG)
			printDP();
		printf("%d\n", burn(1, 0, disksSize));
		if (DEBUG)
			printDP();
		if (test > 1) {
			printf("\n");
		}
	}
	return 0;
}
