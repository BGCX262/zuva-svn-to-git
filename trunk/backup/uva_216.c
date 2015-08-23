#include <stdio.h>
#include <math.h>

#define DEBUG 0

#define max(a,b) (a>b)?a:b

typedef struct Point {
	int x, y;
} POINT;

POINT all[8];
int n, connectSize;
double dist[8][8], currLen, minLen;
int connect[8], minConnect[8];
int visited[8];

void dfs(int curr, int prev) {
	int i, j, isEnd = 1;
	visited[curr] = 1;
	currLen += dist[curr][prev];
	connect[connectSize++] = curr;

	if (DEBUG) {
		printf("dfs curr %d currLen %.2f minLen %.2"
				"f\n", curr, currLen, minLen);
		printf("connect: ");
		for (i = 0; i < connectSize; i++) {
			printf("%d ", connect[i]);
		}
		printf("\n");
	}

	for (i = 0; i < n; i++) {
		if (i == curr || visited[i]) {
			continue;
		}
		isEnd = 0;
		dfs(i, curr);
	}
	if (isEnd) {
		if (currLen < minLen || minLen == 0) {
			minLen = currLen;
			for (j = 0; j < n; j++) {
				minConnect[j] = connect[j];
			}
			if (DEBUG) {
				printf("find shorter one currLen %.2f minLen %.2f\n", currLen, minLen);
				printf("min connect: ");
				for (i = 0; i < n; i++) {
					printf("%d ", minConnect[i]);
				}
				printf("\n");
			}
		}
	}
	visited[curr] = 0;
	currLen -= dist[curr][prev];
	connectSize--;
}

int main() {
	int i, j, count = 0;
	for (;;) {
		count++;
		scanf("%d", &n);
		if (n == 0)
			break;
		for (i = 0; i < n; i++) {
			scanf("%d %d\n", &all[i].x, &all[i].y);
		}
		for (i = 0; i < n; i++) {
			dist[i][i] = 0;
			for (j = i + 1; j < n; j++) {
				dist[i][j] = dist[j][i] = 16 + sqrt((all[i].x - all[j].x) * (all[i].x - all[j].x) + (all[i].y - all[j].y) * (all[i].y - all[j].y));
			}
		}

		if (DEBUG) {
			printf("all\n");
			for (i = 0; i < n; i++) {
				printf("all[%d]%d %d\n", i, all[i].x, all[i].y);
			}
			printf("\n");

			printf("dist\n");
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					printf("dist[%d][%d]%f ", i, j, dist[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}

		minLen = currLen = connectSize = 0;
		for (i = 0; i < n; i++) {
			visited[i] = 0;
		}
		for (i = 0; i < n; i++) {
			dfs(i, i);
		}

		printf("**********************************************************\n");
		printf("Network #%d\n", count);
		for (i = 0; i < n - 1; i++) {
			printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n", all[minConnect[i]].x, all[minConnect[i]].y, all[minConnect[i + 1]].x,
					all[minConnect[i + 1]].y, dist[minConnect[i]][minConnect[i + 1]]);
		}
		printf("Number of feet of cable required is %.2f.\n", minLen);
	}
	return 0;
}
