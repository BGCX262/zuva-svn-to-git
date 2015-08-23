#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
/**
 * 0 - N
 * 1 - NE
 * 2 - E
 * 3 - SE
 * 4 - S
 * 5 - SW
 * 6 - W
 * 7 - NW
 */
char direction[10][3] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };
int dir_x[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dir_y[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int cx, cy, cdir;
char order[100];
int state1, state2;

void printPos() {
	printf("x:%d, y:%d, cdir:%s\n", cx, cy, direction[cdir]);
}

void GO(int k) {
	if (DEBUG) {
		printf("go %d\n", k);
	}
	int nextX = cx + k * dir_x[cdir];
	int nextY = cy + k * dir_y[cdir];
	if (k < 0 || nextX > 50 || nextY > 50 || nextX < -50 || nextY < -50)
		return;
	cx = nextX;
	cy = nextY;
	if (DEBUG) {
		printPos();
	}
}

int LEAVE_VALIDITY(int x, int y, int turn) {
	if (state1 == -1)
		return (turn == 6);
	else
		return (turn == 5);
}

int ARRIVE_VALIDITY(int x, int y, int turn) {
	if (state2 == -1)
		return (turn == 6);
	else
		return (turn == 5);
}

int DIR_VALIDITY(int x, int y, int dir) {
	if (x == 50 && y == 50)
		return (dir == 5 || dir == 6 || dir == 4);
	if (x == 50 && y == 0)
		return (dir == 7 || dir == 5 || dir == 0 || dir == 4 || dir == 6);
	if (x == 50 && y == -50)
		return (dir == 7 || dir == 0 || dir == 6);
	if (x == 0 && y == 50)
		return (dir == 3 || dir == 5 || dir == 2 || dir == 4 || dir == 6);
	if (x == 0 && y == -50)
		return (dir == 1 || dir == 7 || dir == 2 || dir == 0 || dir == 6);
	if (x == -50 && y == 50)
		return (dir == 3 || dir == 2 || dir == 4);
	if (x == -50 && y == 0)
		return (dir == 1 && dir == 3 || dir == 0 || dir == 2 || dir == 4);
	if (x == -50 && y == -50)
		return (dir == 1 || dir == 0 || dir == 2);

	if ((x - y == 0 || x - y == -50 || x - y == 50) && (dir == 1 || dir == 5))
		return 1;
	if ((x + y == 0 || x + y == 50 || x + y == -50) && (dir == 7 || dir == 3))
		return 1;

	if (y == 50 && (dir == 0 || dir == 1 || dir == 7))
		return 0;
	if (y == -50 && (dir == 3 || dir == 4 || dir == 5))
		return 0;
	if (x == -50 && (dir == 5 || dir == 6 || dir == 7))
		return 0;
	if (x == 50 && (dir == 1 || dir == 2 || dir == 3))
		return 0;

	if (dir == 0 || dir == 2 || dir == 4 || dir == 6)
		return 1;
	return 0;
}
/*
 * -1 means it's through way but not boulevard
 * -2 means it's through way and boulevard
 *  1 means it's not through way
 */
int THROUGHWAY(int x, int y, int dir) {
	if ((y == 50 || y == 0 || y == -50) && (dir == 2 || dir == 6))
		return -1;
	if ((x == 50 || x == 0 || x == -50) && (dir == 0 || dir == 4))
		return -1;
	if (x + y == 0 && (dir == 7 || dir == 3))
		return -2;
	if (x - y == 0 && (dir == 1 || dir == 5))
		return -2;
	return 1;
}

int CIRCLE(int x, int y) {
	if ((x == -50 || x == 0 || x == 50) && (y == -50 || y == 0 || y == 50))
		return 1;
	return 0;
}

void TURN(int k) {
	if (DEBUG) {
		printf("turn %d\n", k);
	}

	int xx;
	if (!DIR_VALIDITY(cx + dir_x[cdir], cy + dir_y[cdir], (cdir + k) % 8)) {
		if (DEBUG) {
			printPos();
			printf("dir validity is false\n");
		}
		return;
	}
	state1 = THROUGHWAY(cx + dir_x[cdir], cy + dir_y[cdir], cdir);
	state2 = THROUGHWAY(cx + dir_x[cdir], cy + dir_y[cdir], (cdir + k) % 8);

	if (state1 < 0 && state2 > 0)
		xx = LEAVE_VALIDITY(cx + dir_x[cdir], cy + dir_y[cdir], k);
	else if (state1 > 0 && state2 < 0)
		xx = ARRIVE_VALIDITY(cx + dir_x[cdir], cy + dir_y[cdir], k);
	else
		xx = 1;

	if (xx || CIRCLE(cx + dir_x[cdir], cy + dir_y[cdir])) {
		/*if (xx) {*/
		cx += dir_x[cdir];
		cy += dir_y[cdir];
		cdir = (cdir + k) % 8;
	}

	if (DEBUG) {
		printPos();
	}
}

void DECODE() {
	char msg1[100], msg2[100], msg3[100];
	int d, turn, type, r;

	sscanf(order, "%s", msg1);

	if (strcmp(msg1, "GO") == 0) {
		r = sscanf(order, "%s%s%s", msg1, msg2, msg3);
		if (r == 2 && msg2[0] >= '0' && msg2[0] <= '9')
			sscanf(order, "%s%d", msg1, &d);
		else {
			sscanf(order, "%s%s%d", msg1, msg2, &d);
			if (strcmp(msg2, "STRAIGHT") != 0)
				return;
		}
		GO(d);
	} else if (strcmp(msg1, "TURN") == 0) {
		 r = sscanf(order, "%s%s%s", msg1, msg2, msg3);
		if (DEBUG)
			printf("r = %d\n", r);
		if (r == 3 && (strcmp(msg2, "SHARP") == 0 && strcmp(msg3, "LEFT") == 0)) {
			turn = 5;
		} else if (r == 3 && (strcmp(msg2, "SHARP") == 0 && strcmp(msg3, "RIGHT") == 0)) {
			turn = 3;
		} else if (r == 3 && (strcmp(msg2, "HALF") == 0 && strcmp(msg3, "LEFT") == 0)) {
			turn = 7;
		} else if (r == 3 && (strcmp(msg2, "HALF") == 0 && strcmp(msg3, "RIGHT") == 0)) {
			turn = 1;
		} else if (r == 2 && strcmp(msg2, "LEFT") == 0) {
			turn = 6;
		} else if (r == 2 && strcmp(msg2, "RIGHT") == 0) {
			turn = 2;
		} else
			return;
		TURN(turn);
	}
}
void PRINT() {
	printf("A%d%c", cx * (cx < 0 ? -1 : 1), (cx < 0 ? 'W' : 'E'));
	printf(" S%d%c", cy * (cy < 0 ? -1 : 1), (cy < 0 ? 'S' : 'N'));
	printf(" %s\n", direction[cdir]);
}

void RESULT() {
	int OK = 1;
	OK = THROUGHWAY(cx, cy, cdir);
	if (OK > 0)
		PRINT();
	else
		printf("Illegal stopping place\n");
}

int getOrder() {
	char * r = fgets(order, 100, stdin);
	if (r != NULL) {
		if (order[strlen(order) - 1] == '\n')
			order[strlen(order) - 1] = '\0';
		return 1;
	}
	return 0;
}

int main() {
	char order1[100], order2[100], heading[3];
	char AOS, dir;
	int d, i, r;
	for (;;) {
		getOrder();
		if (DEBUG) {
			printf("order:%s\n", order);
		}
		if (strcmp(order, "END") == 0)
			break;

		r = sscanf(order, "%s%s%s", order1, order2, heading);
		if (r != 3)
			continue;
		r = sscanf(order1, "%c%d%c", &AOS, &d, &dir);
		if (r != 3)
			continue;
		if (AOS == 'A')
			cx = d * (dir == 'W' ? -1 : 1);
		else
			cy = d * (dir == 'S' ? -1 : 1);
		r = sscanf(order2, "%c%d%c", &AOS, &d, &dir);
		if (r != 3)
			continue;
		if (AOS == 'A')
			cx = d * (dir == 'W' ? -1 : 1);
		else
			cy = d * (dir == 'S' ? -1 : 1);
		for (i = 0; i < 8; i++)
			if (strcmp(heading, direction[i]) == 0)
				cdir = i;
		while (getOrder()) {
			if (DEBUG) {
				printf("order:%s\n", order);
			}
			if (strcmp(order, "STOP") == 0)
				break;
			DECODE();
		}
		RESULT();
	}
	return 0;
}
