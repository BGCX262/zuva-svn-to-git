#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define FLOOR_MAX 50000000
#define ELEVATOR_MAX 100

long step[ELEVATOR_MAX], initFloor[ELEVATOR_MAX], graph[ELEVATOR_MAX][ELEVATOR_MAX], maxFloor, fromFloor, toFloor, fifo[ELEVATOR_MAX], fifoStart, fifoEnd,
		elevator, visited[ELEVATOR_MAX];

void ex_gcd(long a, long b, long * d, long * x, long * y) {
	if (b == 0) {
		*x = 1, *y = 0, *d = a;
		return;
	}
	long x1, y1;
	ex_gcd(b, a % b, d, &x1, &y1);
	*x = y1;
	*y = x1 - (a / b) * y1;
}

int isConnectElevator(int i1, int i2) {
	long a, b, d, t, x, y;
	a = step[i1];
	b = 0 - step[i2];
	ex_gcd(a, b, &d, &x, &y);
	if ((initFloor[i2] - initFloor[i1]) % d != 0) {
		if (DEBUG) {
			printf("Elevator %d and %d a1 %d a2 %d return 0\n", i1, i2, step[i1], step[i2]);
		}
		return 0;
	}

	for (t = 0;; t++) {
		long x1 = x - step[i2] / d * t;
		long y1 = y - step[i1] / d * t;
		long f1 = initFloor[i1] + x1 * step[i1];
		if (x1 >= 0 && f1 < maxFloor && y1 >= 0) {
			return 1;
		}
		if (f1 >= maxFloor || f1 < 0)
			break;
	}

	if (DEBUG) {
		printf("Elevator %d and %d return 0\n", i1, i2);
	}
	return 0;
}

void add(int e) {
	if (fifoStart == fifoEnd && fifoEnd == -1) {
		fifoStart = fifoEnd = 0;
	} else {
		fifoEnd = (fifoEnd + 1) % ELEVATOR_MAX;
	}
	fifo[fifoEnd] = e;
}

int delete() {
	int re;
	if (fifoStart == fifoEnd && fifoStart != -1) {
		re = fifo[fifoStart];
		fifoStart = fifoEnd = -1;
	} else if (fifoStart == fifoEnd && fifoStart == -1) {
		re = -1;
	} else {
		re = fifo[fifoStart++];
	}
	return re;
}

int bfs(int fromElevator) {
	memset(visited, 0, sizeof(int) * ELEVATOR_MAX);
	fifoStart = fifoEnd = -1;
	add(fromElevator);
	int curr, j;
	while ((curr = delete()) != -1) {
		visited[curr] = 1;
		for (j = 0; j * step[curr] + initFloor[curr] < maxFloor; j++) {
			if (j * step[curr] + initFloor[curr] == toFloor) {
				return curr;
			}
		}
		for (j = 0; j < elevator; j++) {
			if (visited[j] == 0 && graph[curr][j]) {
				add(j);
			}
		}
	}
	return -1;
}

int main() {
	int numTest;

	for (scanf("%d", &numTest); numTest > 0; numTest--) {
		int i, j, fromElevator, toElevator;
		scanf("%d %d %d %d", &maxFloor, &elevator, &fromFloor, &toFloor);
		for (i = 0; i < elevator; i++) {
			scanf("%d %d", &step[i], &initFloor[i]);
		}

		memset(graph, 0, sizeof(int) * elevator * elevator);
		for (i = 0; i < elevator - 1; i++) {
			for (j = i + 1; j < elevator; j++) {
				if (isConnectElevator(i, j)) {
					graph[i][j] = 1;
					graph[j][i] = 1;
				}
			}
		}
		fromElevator = -1;
		for (i = 0; i < elevator; i++) {
			for (j = 0; j * step[i] + initFloor[i] < maxFloor; j++) {
				if (j * step[i] + initFloor[i] == fromFloor) {
					fromElevator = i;
					break;
				}
			}
			if (fromElevator != -1)
				break;
		}

		if (fromElevator == -1) {
			printf("The furniture cannot be moved.\n");
		} else {
			toElevator = bfs(fromElevator);
			if (toElevator == -1) {
				printf("The furniture cannot be moved.\n");
			} else {
				printf("It is possible to move the furniture.\n");
			}
		}
	}
	return 0;
}

