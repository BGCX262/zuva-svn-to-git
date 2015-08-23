#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct EDGE {
	int cost;
	int n1, n2;
} Edge;

int compare(const void * a, const void * b) {
	return ((*(Edge **) a)->cost - (*(Edge **) b)->cost);
}

Edge * new(int w, int n1, int n2) {
	Edge * p = malloc(sizeof(Edge));
	p->cost = w;
	p->n1 = n1;
	p->n2 = n2;
	return p;
}

Edge * edges[1000000];
int edgesSize;
int connection[1000000];
int n;

int findRoot(int n1) {
	if (connection[n1] == n1)
		return n1;

	connection[n1] = findRoot(connection[n1]);
	return connection[n1];
}

/**
 * 908 Kruskal's algorithm to find minimum spanning tree MST
 */

int main(int argc, char * argv[]) {
	int n1, n2, i, j, c, k, m, test = 0;
	while (scanf("%d", &n) != EOF) {
		test++;
		int oldCost = 0;
		edgesSize = 0;
		for (i = 0; i < n - 1; i++) {
			scanf("%d %d %d", &n1, &n2, &c);
			oldCost += c;
		}
		scanf("%d\n", &k);
		for (i = 0; i < k; i++) {
			scanf("%d %d %d", &n1, &n2, &c);
			edges[edgesSize++] = new(c, n1, n2);
		}
		scanf("%d", &m);
		for (i = 0; i < m; i++) {
			scanf("%d %d %d", &n1, &n2, &c);
			edges[edgesSize++] = new(c, n1, n2);
		}
		for (i = 1; i <= n; i++) {
			connection[i] = i;
		}
		if (DEBUG) {
			int index;
			printf("edges before ====================================\n");
			for (index = 0; index < edgesSize; index++) {
				printf("n1 %d n2 %d cost %d\n", edges[index]->n1, edges[index]->n2, edges[index]->cost);
			}
		}

		qsort(edges, edgesSize, sizeof(Edge*), compare);

		if (DEBUG) {
			int index;
			printf("edges after ====================================\n");
			for (index = 0; index < edgesSize; index++) {
				printf("n1 %d n2 %d cost %d\n", edges[index]->n1, edges[index]->n2, edges[index]->cost);
			}
		}

		int newCost = 0;
		for (i = 0; i < edgesSize; i++) {
			Edge * d = edges[i];
			int r1 = findRoot(d->n1);
			int r2 = findRoot(d->n2);
			if (r1 == r2)
				continue;
			connection[r2] = r1;
			newCost += d->cost;
		}
		if (test > 1) {
			printf("\n");
		}
		printf("%d\n", oldCost);
		printf("%d\n", newCost);
	}

	return 0;
}
