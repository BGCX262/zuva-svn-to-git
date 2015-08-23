#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 101

#define NUL -1

/**
 * 1000
 */
int main(int argc, char * argv[]) {
	int i, j, testCase = 1, k, path[NODE_MAX][NODE_MAX], numNode, start, maxPath, end;

	for (;;) {
		scanf("%d", &numNode);
		if (numNode == 0)
			break;

		scanf("%d", &start);
		for (i = 1; i <= numNode; i++) {
			for (j = 1; j <= numNode; j++) {
				path[i][j] = NUL;
			}
		}
		for (;;) {
			int from, to;
			scanf("%d %d", &from, &to);
			if (from == 0 && to == 0)
				break;
			path[from][to] = 1;
		}
		for (k = 1; k <= numNode; k++) {
			for (i = 1; i <= numNode; i++) {
				for (j = 1; j <= numNode; j++) {
					if (path[i][k] != NUL && path[k][j] != NUL) {
						if (path[i][k] + path[k][j] > path[i][j]) {
							path[i][j] = path[i][k] + path[k][j];
						}
					}
				}
			}
		}
		end = start;
		maxPath = 0;
		for (i = 1; i <= numNode; i++) {
			if (i == start)
				continue;

			if (path[start][i] != NUL) {
				if (path[start][i] > maxPath) {
					end = i;
					maxPath = path[start][i];
				} else if (path[start][i] == maxPath && i < end) {
					end = i;
				}
			}
		}
		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n", testCase++, start, maxPath, end);
	}
	return 0;
}
