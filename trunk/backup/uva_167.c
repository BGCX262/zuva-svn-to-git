#include<stdio.h>
#include<string.h>
#define DEBUG 0

static int board[8][8], score[8][8], maxScore;

int hasConflict(int i, int j) {
	/**
	 * check to see if there is conflict in [i,j]
	 */
	if (board[i][0] + board[i][1] + board[i][2] + board[i][3] + board[i][4] + board[i][5] + board[i][6] + board[i][7] > 0) {
		return 1;
	}
	if (board[0][j] + board[1][j] + board[2][j] + board[3][j] + board[4][j] + board[5][j] + board[6][j] + board[7][j] > 0) {
		return 1;
	}
	int x, y;
	for (x = i + 1, y = j + 1; x <= 7 && y <= 7; x++, y++) {
		if (board[x][y]) {
			return 1;
		}
	}
	for (x = i + 1, y = j - 1; x <= 7 && y >= 0; x++, y--) {
		if (board[x][y]) {
			return 1;
		}
	}
	for (x = i - 1, y = j - 1; x >= 0 && y >= 0; x--, y--) {
		if (board[x][y]) {
			return 1;
		}
	}
	for (x = i - 1, y = j + 1; x >= 0 && y <= 7; x--, y++) {
		if (board[x][y] == 1) {
			return 1;
		}
	}
	return 0;
}

void dfs(int curRow) {
	int i, j;
	if (curRow == 8) {
		/**
		 * find one solution
		 */

		int s = 0;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (board[i][j]) {
					s += score[i][j];
				}
			}
		}
		if (maxScore < s) {
			maxScore = s;
		}
		return;
	}
	for (j = 0; j < 8; j++) {
		if (!hasConflict(curRow, j)) {
			board[curRow][j] = 1;
			dfs(curRow + 1);
			board[curRow][j] = 0;
		}
	}
}

int main() {
	int r, i, j;
	int howManyChess;
	r = scanf("%d", &howManyChess);
	while (howManyChess-- > 0) {
		maxScore = 0;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				r = scanf("%d", &score[i][j]);
				board[i][j] = 0;
			}
		}
		dfs(0);
		printf("%5d\n", maxScore);
	}
	return 0;
}

