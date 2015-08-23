#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

/**
 * uva 220
 */
struct Point {
	int row;
	int col;
	char color;
};
static char curr, opp;
static struct Point target, moves[64], board[8][8];
static int movesSize;

int inBoard(int i) {
	return i >= 0 && i <= 7;
}

struct Point * leftBracket(struct Point * p) {
	int left = p->col - 1;
	while (inBoard(left) && board[p->row][left].color == opp) {
		left--;
	}
	if (inBoard(left) && left != p->col - 1 && board[p->row][left].color == curr) {
		return &board[p->row][left];
	}
	return NULL;
}

struct Point * rightBracket(struct Point * p) {
	int right = p->col + 1;
	while (inBoard(right) && board[p->row][right].color == opp) {
		right++;
	}
	if (inBoard(right) && right != p->col + 1 && board[p->row][right].color == curr) {
		return &board[p->row][right];
	}
	return NULL;
}

struct Point * upBracket(struct Point * p) {
	int up = p->row - 1;
	while (inBoard(up) && board[up][p->col].color == opp) {
		up--;
	}
	if (inBoard(up) && up != p->row - 1 && board[up][p->col].color == curr) {
		return &board[up][p->col];
	}
	return NULL;
}

struct Point * downBracket(struct Point * p) {
	int down = p->row + 1;
	while (inBoard(down) && board[down][p->col].color == opp) {
		down++;
	}
	if (inBoard(down) && down != p->row + 1 && board[down][p->col].color == curr) {
		return &board[down][p->col];
	}
	return NULL;
}

struct Point * leftUpBracket(struct Point * p) {
	int up = p->row - 1, left = p->col - 1;
	while (inBoard(up) && inBoard(left) && board[up][left].color == opp) {
		up--;
		left--;
	}
	if (inBoard(up) && up != p->row - 1 && left != p->col - 1 && inBoard(left) && board[up][left].color == curr) {
		return &board[up][left];
	}
	return NULL;
}

struct Point * leftDownBracket(struct Point * p) {
	int down = p->row + 1, left = p->col - 1;
	while (inBoard(down) && inBoard(left) && board[down][left].color == opp) {
		down++;
		left--;
	}
	if (inBoard(down) && down != p->row + 1 && left != p->col - 1 && inBoard(left) && board[down][left].color == curr) {
		return &board[down][left];
	}
	return NULL;
}

struct Point * rightDownBracket(struct Point * p) {
	int down = p->row + 1, right = p->col + 1;
	while (inBoard(down) && inBoard(right) && board[down][right].color == opp) {
		down++;
		right++;
	}
	if (inBoard(down) && down != p->row + 1 && right != p->col + 1 && inBoard(right) && board[down][right].color == curr) {
		return &board[down][right];
	}
	return NULL;
}

struct Point * rightUpBracket(struct Point * p) {
	int up = p->row - 1, right = p->col + 1;
	while (inBoard(up) && inBoard(right) && board[up][right].color == opp) {
		up--;
		right++;
	}
	if (inBoard(up) && up != p->row - 1 && right != p->col + 1 && inBoard(right) && board[up][right].color == curr) {
		return &board[up][right];
	}
	return NULL;
}

int bracketed(struct Point * p) {
	return leftBracket(p) != NULL || rightBracket(p) != NULL || upBracket(p) != NULL || downBracket(p) != NULL || leftUpBracket(p) != NULL
			|| leftDownBracket(p) != NULL || rightDownBracket(p) != NULL || rightUpBracket(p) != NULL;
}

int cmp_i_j(const void * a, const void * b) {
	struct Point * p1 = (struct Point *) a;
	struct Point * p2 = (struct Point *) b;
	if (p1->row != p2->row) {
		return p1->row - p2->row;
	} else {
		return p1->col - p2->col;
	}
}

void list() {
	int i, j;
	movesSize = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j].color == '-' && bracketed(&board[i][j])) {
				moves[movesSize].row = i;
				moves[movesSize].col = j;
				movesSize++;
			}
		}
	}
	if (movesSize > 0) {
		qsort(moves, movesSize, sizeof(struct Point), cmp_i_j);
		for (i = 0; i < movesSize; i++) {
			printf("(%d,%d)", moves[i].row + 1, moves[i].col + 1);
			if (i < movesSize - 1) {
				printf(" ");
			}
		}
	} else {
		printf("No legal move.");
	}

	printf("\n");
}

void switchCurr() {
	char t = curr;
	curr = opp;
	opp = t;
}

int changeColor() {
	struct Point * p;
	int i, j, legal = 0;
	p = leftBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (j = p->col + 1; j < target.col; j++) {
			board[target.row][j].color = curr;
		}
	}
	p = rightBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (j = p->col - 1; j > target.col; j--) {
			board[target.row][j].color = curr;
		}
	}

	p = upBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (i = p->row + 1; i < target.row; i++) {
			board[i][target.col].color = curr;
		}
	}

	p = downBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (i = p->row - 1; i > target.row; i--) {
			board[i][target.col].color = curr;
		}
	}

	p = leftUpBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (i = p->row + 1, j = p->col + 1; i < target.row; i++, j++) {
			board[i][j].color = curr;
		}
	}

	p = leftDownBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (i = p->row - 1, j = p->col + 1; i > target.row; i--, j++) {
			board[i][j].color = curr;
		}
	}

	p = rightDownBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (i = p->row - 1, j = p->col - 1; i > target.row; i--, j--) {
			board[i][j].color = curr;
		}
	}
	p = rightUpBracket(&target);
	if (p != NULL) {
		legal = 1;
		for (i = p->row + 1, j = p->col - 1; i < target.row; i++, j--) {
			board[i][j].color = curr;
		}
	}
	return legal;
}

void move() {
	int legal = changeColor();
	if (!legal) {
		switchCurr();
		changeColor();
	}
	board[target.row][target.col].color = curr;
	switchCurr();
	/**
	 * print color
	 */
	int i, j, black = 0, white = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j].color == 'B') {
				black++;
			} else if (board[i][j].color == 'W') {
				white++;
			}
		}
	}
	printf("Black - %2d White - %2d\n", black, white);
}

void quit() {
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			printf("%c", board[i][j].color);
		}
		printf("\n");
	}
}

int main() {
	int game;
	char line[256], command;
	fgets(line, 256, stdin);
	for (sscanf(line, "%d", &game); game > 0; game--) {
		int i, j;
		for (i = 0; i < 8; i++) {
			fgets(line, 256, stdin);
			for (j = 0; j < 8; j++) {
				board[i][j].color = line[j];
				board[i][j].row = i;
				board[i][j].col = j;
			}
		}
		for (;;) {
			fgets(line, 256, stdin);
			command = line[0];
			if (command == 'Q') {
				quit();
				break;
			} else if (command == 'W') {
				curr = 'W';
				opp = 'B';
			} else if (command == 'B') {
				curr = 'B';
				opp = 'W';
			} else if (command == 'L') {
				list();
			} else if (command == 'M') {
				target.row = line[1] - '0' - 1;
				target.col = line[2] - '0' - 1;
				move();
			}
		}
		if (game > 1) {
			printf("\n");
		}
	}

	return 0;
}

