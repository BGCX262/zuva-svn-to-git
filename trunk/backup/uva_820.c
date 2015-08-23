#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 102

#define NUL -1

static int capacity[NODE_MAX][NODE_MAX], parent[NODE_MAX], flow[NODE_MAX][NODE_MAX], fifoStart, fifoEnd, fifo[NODE_MAX];
static int numNode, from, to;

void addFifo(int curr) {
	if (fifoStart == -1 && fifoEnd == -1) {
		fifo[0] = curr;
		fifoStart = fifoEnd = 0;
	} else {
		fifoEnd = (fifoEnd + 1) % NODE_MAX;
		fifo[fifoEnd] = curr;
	}
}

int removeFifo() {

	if (fifoStart == -1 && fifoEnd == -1) {
		return NUL;
	}
	int r = fifo[fifoStart];
	if (fifoStart == fifoEnd) {
		fifoStart = fifoEnd = -1;
	} else {
		fifoStart = (fifoStart + 1) % NODE_MAX;
	}
	return r;
}

int bfs() {
	int i, j, pathFlow[numNode + 1], curr;
	fifoStart = fifoEnd = -1;
	for (i = 1; i <= numNode; i++) {
		parent[i] = -1;
		pathFlow[i] = 0;
	}
	parent[from] = -2;
	pathFlow[from] = INT_MAX;

	addFifo(from);
	while ((curr = removeFifo()) != NUL) {
		for (i = 1; i <= numNode; i++) {
			if (capacity[curr][i] - flow[curr][i] > 0 && parent[i] == -1) {
				parent[i] = curr;
				pathFlow[i] = (capacity[curr][i] - flow[curr][i]) < pathFlow[curr] ? (capacity[curr][i] - flow[curr][i]) : pathFlow[curr];
				if (i == to) {
					return pathFlow[to];
				} else {
					addFifo(i);
				}
			}
		}
	}
	return 0;

}

int EdmondsKarp() {
	int maxFlow = 0, i, j;

	for (i = 1; i <= numNode; i++) {
		for (j = 1; j <= numNode; j++) {
			flow[i][j] = 0;
		}
	}

	for (;;) {
		int max = bfs();

		if (DEBUG) {
			printf("bfs get %d\n", max);
		}

		if (max == 0)
			break;
		maxFlow += max;
		int v = to;
		while (v != from) {
			int u = parent[v];
			flow[u][v] = flow[u][v] + max;
			flow[v][u] = flow[v][u] - max;
			v = u;
		}
	}

	return maxFlow;
}

/**
 * 820
 */
int main(int argc, char * argv[]) {
	int i, j, testCase = 1, numEdge;

	while (1) {
		scanf("%d", &numNode);
		if (numNode == 0)
			break;

		memset(capacity, 0, sizeof(int) * NODE_MAX * NODE_MAX);
		scanf("%d", &from);
		scanf("%d", &to);
		scanf("%d", &numEdge);
		for (i = 0; i < numEdge; i++) {
			int n1, n2, c;
			scanf("%d", &n1);
			scanf("%d", &n2);
			scanf("%d", &c);
			capacity[n1][n2] += c;
			capacity[n2][n1] += c;
		}

		if (DEBUG) {
			printf("capacity:\n");
			for (i = 1; i <= numNode; i++) {
				for (j = 1; j <= numNode; j++) {
					printf("[%d][%d]%d ", i, j, capacity[i][j]);
				}
				printf("\n");
			}
		}
		printf("Network %d\n", testCase++);
		printf("The bandwidth is %d.\n\n", EdmondsKarp());
	}

	return 0;
}
