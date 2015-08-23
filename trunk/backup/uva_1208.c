#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

#define max(a,b) (a>b)?a:b

struct Edge {
	int cost, a, b;
}typedef EDGE;

int connection[26], edgesSize, vertexSize;
EDGE edges[400];

int findRoot(int n1) {
	if (connection[n1] == n1)
		return n1;

	connection[n1] = findRoot(connection[n1]);
	return connection[n1];
}

int compare(const void * a, const void * b) {
	if (((EDGE *) a)->cost != ((EDGE *) b)->cost)
		return ((EDGE *) a)->cost - ((EDGE *) b)->cost;
	else
		return ((EDGE *) a)->a - ((EDGE *) b)->a;
}

int main() {
	int i, j, caseSize, t, x;
	scanf("%d", &caseSize);
	for (x = 0; x < caseSize; x++) {
		scanf("%d", &vertexSize);
		for (i = 0; i < vertexSize; i++) {
			connection[i] = i;
		}
		edgesSize = 0;
		for (i = 0; i < vertexSize; i++) {
			for (j = 0; j < vertexSize - 1; j++) {
				scanf("%d,", &t);
				if (t != 0) {
					edges[edgesSize].cost = t;
					edges[edgesSize].a = i;
					edges[edgesSize].b = j;
					edgesSize++;
				}
			}
			scanf("%d", &t);
			if (t != 0) {
				edges[edgesSize].cost = t;
				edges[edgesSize].a = i;
				edges[edgesSize].b = j;
				edgesSize++;
			}
		}
		if (DEBUG) {
			printf("edges:\n");
			for (i = 0; i < edgesSize; i++) {
				printf("%d %d cost %d\n", edges[i].a, edges[i].b, edges[i].cost);
			}
		}
		qsort(edges, edgesSize, sizeof(EDGE), compare);
		if (DEBUG) {
			printf("edges:\n");
			for (i = 0; i < edgesSize; i++) {
				printf("%d %d cost %d\n", edges[i].a, edges[i].b, edges[i].cost);
			}
		}
		printf("Case %d:\n", x + 1);
		for (i = 0; i < edgesSize; i++) {
			int aRoot = findRoot(edges[i].a);
			int bRoot = findRoot(edges[i].b);
			if (aRoot != bRoot) {
				connection[bRoot] = aRoot;
				printf("%c-%c %d\n", 'A' + edges[i].a, 'A' + edges[i].b, edges[i].cost);
			}
		}
	}
	return 0;
}
