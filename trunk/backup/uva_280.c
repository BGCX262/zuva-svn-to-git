#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

#define max(a,b) (a>b)?a:b

int graph[101][101], visited[101], n, start;

void dfs(int curr) {
	if (DEBUG) {
		printf("dfs %d\n", curr);
	}

	int i, j;
	for (j = 0; j < n; j++) {
		if (graph[curr][j] && visited[j] == 0) {
			visited[j] = 1;
			dfs(j);
		}
	}
}

int main() {
	int y, i, j, t, max, from;
	for (;;) {
		scanf("%d", &n);
		if (n == 0) {
			break;
		}
		for (i = 0; i < 101; i++) {
			for (j = 0; j < 101; j++) {
				graph[i][j] = 0;
			}
		}

		for (;;) {
			scanf("%d", &from);
			if (from == 0) {
				break;
			}
			for (;;) {
				scanf("%d", &t);
				if (t == 0) {
					break;
				}
				graph[from - 1][t - 1] = 1;
			}
		}

		if (DEBUG) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					printf("[%d][%d]%d ", i, j, graph[i][j]);
				}
				printf("\n");
			}
		}

		scanf("%d", &t);
		for (i = 0; i < t; i++) {
			scanf("%d", &start);
			for (j = 0; j < n; j++) {
				visited[j] = 0;
			}
			start--;
			dfs(start);
			int noVisited = 0;
			for (j = 0; j < n; j++) {
				if (visited[j] == 0) {
					noVisited++;
				}
			}
			printf("%d", noVisited);
			for (j = 0; j < n; j++) {
				if (visited[j] == 0) {
					printf(" %d", j + 1);
				}
			}
			printf("\n");
		}
	}
	return 0;
}
