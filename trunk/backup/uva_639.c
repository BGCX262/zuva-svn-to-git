#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * 639
 */
static char matrix[4][4];

static int max, size;

void dfs(int x, int y, int n) {
	int i, j, nextX = x, nextY = y, rook, wall;
	if (DEBUG) {
		printf("dfs %d %d %d\n", x, y, n);
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				printf("%c", matrix[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	if (x == -1 && y == -1) {
		return;
	}

	if (x == size - 1 && y == size - 1) {
		nextX = nextY = -1;
	} else {
		if (y == size - 1) {
			nextY = 0;
			nextX++;
		} else {
			nextY++;
		}
	}

	if (matrix[x][y] == 'X') {
		dfs(nextX, nextY, n);
		return;
	} else if (matrix[x][y] == '.') {
		rook = wall = -1;
		for (j = y - 1; j >= 0; j--) {
			if (matrix[x][j] == 'X' && wall == -1) {
				wall = j;
			}
			if (matrix[x][j] == 'O' && rook == -1) {
				rook = j;
			}
		}
		if ((rook != -1 && wall != -1 && rook > wall) || (wall == -1 && rook != -1)) {
			if (DEBUG) {
				printf("left is break\n");
			}
			dfs(nextX, nextY, n);
			return;
		}

		rook = wall = -1;
		for (j = y + 1; j < size; j++) {
			if (matrix[x][j] == 'X' && wall == -1) {
				wall = j;
			}
			if (matrix[x][j] == 'O' && rook == -1) {
				rook = j;
			}
		}
		if ((rook != -1 && wall != -1 && rook < wall) || (wall == -1 && rook != -1)) {
			if (DEBUG) {
				printf("right is break\n");
			}
			dfs(nextX, nextY, n);
			return;
		}

		rook = wall = -1;
		for (i = x - 1; i >= 0; i--) {
			if (matrix[i][y] == 'X' && wall == -1) {
				wall = i;
			}
			if (matrix[i][y] == 'O' && rook == -1) {
				rook = i;
			}
		}
		if ((rook != -1 && wall != -1 && rook > wall) || (wall == -1 && rook != -1)) {
			if (DEBUG) {
				printf("up is break\n");
			}
			dfs(nextX, nextY, n);
			return;
		}

		rook = wall = -1;
		for (i = x + 1; i < size; i++) {
			if (matrix[i][y] == 'X' && wall == -1) {
				wall = i;
			}
			if (matrix[i][y] == 'O' && rook == -1) {
				rook = i;
			}
		}
		if ((rook != -1 && wall != -1 && rook < wall) || (wall == -1 && rook != -1)) {
			if (DEBUG) {
				printf("down is break\n");
			}
			dfs(nextX, nextY, n);
			return;
		}
		matrix[x][y] = 'O';
		if (n + 1 > max) {
			max = n + 1;
		}
		dfs(nextX, nextY, n + 1);
		matrix[x][y] = '.';
		dfs(nextX, nextY, n);
	}

}

int main(int argc, char * argv[]) {
	int i, j;
	char line[8];
	for (; scanf("%d\n", &size) && size != 0;) {
		max = 0;
		for (i = 0; i < size; i++) {
			fgets(line, 8, stdin);
			for (j = 0; j < size; j++) {
				matrix[i][j] = line[j];
			}
		}
		dfs(0, 0, 0);
		printf("%d\n", max);
	}

	return 0;
}

