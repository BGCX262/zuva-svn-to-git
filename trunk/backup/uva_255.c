#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * uva 255
 */

static int queenX, queenY, kingX, kingY, queenMoveX, queenMoveY, king, queen, queenMove;

int illegalState() {
	return king == queen;
}

int illeagalMove() {
	if ((queenMoveX != queenX && queenMoveY != queenY) || (queenMoveX == queenX && queenMoveY == queenY)) {
		return 1;
	}

	if (queenY == kingY && queenMoveX > queenX && kingX >= queenX && kingX <= queenMoveX) {
		return 1;
	}
	if (queenY == kingY && queenMoveX < queenX && kingX >= queenMoveX && kingX <= queenX) {
		return 1;
	}
	if (queenX == kingX && queenMoveY < queenY && kingY >= queenMoveY && kingY <= queenY) {
		return 1;
	}
	if (queenX == kingX && queenMoveY > queenY && kingY >= queenY && kingY <= queenMoveY) {
		return 1;
	}
	return 0;
}

int queenAllowed() {
	if (queenMoveX == kingX && (queenMoveY == kingY - 1 || queenMoveY == kingY + 1)) {
		return 0;
	}
	if (queenMoveY == kingY && (queenMoveX == kingX - 1 || queenMoveX == kingX + 1)) {
		return 0;
	}
	return 1;
}

int kingAllowed() {
	if (kingX == 0 && kingY == 0 && queenMoveX == 1 && queenMoveY == 1) {
		return 0;
	}

	if (kingX == 0 && kingY == 7 && queenMoveX == 1 && queenMoveY == 6) {
		return 0;
	}
	if (kingX == 7 && kingY == 7 && queenMoveX == 6 && queenMoveY == 6) {
		return 0;
	}
	if (kingX == 7 && kingY == 0 && queenMoveX == 6 && queenMoveY == 1) {
		return 0;
	}
	return 1;
}

int main() {
	int i;
	char line[256];
	for (; fgets(line, 256, stdin) != NULL;) {
		sscanf(line, "%d %d %d", &king, &queen, &queenMove);
		kingX = king / 8;
		kingY = king % 8;
		queenX = queen / 8;
		queenY = queen % 8;
		queenMoveX = queenMove / 8;
		queenMoveY = queenMove % 8;

		if (DEBUG) {
			printf("king %d -> [%d, %d]\n", king, kingX, kingY);
			printf("queen %d -> [%d, %d]\n", queen, queenX, queenY);
			printf("queen %d -> [%d, %d]\n", queenMove, queenMoveX, queenMoveY);
		}

		int st = illegalState();
		int im = illeagalMove();
		int qa = queenAllowed();
		int ka = kingAllowed();
		if (st) {
			printf("Illegal state\n");
		} else if (im) {
			printf("Illegal move\n");
		} else if (!qa) {
			printf("Move not allowed\n");
		} else if (ka) {
			printf("Continue\n");
		} else {
			printf("Stop\n");
		}
	}
	return 0;
}

