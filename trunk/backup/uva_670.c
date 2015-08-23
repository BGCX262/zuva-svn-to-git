#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 102

#define NUL -1
static int map[NODE_MAX][NODE_MAX], visited[NODE_MAX], match[NODE_MAX], leftX[NODE_MAX], leftY[NODE_MAX], rightX[NODE_MAX], rightY[NODE_MAX], leftSize,
		rightSize;

int dfs(int curr) {
	int i;
	for (i = 1; i <= rightSize; i++) {
		if (!visited[i] && map[curr][i]) {
			visited[i] = 1;
			if (dfs(match[i]) || !match[i]) {
				match[i] = curr;
				return 1;
			}
		}
	}
	return 0;
}

/**
 * 670
 */
int main(int argc, char * argv[]) {
	int i, j, testCase, testCaseNum;
	scanf("%d", &testCaseNum);
	for (testCase = 0; testCase < testCaseNum; testCase++) {
		memset(map, 0, NODE_MAX * NODE_MAX * sizeof(int));
		memset(match, 0, NODE_MAX * sizeof(int));
		scanf("%d %d", &leftSize, &rightSize);
		for (i = 1; i <= leftSize; i++) {
			int xTemp, yTemp;
			scanf("%d %d", &xTemp, &yTemp);
			leftX[i] = xTemp;
			leftY[i] = yTemp;
		}

		for (i = 1; i <= rightSize; i++) {
			int xTemp, yTemp;
			scanf("%d %d", &xTemp, &yTemp);
			rightX[i] = xTemp;
			rightY[i] = yTemp;
		}

		for (i = 1; i < leftSize; i++) {
			for (j = 1; j <= rightSize; j++) {
				float dist1 = sqrt(
						(float) (leftX[i] - rightX[j]) * (float) (leftX[i] - rightX[j]) + (float) (leftY[i] - rightY[j]) * (float) (leftY[i] - rightY[j]));
				float dist2 = sqrt(
						(float) (leftX[i + 1] - rightX[j]) * (float) (leftX[i + 1] - rightX[j])
								+ (float) (leftY[i + 1] - rightY[j]) * (float) (leftY[i + 1] - rightY[j]));
				float dist3 = sqrt(
						(float) (leftX[i] - leftX[i + 1]) * (float) (leftX[i] - leftX[i + 1])
								+ (float) (leftY[i] - leftY[i + 1]) * (float) (leftY[i] - leftY[i + 1]));
				if (dist1 + dist2 <= dist3 * 2) {
					map[i][j] = 1;
				}
			}
		}

		if (DEBUG) {
			printf("map:\n");
			for (i = 1; i <= leftSize; i++) {
				for (j = 1; j <= rightSize; j++) {
					printf("[%d][%d]%d ", i, j, map[i][j]);
				}
				printf("\n");
			}

		}

		for (i = 1; i <= leftSize; i++) {
			memset(visited, 0, NODE_MAX * sizeof(int));
			dfs(i);
		}
		if (DEBUG) {
			printf("match:\n");
			for (i = 1; i <= rightSize; i++) {
				printf("[%d]%d ", i, match[i]);
			}
			printf("\n");
		}

		int howManyInterest = 0;
		for (i = 1; i <= rightSize; i++) {
			if (match[i])
				howManyInterest++;
		}

		if (testCase > 0) {
			printf("\n");
		}

		printf("%d\n", howManyInterest + leftSize);
		for (i = 1; i <= leftSize; i++) {
			if (i == 1) {
				printf("%d %d", leftX[i], leftY[i]);
			} else {
				printf(" %d %d", leftX[i], leftY[i]);
			}

			for (j = 1; j <= rightSize; j++) {
				if (match[j] == i) {
					printf(" %d %d", rightX[j], rightY[j]);
				}
			}
		}
		printf("\n");
	}
	return 0;
}
