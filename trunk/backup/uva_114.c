#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0

struct Obstacle {
	int value;
	int cost;
};

struct Ball {
	int x;
	int y;
	int direction;
	int lifetime;
};

struct Obstacle * newObstacle(int value, int cost) {
	struct Obstacle * p = malloc(sizeof(struct Obstacle));
	p->value = value;
	p->cost = cost;
	return p;
}

struct Ball * newBall(int x, int y, int direction, int lifetime) {
	struct Ball * p = malloc(sizeof(struct Ball));
	p->x = x;
	p->y = y;
	p->direction = direction;
	p->lifetime = lifetime;
	return p;
}

void printBoard(struct Obstacle * board[51][51], int m, int n, struct Ball * ball) {
	int i, j;
	printf("=============================================\n");
	for (j = n; j >= 1; j--) {
		for (i = 1; i <= m; i++) {
			if (ball->x == i && ball->y == j) {
				printf("B(%2d,%2d)", ball->direction, ball->lifetime);
			} else {
				if (board[i][j] == NULL) {
					printf("        ");
				} else {
					printf("(%2d,%2d) ", board[i][j]->value, board[i][j]->cost);
				}
			}
		}
		printf("\n");
	}
}

int runBall(struct Obstacle * surface[51][51], int m, int n, struct Ball * ball) {
	int i, j, points = 0, nextX, nextY;
	if (DEBUG) {
		printBoard(surface, m, n, ball);
	}
	while (ball->lifetime > 0) {
		ball->lifetime--;
		if (ball->direction == 0) {
			/**
			 * right
			 */
			nextX = ball->x + 1;
			nextY = ball->y;
		} else if (ball->direction == 1) {
			/**
			 * up
			 */
			nextX = ball->x;
			nextY = ball->y + 1;
		} else if (ball->direction == 2) {
			/**
			 * left
			 */
			nextX = ball->x - 1;
			nextY = ball->y;
		} else if (ball->direction == 3) {
			/**
			 * down
			 */
			nextX = ball->x;
			nextY = ball->y - 1;
		}

		if (surface[nextX][nextY] != NULL) {
			/**
			 * hit wall or bumper
			 */
			if (ball->lifetime > 0) {
				ball->lifetime -= surface[nextX][nextY]->cost;
				/**
				 * still live and get points
				 */
				points += surface[nextX][nextY]->value;
				/**
				 * turn right 90 degree
				 */
				ball->direction = (ball->direction + 3) % 4;
			}
		} else {
			/**
			 * hit nothing
			 */
			ball->x = nextX;
			ball->y = nextY;
		}
		if (DEBUG) {
			printBoard(surface, m, n, ball);
		}
	}
	return points;
}

int main(int argc, char * argv[]) {
	int i, j, m, n, wall_cost, num_bumper, x, y, value, cost, direction, lifetime, sum = 0;
	if (DEBUG)
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	scanf("%d %d\n", &m, &n);
	struct Obstacle * surface[51][51];
	scanf("%d\n", &wall_cost);
	/**
	 * initiate surface
	 */
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (i == 1 || i == m || j == 1 || j == n) {
				surface[i][j] = newObstacle(0, wall_cost);
			} else {
				surface[i][j] = NULL;
			}
		}
	}
	scanf("%d\n", &num_bumper);
	for (i = 0; i < num_bumper; i++) {
		scanf("%d %d %d %d\n", &x, &y, &value, &cost);
		surface[x][y] = newObstacle(value, cost);
	}
	while (scanf("%d %d %d %d\n", &x, &y, &direction, &lifetime) != EOF) {
		struct Ball *ball = newBall(x, y, direction, lifetime);
		int points = runBall(surface, m, n, ball);
		printf("%d\n", points);
		sum += points;
	}
	printf("%d\n", sum);
	return 0;
}

