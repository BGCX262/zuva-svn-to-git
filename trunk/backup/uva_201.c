#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define EPS 0.000000001

static char board[10][10];
static int m, n, size[11];

int isSquare(int row, int col, int size) {
	int i, j;
	/*check left top*/
	if (board[row][col] != 'B') {
		return 0;
	}
	/*check left border vertically*/
	for (i = row + 1; i - row < size; i++) {
		if (board[i][col] != 'B' && board[i][col] != 'V') {
			return 0;
		}
	}

	/*check left down*/
	if (board[row + size][col] != 'B' && board[row + size][col] != 'H') {
		return 0;
	}

	/*check down border horizontally*/
	for (j = col + 1; j - col < size; j++) {
		if (board[row + size][j] != 'B' && board[row + size][j] != 'H') {
			return 0;
		}
	}

	/*check up border horizontally*/
	for (j = col + 1; j - col < size; j++) {
		if (board[row][j] != 'B' && board[row][j] != 'H') {
			return 0;
		}
	}

	/*check right top*/
	if (board[row][col + size] != 'B' && board[row][col + size] != 'V') {
		return 0;
	}

	/*check right border vertically*/
	for (i = row + 1; i - row < size; i++) {
		if (board[i][col + size] != 'B' && board[i][col + size] != 'V') {
			return 0;
		}
	}

	/*no need to check right down*/
	return 1;
}

/**
 * 201
 */
int main(int argc, char * argv[]) {
	int i, j, m, n, prob = 0;
	while (scanf("%d\n", &n) == 1) {
		prob++;
		scanf("%d\n", &m);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				board[i][j] = '0';
			}
		}
		for (i = 1; i < 10; i++) {
			size[i] = 0;
		}

		char v;
		for (i = 0; i < m; i++) {
			int row, col;
			scanf("%c %d %d\n", &v, &row, &col);
			row -= 1;
			col -= 1;
			if (v == 'H') {
				if (board[row][col] == 'V') {
					board[row][col] = 'B';
				} else {
					board[row][col] = 'H';
				}
			} else if (v == 'V') {
				if (board[col][row] == 'H') {
					board[col][row] = 'B';
				} else {
					board[col][row] = 'V';
				}
			}
		}

		if (DEBUG) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					printf("%c ", board[i][j]);
				}
				printf("\n");
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (board[i][j] == 'B') {
					int s;
					for (s = 1; s <= n; s++) {
						if (isSquare(i, j, s) == 1) {
							size[s]++;
						}
					}
				}
			}
		}

		if (prob > 1) {
			printf("\n**********************************\n\n");
		}
		printf("Problem #%d\n\n", prob);

		int found = 0;
		for (i = 1; i <= n; i++) {
			if (size[i] > 0) {
				found = 1;
				printf("%d square (s) of size %d\n", size[i], i);
			}
		}
		if (found == 0) {
			printf("No completed squares can be found.\n");
		}

	}

	return 0;
}
