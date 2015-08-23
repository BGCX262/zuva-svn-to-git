#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * uva 540
 */

#define MAX

static int head, tail, team[1000000], queue[200001];

void enqueue(int c) {
	if (head == tail && head == -1) {
		head = tail = 0;
	} else {
		tail++;
	}
	queue[tail] = c;
}

int dequeue() {
	int r = queue[head];
	if (head == tail) {
		head = tail = -1;
	} else {
		head++;
	}
	return r;
}

int empty() {
	if (head == tail && head == -1) {
		return 1;
	}
	return 0;
}

void insert(int i, int m) {
	int j = tail + 1;
	while (j > i + 1) {
		queue[j] = queue[j - 1];
		j--;
	}
	queue[i + 1] = m;
	tail++;
}

int main() {
	int i, j, t, m, tSize, scenario = 0;
	for (; scanf("%d", &t) && t != 0;) {
		scenario++;
		printf("Scenario #%d\n", scenario);
		head = tail = -1;
		for (i = 0; i < 1000000; i++) {
			team[i] = -1;
		}

		for (i = 0; i < t; i++) {
			scanf("%d", &tSize);
			for (j = 0; j < tSize; j++) {
				scanf("%d", &m);
				team[m] = i;
			}
		}

		char line[128], cmd[128];
		int d;
		gets(line);
		while (gets(line) != NULL) {
			if (line[0] == 'E') {
				sscanf(line, "%s %d", cmd, &d);
				if (DEBUG) {
					printf("enqueue;%d\n", d);
				}
				int in = 0;
				for (i = tail; i >= head; i--) {
					if (team[queue[i]] == team[d]) {
						insert(i, d);
						in = 1;
						break;
					}
				}
				if (in == 0) {
					enqueue(d);
				}
			} else if (line[0] == 'D') {
				if (DEBUG) {
					printf("dequeue\n");
				}
				printf("%d\n", dequeue());
			} else {
				if (DEBUG) {
					printf("STOP\n");
					for (i = 0; i < 1000000; i++) {
						if (team[i] != -1) {
							printf("team %d has %d\n", team[i], i);
						}
					}
				}
				break;
			}
		}
		printf("\n");

	}
	return 0;
}

