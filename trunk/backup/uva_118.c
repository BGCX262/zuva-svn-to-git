#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 1
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
	if (DEBUG) {
		printf("left\n");
	}
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
	if (DEBUG) {
		printf("right\n");
	}
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
	if (DEBUG) {
		printf("forward\n");
	}
	switch (m->o) {
	case 'N':
		isScent()
		m->y++;
		break;
	case 'S':
		isScent()
		m->y--;
		break;
	case 'E':
		isScent()
		m->x++;
		break;
	case 'W':
		isScent()
		m->x--;
		break;
	}
	if (m->x > maxX) {
		isLost = 1;
		grid[m->x-1][y] = SCENT;
	}

	return isLost;
}

/**
 * if lost then return 1
 */
int run(struct Robot * m, char * inst) {
	if (DEBUG) {
		print(m);
		printf("command:%s\n", inst);
	}
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
			moveForward(m);
			break;
		}
		if (DEBUG) {
			print(m);
		}
	}
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
		run(me, inst);
	}
	return 0;
}

