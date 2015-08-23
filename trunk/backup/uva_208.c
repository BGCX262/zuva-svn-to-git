#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * 208
 */

static int map[21][21], fire, visited[21], stack[21], stackSize, routeSize, reach[21];

void dfs(int curr) {
	if (DEBUG) {
		printf("dfs %d fire %d\n", curr, fire);
	}

	int i, j;
	if (curr == fire) {
		if (DEBUG) {
			printf("stackSize %d\n", stackSize);
		}

		for (i = 0; i < stackSize; i++) {
			printf("%d ", stack[i]);
		}
		printf("%d\n", curr);
		routeSize++;
		return;
	}
	stack[stackSize++] = curr;
	visited[curr] = 1;
	for (i = 1; i <= 20; i++) {
		if (i != curr && map[curr][i] == 1 && visited[i] == 0 && reach[i] == 1) {
			dfs(i);
		}
	}
	visited[curr] = 0;
	stackSize--;
	return;
}

void setReach(int curr) {
	if (DEBUG)
		printf("setReach %d\n", curr);
	reach[curr] = visited[curr] = 1;
	int i;
	for (i = 1; i <= 20; i++) {
		if (i != curr && map[curr][i] == 1 && visited[i] == 0) {
			setReach(i);
		}
	}
}

int main(int argc, char * argv[]) {
	int i, j, caseNum=1;
	char line[16];
	while (fgets(line, 16, stdin) != NULL) {
		stackSize = 0;
		routeSize = 0;
		sscanf(line, "%d", &fire);
		if (DEBUG) {
			printf("fire %d\n", fire);
		}
		for (i = 1; i <= 20; i++) {
			visited[i] = reach[i] = 0;
			for (j = 1; j <= 20; j++) {
				map[i][j] = 0;
			}
		}
		for (;;) {
			int from, to;
			scanf("%d %d\n", &from, &to);
			if (DEBUG) {
				printf("from %d to %d\n", from, to);
			}

			if (from == 0 && to == 0) {
				break;
			}
			map[from][to] = 1;
			map[to][from] = 1;
		}
		setReach(fire);
		for (i = 1; i <= 20; i++) {
			visited[i] = 0;
		}
		if (DEBUG) {
			for (i = 1; i <= 20; i++) {
				printf("reach[%d]%d\n", i, reach[i]);
			}
		}
		printf("CASE %d:\n", caseNum++);
		dfs(1);
		printf("There are %d routes from the firestation to streetcorner %d.\n", routeSize, fire);
	}

	return 0;
}

