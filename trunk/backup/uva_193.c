#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/*typedef struct NODE {
 int black, visited, num;
 struct NODE * nei[128];
 int neiSize;
 } Node;

 Node * new(int num) {
 Node * p = malloc(sizeof(Node));
 p->num = num;
 p->neiSize = 0;
 p->visited = 0;
 return p;
 }*/
enum COLOR {
	BLACK, WHITE
};

static int maxBlack[128], maxBlackSize, graph[128][128], n;
static enum COLOR color[128];

void dfs(int curr, int currWhiteSize) {
	if (curr == n) {
		if (n - currWhiteSize > maxBlackSize) {
			maxBlackSize = n - currWhiteSize;
			int i, j = 0;
			for (i = 0; i < n; i++) {
				if (color[i] == BLACK) {
					maxBlack[j++] = i;
				}
			}
		}
		return;
	}

	int ok = 1;
	int i;
	for (i = 0; i < n; i++) {
		if (graph[curr][i] && color[i] == BLACK) {
			ok = 0;
			break;
		}
	}

	if (ok) {
		color[curr] = BLACK;
		dfs(curr + 1, currWhiteSize);
	}
	color[curr] = WHITE;
	dfs(curr + 1, currWhiteSize + 1);

}

/**
 * 11235
 */
int main(int argc, char * argv[]) {
	int i, m, k, n1, n2, j;

	for (scanf("%d", &m); m > 0; m--) {
		scanf("%d %d", &n, &k);
		memset(graph, 0, sizeof(int) * 128 * 128);
		memset(color, WHITE, sizeof(WHITE) * 128);
		for (i = 0; i < k; i++) {
			scanf("%d %d", &n1, &n2);
			n1--;
			n2--;
			graph[n1][n2] = 1;
			graph[n2][n1] = 1;
		}

		if (DEBUG) {
			printf("graph \n");
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					printf("%d ", graph[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}
		maxBlackSize = 0;
		dfs(0, 0);

		printf("%d\n", maxBlackSize);
		for (i = 0; i < maxBlackSize - 1; i++) {
			printf("%d ", maxBlack[i] + 1);
		}
		printf("%d\n", maxBlack[maxBlackSize - 1] + 1);
	}
	return 0;
}
