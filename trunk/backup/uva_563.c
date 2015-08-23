#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 51*51*2+3

#define NUL -1

static int capacity[NODE_MAX][NODE_MAX], adj[NODE_MAX][NODE_MAX], adjSize[NODE_MAX], parent[NODE_MAX], flow[NODE_MAX][NODE_MAX], fifo[NODE_MAX], next[4][2] = {
		{ -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } }, numNode, rowSize, colSize, size, fifoStart, fifoEnd;

int getFront(int x, int y) {
	if (x < 1 || x > rowSize || y < 1 || y > colSize)
		return NUL;
	return (x - 1) * colSize + y;
}

int getRear(int x, int y) {
	if (x < 1 || x > rowSize || y < 1 || y > colSize)
		return NUL;
	return (x - 1) * colSize + y + size;
}

void addFifo(int curr) {
	if (DEBUG) {
		printf("add %d\n", curr);
	}

	if (fifoStart == -1 && fifoEnd == -1) {
		fifo[0] = curr;
		fifoStart = fifoEnd = 0;
	} else {
		fifoEnd++;
		fifo[fifoEnd] = curr;
	}

	if (DEBUG) {
		if (fifoStart != -1) {
			int i;
			for (i = fifoStart; i <= fifoEnd; i++) {
				printf(" %d , ", fifo[i]);
			}
			printf("\n");

		}
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
		fifoStart++;
	}

	if (DEBUG) {
		printf("remove %d\n", r);
	}
	if (DEBUG) {
		if (fifoStart != -1) {
			int i;
			for (i = fifoStart; i <= fifoEnd; i++) {
				printf(" %d , ", fifo[i]);
			}
			printf("\n");

		}
	}

	return r;
}

int bfs(int from, int to) {
	int i, j, pathFlow[numNode], curr;
	fifoStart = fifoEnd = -1;
	for (i = 1; i <= numNode; i++) {
		parent[i] = NUL;
		pathFlow[i] = 0;
	}
	parent[from] = -2;
	pathFlow[from] = INT_MAX;

	addFifo(from);
	while ((curr = removeFifo()) != NUL) {
		for (i = 0; i < adjSize[curr]; i++) {
			int currTo = adj[curr][i];
			int remain = capacity[curr][currTo] - flow[curr][currTo];
			if (DEBUG) {
				printf("capacity from %d to %d is %d, and flow is %d\n", curr, currTo, capacity[curr][currTo], flow[curr][currTo]);
			}
			if (remain > 0 && parent[currTo] == NUL) {

				parent[currTo] = curr;
				pathFlow[currTo] = remain < pathFlow[curr] ? remain : pathFlow[curr];
				if (currTo == to) {
					return pathFlow[to];
				} else {
					addFifo(currTo);
				}
			}
		}
	}
	return 0;
}

void makeConnection(int f, int t) {
	adj[f][adjSize[f]++] = t;
	capacity[f][t] = 1;
}

int EdmondsKarp(int from, int to) {
	int maxFlow = 0;
	for (;;) {
		if (DEBUG) {
			printf("from %d to %d ==============================\n", from, to);
		}
		int max = bfs(from, to);
		if (DEBUG) {
			printf("from %d to %d get %d *****************************\n", from, to, max);
		}
		if (max == 0)
			break;
		maxFlow += max;
		int v = to;
		while (v != from) {
			int u = parent[v];
			if (DEBUG) {
				printf("parent[%d] %d\n", u, v);
			}
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
	int i, j, testCase = 1, numTest, k, bankSize;
	scanf("%d", &numTest);
	while (numTest-- > 0) {
		scanf("%d", &rowSize);
		scanf("%d", &colSize);
		scanf("%d", &bankSize);
		int bankX[bankSize], bankY[bankSize];
		for (i = 0; i < bankSize; i++) {
			scanf("%d", &bankX[i]);
			scanf("%d", &bankY[i]);
		}
		numNode = rowSize * colSize * 2 + 3;
		for (i = 1; i <= numNode; i++) {
			for (j = 0; j < 5; j++) {
				adj[i][j] = NUL;
			}
			adjSize[i] = 0;
		}
		for (i = 1; i <= numNode; i++) {
			for (j = 1; j <= numNode; j++) {
				capacity[i][j] = 0;
			}
		}

		size = rowSize * colSize;
		for (i = 1; i <= rowSize; i++) {
			for (j = 1; j <= colSize; j++) {
				int front = getFront(i, j);
				int rear = getRear(i, j);
				if (DEBUG) {
					printf("front [%d, %d] -> %d\n", i, j, front);
					printf("rear [%d, %d] -> %d\n", i, j, rear);
				}
				makeConnection(front, rear);
			}
		}

		for (i = 2; i <= rowSize - 1; i++) {
			for (j = 2; j <= colSize - 1; j++) {
				int rear = getRear(i, j);
				for (k = 0; k < 4; k++) {
					int x = i + next[k][0];
					int y = j + next[k][1];
					int neighbourFront = getFront(x, y);
					if (neighbourFront != NUL) {
						makeConnection(rear, neighbourFront);
					}
				}
			}
		}

		int end = getRear(rowSize, colSize) + 1;
		int start = end + 1;

		for (j = 1; j <= colSize; j++) {
			makeConnection(getRear(1, j), end);
			makeConnection(getRear(rowSize, j), end);
		}

		for (i = 2; i <= rowSize - 1; i++) {
			makeConnection(getRear(i, 1), end);
			makeConnection(getRear(i, colSize), end);
		}
		for (i = 1; i <= numNode; i++) {
			for (j = 1; j <= numNode; j++) {
				flow[i][j] = 0;
			}
		}

		for (i = 0; i < bankSize; i++) {
			int bank = getFront(bankX[i], bankY[i]);
			makeConnection(start, bank);
		}

		if (DEBUG) {
			printf("============= adj ===================\n");
			for (i = 1; i <= numNode; i++) {
				for (j = 0; j < adjSize[i]; j++) {
					printf("[ %d ][ %d ] %d, ", i, j, adj[i][j]);
				}
				printf("\n");
			}
		}

		if (EdmondsKarp(start, end) == bankSize) {
			printf("possible\n");
		} else {
			printf("not possible\n");
		}
	}
	return 0;
}
