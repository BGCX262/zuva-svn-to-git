#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

#define FIFO_SIZE 1000

static int edge[200][200], color[200], fifo[FIFO_SIZE], fifoStart, fifoEnd, nodeSize;

void addFifo(int curr) {
	if (DEBUG) {
		printf("addFifo %d\n", curr);
	}

	if (fifoStart == -1 && fifoEnd == -1) {
		fifo[0] = curr;
		fifoStart = fifoEnd = 0;
	} else {
		fifoEnd = (fifoEnd + 1) % FIFO_SIZE;
		fifo[fifoEnd] = curr;
	}
}

int removeFifo() {

	if (fifoStart == -1 && fifoEnd == -1) {
		return -1;
	}
	int r = fifo[fifoStart];
	if (fifoStart == fifoEnd) {
		fifoStart = fifoEnd = -1;
	} else {
		fifoStart = (fifoStart + 1) % FIFO_SIZE;
	}

	if (DEBUG) {
		printf("removeFifo %d\n", r);
	}
	return r;
}

int isBiColor(int curr) {
	int i, j;
	color[curr] = 0;
	addFifo(curr);
	while ((curr = removeFifo()) != -1) {
		for (i = 0; i < nodeSize; i++) {
			if (curr == i)
				continue;
			if (edge[curr][i] && color[i] == color[curr]) {
				return 0;
			} else if (edge[curr][i] && color[i] == 2) {
				color[i] = (color[curr] + 1) % 2;
				addFifo(i);
			}
		}
	}
	return 1;
}

/**
 * 10004
 */
int main(int argc, char * argv[]) {
	int i, j, m, n, edgeSize;
	for (;;) {
		fifoStart = -1;
		fifoEnd = -1;

		for (i = 0; i < 200; i++) {
			for (j = 0; j < 200; j++) {
				edge[i][j] = 0;
			}
		}
		for (i = 0; i < 200; i++) {
			color[i] = 2;
		}

		scanf("%d", &nodeSize);
		if (nodeSize == 0)
			break;
		scanf("%d", &edgeSize);
		for (i = 0; i < edgeSize; i++) {
			int n1, n2;
			scanf("%d %d", &n1, &n2);
			edge[n1][n2] = 1;
			edge[n2][n1] = 1;
		}

		if (isBiColor(0)) {
			printf("BICOLORABLE.\n");
		} else {
			printf("NOT BICOLORABLE.\n");
		}

	}

	return 0;
}
