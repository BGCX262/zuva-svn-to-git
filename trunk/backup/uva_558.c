#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 1

struct edge {
	int x, y, len;
}typedef EDGE;

EDGE edges[2005];
int edgesSize, n;
int weight[1005];

int main() {
	int i, j, t, x = 0;
	scanf("%d", &x);
	while (x-- > 0) {
		scanf("%d %d", &n, &edgesSize);

		for (i = 0; i < edgesSize; i++) {
			scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].len);
		}

		for (i = 0; i < n; i++) {
			if (i == 0) {
				weight[i] = 0;
			} else {
				weight[i] = 2000000;
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < edgesSize; j++) {
				if (weight[edges[j].x] + edges[j].len < weight[edges[j].y]) {
					weight[edges[j].y] = weight[edges[j].x] + edges[j].len;
				}
			}
		}
		int hasNegativeCycle = 0;
		for (i = 0; i < edgesSize; i++) {
			if (weight[edges[i].x] + edges[i].len < weight[edges[i].y]) {
				hasNegativeCycle = 1;
				break;
			}
		}
		if (hasNegativeCycle) {
			printf("possible\n");
		} else {
			printf("not possible\n");
		}
	}

	return 0;
}
