#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0

struct Node {
	int cost;
	int row;
	int prev;
};
/**
 * path matrix
 */
static struct Node * pmat[11][101];
/**
 * weight matrix
 */
static int wmat[11][101];
static int m, n;
static int minPath[101];
void printfMatrix() {
	int i, j;
	printf("weight matrix\n");
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			printf("%2d  ", wmat[i][j]);
		}
		printf("\n");
	}
	printf("path matrix\n");
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			printf("[%2d %2d %2d] ", pmat[i][j]->cost, pmat[i][j]->row,
					pmat[i][j]->prev);
		}
		printf("\n");
	}
}

struct Node * newNode(int cost, int row) {
	struct Node * p = malloc(sizeof(struct Node));
	p->cost = cost;
	p->row = row;
	p->prev = 0;
	return p;
}

struct Node * min(struct Node * a, struct Node * b, struct Node * c) {
	struct Node * min = a;
	if (b->cost < min->cost) {
		min = b;
	} else if (b->cost == min->cost && b->row < min->row) {
		min = b;
	}
	if (c->cost < min->cost) {
		min = c;
	} else if (c->cost == min->cost && c->row < min->row) {
		min = c;
	}
	return min;
}
void calMinPath() {
	int i, j, i1, i2, i3;
	struct Node * prevMin;
	for (i = 1; i <= m; i++) {
		pmat[i][n] = newNode(wmat[i][n], i);
	}

	for (j = n - 1; j >= 1; j--) {
		for (i = 1; i <= m; i++) {
			i1 = i - 1;
			i2 = i;
			i3 = i + 1;
			if (i1 == 0) {
				i1 = m;
			}
			if (i3 == m + 1) {
				i3 = 1;
			}
			prevMin = min(pmat[i1][(j + 1)], pmat[i2][j + 1], pmat[i3][j + 1]);
			pmat[i][j] = newNode(prevMin->cost + wmat[i][j], i);
			pmat[i][j]->prev = prevMin->row;
		}
	}
}

void setMinPath(int * minValue) {
	int i, j;
	(*minValue) = pmat[1][1]->cost;
	int minRow = 1;

	for (i = 2; i <= m; i++) {
		if (pmat[i][1]->cost < (*minValue)) {
			(*minValue) = pmat[i][1]->cost;
			minRow = i;
		}
	}
	j = 1;
	while (pmat[minRow][j]->prev != 0) {
		minPath[j] = minRow;
		minRow = pmat[minRow][j]->prev;
		j++;
	}
	minPath[j] = minRow;
}

int main(int argc, char * argv[]) {
	int i, j, minValue, minRow;
	while (scanf("%d %d\n", &m, &n) != EOF) {
		for (i = 1; i <= m; i++) {
			for (j = 1; j <= n; j++) {
				scanf("%d ", &wmat[i][j]);
			}
		}
		calMinPath();
		if (DEBUG) {
			printfMatrix();
		}
		setMinPath(&minValue);
		for (j = 1; j <= n; j++) {
			printf("%d", minPath[j]);
			if (j < n)
				printf(" ");
		}
		printf("\n%d\n", minValue);
	}
	return 0;
}
