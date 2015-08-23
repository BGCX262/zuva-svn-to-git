#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int adj[1024][1024], numVertex, parent[1024], order[1024], nodeSize, visited[1024], fireExits[1024];

void dfs(int curr) {
	visited[curr] = 1;
	order[nodeSize++] = curr;
	int i;
	for (i = 0; i < numVertex; i++) {
		if (adj[curr][i] && visited[i] == 0) {
			dfs(i);
			parent[i] = curr;
		}
	}
}

void setFireExit(int curr) {
	if (parent[curr] != -1 && fireExits[curr] == 0 && fireExits[parent[curr]] == 0)
		fireExits[parent[curr]] = 1;
}

/**
 * 10243
 */
int main(int argc, char * argv[]) {
	int test, i, j, d, numAdj, a, numFireExit;
	for (test = 1;; test++) {
		scanf("%d", &numVertex);
		if (numVertex == 0)
			break;

		memset(adj, 0, 1024 * 1024 * sizeof(int));
		memset(parent, -1, 1024 * sizeof(int));
		memset(order, -1, 1024 * sizeof(int));
		memset(visited, 0, 1024 * sizeof(int));
		memset(fireExits, 0, 1024 * sizeof(int));
		nodeSize = 0;
		numFireExit = 0;

		for (i = 0; i < numVertex; i++) {
			scanf("%d", &numAdj);
			for (j = 0; j < numAdj; j++) {
				scanf("%d", &a);
				adj[a - 1][i] = adj[i][a - 1] = 1;
			}
			if (numAdj == 0 || (numAdj == 1 && a == i + 1))
				numFireExit++;
		}

		for (i = 0; i < numVertex; i++) {
			if (parent[i] == -1) {
				dfs(i);
			}
		}
		for (i = numVertex - 1; i >= 0; i--) {
			setFireExit(order[i]);
		}
		for (i = 0; i < numVertex; i++) {
			if (fireExits[i])
				numFireExit++;
		}
		printf("%d\n", numFireExit);

		if (DEBUG) {

			printf("adjacent \n");
			for (i = 0; i < numVertex; i++) {
				for (j = 0; j < numVertex; j++) {
					printf("[%d][%d]%d  ", i, j, adj[i][j]);
				}
				printf("\n");
			}
			printf("\nnode \n");
			for (i = 0; i < numVertex; i++) {
				printf("[%d]%d  ", i, order[i]);
			}
			printf("\n");

			printf("\nparent \n");
			for (i = 0; i < numVertex; i++) {
				printf("[%d]%d  ", i, parent[i]);
			}
			printf("\n");

			printf("\nfire exit \n");
			for (i = 0; i < numVertex; i++) {
				printf("[%d]%d  ", i, fireExits[i]);
			}
			printf("\n");

		}
	}
	return 0;
}
