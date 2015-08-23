#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

#define NULL_JUMP -1

#define Q_MAX 6000

struct Vertex {
	int x, y, ort, cost, type;
}typedef VERTEX;

int row, col, beginX, beginY, endX, endY, queueStart, queueEnd;
int block[60][60];
int blockCost[60][60];
VERTEX queue[Q_MAX];

void addQueue(VERTEX v) {
	if (queueStart == -1 && queueEnd == -1) {
		queueStart = queueEnd = 0;
	} else {
		queueEnd = (queueEnd + 1) % Q_MAX;
	}
	if (DEBUG) {
		printf("add to queue %d %d ort %d cost %d\n", v.x, v.y, v.ort, v.cost);
	}
	queue[queueEnd] = v;
}

VERTEX getQueue() {
	VERTEX result;
	result.x = -1;
	result.y = -1;

	if (queueStart != -1) {
		result = queue[queueStart];
	}
	if (queueStart == queueEnd) {
		queueStart = queueEnd = -1;
	} else {
		queueStart = (queueStart + 1) % Q_MAX;
	}
	return result;
}

int valid(int x, int y) {
	if (x >= 0 && x <= row && block[x][y] != 1 && y >= 0 && y <= col) {
		return 1;
	}
	return 0;
}

void moveSouth(VERTEX curr, int step) {
	int nextX = curr.x + step;
	int nextY = curr.y;

	if (valid(nextX, nextY) == 0)
		return;

	int i, j;
	for (i = 1; i <= step; i++) {
		if (block[curr.x + i][curr.y]) {
			return;
		}
	}

	int c = curr.cost;
	if (curr.ort == 0) {
	} else if (curr.ort == 1) {
		c++;
	} else if (curr.ort == 2) {
		c++;
		c++;
	} else if (curr.ort == 3) {
		c++;
	}
	VERTEX v;
	v.x = nextX;
	v.y = nextY;
	v.ort = 0;
	v.cost = c + 1;
	addQueue(v);
}

void moveWest(VERTEX curr, int step) {
	int nextX = curr.x;
	int nextY = curr.y - step;

	if (valid(nextX, nextY) == 0)
		return;

	int i, j;
	for (i = 1; i <= step; i++) {
		if (block[curr.x][curr.y - i] == 1) {
			return;
		}
	}

	int c = curr.cost;
	if (curr.ort == 0) {
		c++;
	} else if (curr.ort == 1) {
	} else if (curr.ort == 2) {
		c++;
	} else if (curr.ort == 3) {
		c++;
		c++;
	}
	VERTEX v;
	v.x = nextX;
	v.y = nextY;
	v.ort = 1;
	v.cost = c + 1;
	addQueue(v);
}

void moveNorth(VERTEX curr, int step) {
	int nextX = curr.x - step;
	int nextY = curr.y;

	if (valid(nextX, nextY) == 0)
		return;

	int i, j;
	for (i = 1; i <= step; i++) {
		if (block[curr.x - i][curr.y] == 1) {
			return;
		}
	}

	int c = curr.cost;
	if (curr.ort == 0) {
		c++;
		c++;
	} else if (curr.ort == 1) {
		c++;
	} else if (curr.ort == 2) {
	} else if (curr.ort == 3) {
		c++;
	}
	VERTEX v;
	v.x = nextX;
	v.y = nextY;
	v.ort = 2;
	v.cost = c + 1;
	addQueue(v);
}

void moveEast(VERTEX curr, int step) {
	int nextX = curr.x;
	int nextY = curr.y + step;
	if (valid(nextX, nextY) == 0)
		return;

	int i, j;
	for (i = 1; i <= step; i++) {
		if (block[curr.x][curr.y + i] == 1) {
			return;
		}
	}

	int c = curr.cost;
	if (curr.ort == 0) {
		c++;
	} else if (curr.ort == 1) {
		c++;
		c++;
	} else if (curr.ort == 2) {
		c++;
	} else if (curr.ort == 3) {
	}
	VERTEX v;
	v.x = nextX;
	v.y = nextY;
	v.ort = 3;
	v.cost = c + 1;
	addQueue(v);
}

int main() {
	int i, j, t, x = 0;
	char orientation[10];
	VERTEX * curr;
	for (;;) {

		x++;
		scanf("%d %d\n", &row, &col);
		if (row == 0 && col == 0)
			break;
		for (i = 0; i <= row; i++) {
			for (j = 0; j <= col; j++) {
				block[i][j] = blockCost[i][j] = 0;
			}
		}
		for (i = 0; i <= row; i++) {
			block[i][0] = block[i][col] = 1;
		}
		for (j = 0; j <= col; j++) {
			block[0][j] = block[row][j] = 1;
		}

		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				scanf("%d", &t);
				if (t) {
					block[i][j] = block[i][j + 1] = block[i + 1][j] = block[i + 1][j + 1] = 1;
				}
			}
		}
		scanf("%d %d %d %d %s\n", &beginX, &beginY, &endX, &endY, orientation);
		queueStart = queueEnd = -1;
		VERTEX v;
		v.x = beginX;
		v.y = beginY;
		v.cost = 0;

		if (strcmp(orientation, "south") == 0) {
			v.ort = 0;
		} else if (strcmp(orientation, "west") == 0) {
			v.ort = 1;
		} else if (strcmp(orientation, "north") == 0) {
			v.ort = 2;
		} else if (strcmp(orientation, "east") == 0) {
			v.ort = 3;
		} else {
			printf("orientation is not correct %s\n", orientation);
		}
		addQueue(v);
		VERTEX curr;
		while (1) {
			curr = getQueue();
			if (DEBUG) {
				printf("%d %d ort %d cost %d\n", curr.x, curr.y, curr.ort, curr.cost);
			}
			if (curr.x == -1) {
				break;
			}

			if (blockCost[curr.x][curr.y] == 0) {
				blockCost[curr.x][curr.y] = curr.cost;
			} else {
				if (blockCost[curr.x][curr.y] > curr.cost) {
					blockCost[curr.x][curr.y] = curr.cost;
				} else {
					continue;
				}
			}

			for (i = 0; i < 3; i++) {
				moveSouth(curr, i + 1);
				moveWest(curr, i + 1);
				moveNorth(curr, i + 1);
				moveEast(curr, i + 1);
			}
		}
		if (beginX == endX && beginY == endY) {
			printf("0\n");
		} else if (blockCost[endX][endY] == 0) {
			printf("-1\n");
		} else {
			printf("%d\n", blockCost[endX][endY]);
		}
	}
	return 0;
}
