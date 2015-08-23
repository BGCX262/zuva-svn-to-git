#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int adj[128][128], n, visited[128], depth[128], low[128], cut[128];

void dfs(int curr, int parent, int dep) {
	if (DEBUG) {
		printf("dfs curr %d parent %d dep %d\n", curr, parent, dep);

		if (DEBUG) {
			printf("low: ");
			int i;
			for (i = 1; i <= n; i++) {
				printf("%d ", low[i]);
			}
			printf("\n");
		}

	}

	int i, j;
	visited[curr] = 1;
	depth[curr] = low[curr]=dep;
	int totalSub = 0;
	for (i = 1; i <= n; i++) {
		if (adj[curr][i] != 0 && i != parent) {
			if (visited[i] == 1) {
				low[curr] = depth[i] < low[curr] ? depth[i] : low[curr];
			} else if (visited[i] == 0) {
				dfs(i, curr, dep + 1);
				totalSub++;
				low[curr] = low[i] < low[curr] ? low[i] : low[curr];
				if ((curr == 1 && totalSub > 1) || (curr > 1 && low[i] >= depth[curr])) {
					cut[curr] = 1;
				}
			}
		}
	}

	visited[curr] = 2;
}

/**
 * 315
 */
int main(int argc, char * argv[]) {
	char data[1005];
	int places[128];
	int placesSize = 0;
	int place = 0;

	int i, j, len;
	while (1) {
		gets(data);
		len = strlen(data);
		place = 0;
		for (i = 0; i < len; i++) {
			if (data[i] >= '0' && data[i] <= '9') {
				place = (data[i] - '0') + place * 10;
			}
		}
		if (DEBUG)
			printf("n %d\n", place);

		if (place == 0)
			break;

		n = place;

		memset(adj, 0, 128 * 128 * sizeof(int));
		memset(visited, 0, 128 * sizeof(int));
		memset(depth, 0, 128 * sizeof(int));
		memset(low, 0, 128 * sizeof(int));
		memset(cut, 0, 128 * sizeof(int));

		while (1) {
			gets(data);
			len = strlen(data);
			placesSize = 0;
			place = -1;
			for (i = 0; i < len; i++) {
				if (data[i] == ' ') {
					places[placesSize++] = place;
					place = 0;
				}
				if (data[i] >= '0' && data[i] <= '9') {
					if (place == -1)
						place = 0;
					place = (data[i] - '0') + place * 10;
				}
			}
			if (place != -1) {
				places[placesSize++] = place;
			}
			if (placesSize == 1 && places[0] == 0)
				break;

			for (i = 1; i < placesSize; i++) {
				adj[places[0]][places[i]] = adj[places[i]][places[0]] = 1;
			}
		}
		dfs(1, 0, 0);
		int nCut = 0;
		for (i = 1; i <= n; i++) {
			if (cut[i]) {
				nCut++;
			}
		}
		printf("%d\n", nCut);
	}

	return 0;
}
