#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define bSize 1025

struct Rat {
	int x, y, pop;
};

static struct Rat* rats[20000];
static int ratsSize, d, maxX, maxY, maxDead;
static int dead[bSize][bSize];

struct Rat * newRat(int x, int y, int pop) {
	struct Rat * p = malloc(sizeof(struct Rat));
	p->x = x;
	p->y = y;
	p->pop = pop;
	return p;
}

void findMaxDead(struct Rat * rat) {
	int upX = rat->x - d > 0 ? rat->x - d : 0;
	int downX = rat->x + d < bSize - 1 ? rat->x + d : bSize - 1;
	int rightY = rat->y + d < bSize - 1 ? rat->y + d : bSize - 1;
	int leftY = rat->y - d > 0 ? rat->y - d : 0;
	int i, j;
	for (i = upX; i <= downX; i++) {
		for (j = leftY; j <= rightY; j++) {
			dead[i][j] += rat->pop;
			if (dead[i][j] > maxDead) {
				maxX = i;
				maxY = j;
				maxDead = dead[i][j];
			}
		}
	}
}

int main(int argc, char * argv[]) {
	int m, i, index, j, size, n, x, y, p;
	scanf("%d\n", &m);
	for (index = 0; index < m; index++) {
		scanf("%d\n", &d);
		scanf("%d\n", &n);
		memset(dead, 0, sizeof(int) * bSize * bSize);
		for (j = 0; j < n; j++) {
			scanf("%d %d %d\n", &x, &y, &p);
			rats[ratsSize++] = newRat(x, y, p);
		}
		maxDead = 0;
		for (i = 0; i < ratsSize; i++) {
			struct Rat * rat = rats[i];
			findMaxDead(rat);
		}
		printf("%d %d %d\n", maxX, maxY, maxDead);

		for (i = 0; i < ratsSize; i++) {
			free(rats[i]);
		}
		ratsSize = 0;
	}
	return 0;
}
