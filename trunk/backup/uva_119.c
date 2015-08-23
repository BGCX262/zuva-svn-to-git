#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0
#define SCENT -1

static int maxX, maxY;
static int grid[51][51];

struct Robot {
	int x;
	int y;
	char o;
};

struct Robot * alloc(int x, int y, char o) {
	struct Robot * p = malloc(sizeof(struct Robot));
	p->x = x;
	p->y = y;
	p->o = o;
	return p;
}

void print(struct Robot * m) {
	printf("[%d,%d]%c\n", m->x, m->y, m->o);
}

void turnLeft(struct Robot * m) {
/*
	if (DEBUG) {
		printf("left\n");
	}
*/
	switch (m->o) {
	case 'N':
		m->o = 'W';
		break;
	case 'S':
		m->o = 'E';
		break;
	case 'E':
		m->o = 'N';
		break;
	case 'W':
		m->o = 'S';
		break;
	}
}

void turnRight(struct Robot *m) {
/*
	if (DEBUG) {
		printf("right\n");
	}
*/
	switch (m->o) {
	case 'N':
		m->o = 'E';
		break;
	case 'S':
		m->o = 'W';
		break;
	case 'E':
		m->o = 'S';
		break;
	case 'W':
		m->o = 'N';
		break;
	}
}

/**
 * if lost then return 1
 */
int moveForward(struct Robot *m) {
	int isLost = 0;
/*
	if (DEBUG) {
		printf("forward\n");
	}
*/
	int nextX, nextY;
	switch (m->o) {
	case 'N':
		if (m->y < maxY) {
			/**
			 * within the board
			 */
			m->y++;
		} else if (m->y == maxY) {
			/**
			 * in the edge
			 */
			if (grid[m->x][m->y] != SCENT) {
				/**
				 * lost
				 */
				grid[m->x][m->y] = SCENT;
				isLost = 1;
			}
		}
		break;
	case 'S':
		if (m->y > 0) {
			/**
			 * within the board
			 */
			m->y--;
		} else if (m->y == 0) {
			/**
			 * in the edge
			 */
			if (grid[m->x][m->y] != SCENT) {
				/**
				 * lost
				 */
				grid[m->x][m->y] = SCENT;
				isLost = 1;
			}
		}
		break;
	case 'E':
		if (m->x < maxX) {
			/**
			 * within the board
			 */
			m->x++;
		} else if (m->x == maxX) {
			/**
			 * in the edge
			 */
			if (grid[m->x][m->y] != SCENT) {
				/**
				 * lost
				 */
				grid[m->x][m->y] = SCENT;
				isLost = 1;
			}
		}
		break;
	case 'W':
		if (m->x > 0) {
			/**
			 * within the board
			 */
			m->x--;
		} else if (m->x == 0) {
			/**
			 * in the edge
			 */
			if (grid[m->x][m->y] != SCENT) {
				/**
				 * lost
				 */
				grid[m->x][m->y] = SCENT;
				isLost = 1;
			}
		}
		break;
	}
	return isLost;
}

/**
 * if lost then return 1
 */
int run(struct Robot * m, char * inst) {
/*
	if (DEBUG) {
		print(m);
		printf("command:%s\n", inst);
	}
*/
	int i;
	char command;
	for (i = 0; i < strlen(inst); i++) {
		command = *(inst + i);
		switch (command) {
		case 'L':
			turnLeft(m);
			break;
		case 'R':
			turnRight(m);
			break;
		case 'F':
			if (moveForward(m)) {
				return 1;
			}
			break;
		}
		if (DEBUG) {
			print(m);
		}
	}
	return 0;
}

int main(int argc, char * argv[]) {
	int x, y;
	char o;
	char inst[100];
	struct Robot * me;
	scanf("%d %d\n", &maxX, &maxY);
	while (scanf("%d %d %c\n", &x, &y, &o) != EOF) {
		me = alloc(x, y, o);
		scanf("%s\n", inst);
		if (run(me, inst)) {
			printf("%d %d %c LOST\n", me->x, me->y, me->o);
		} else {
			printf("%d %d %c\n", me->x, me->y, me->o);
		}
	}
	return 0;
}

