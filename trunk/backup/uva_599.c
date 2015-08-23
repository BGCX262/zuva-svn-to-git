#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define invalid -2
#define isolated -1

/**
 * uva 599
 */

struct Node {
	int name;
	int adj[26];
	int adjSize;
	int graph;
};

static struct Node all[26];

void initAll() {
	int i;
	for (i = 0; i < 26; i++) {
		all[i].name = i;
		all[i].adjSize = 0;
		all[i].graph = invalid;
	}
}

void dfs(int curr, int graphNum) {
	all[curr].graph = graphNum;
	int i;
	for (i = 0; i < all[curr].adjSize; i++) {
		if (all[all[curr].adj[i]].graph == isolated) {
			dfs(all[curr].adj[i], graphNum);
		}
	}
}

int isIsolated(int curr) {
	int i;
	for (i = 0; i < all[curr].adjSize; i++) {
		if (all[all[curr].adj[i]].graph == all[curr].graph) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int t, re, len, n, beginNode = 0;
	char line[128];
	gets(line);
	sscanf(line, "%d", &n);

	initAll();

	for (t = 0; t < n; t++) {
		while (fgets(line, 128, stdin) != NULL) {
			if (beginNode) {
				int i;
				for (i = 0; i < strlen(line); i++) {
					if (line[i] >= 'A' && line[i] <= 'Z') {
						all[line[i] - 'A'].graph = isolated;
					}
				}
				if (DEBUG) {
					for (i = 0; i < 26; i++) {
						printf("node:%d graph:%d adjSize:%d\n", all[i].name, all[i].graph, all[i].adjSize);
					}
				}

				int graphNum = 0;
				for (i = 0; i < 26; i++) {
					if (all[i].graph == isolated) {
						dfs(i, graphNum++);
					}
				}
				int isolatedNum = 0;
				for (i = 0; i < 26; i++) {
					if (all[i].graph != invalid && isIsolated(i)) {
						isolatedNum++;
					}
				}
				printf("There are %d tree(s) and %d acorn(s).\n", graphNum - isolatedNum, isolatedNum);

				initAll();
				beginNode = 0;
			} else if (line[0] == '*') {
				beginNode = 1;
			} else {
				char c1, c2;
				sscanf(line, "(%c,%c)", &c1, &c2);
				int a = c1 - 'A';
				int b = c2 - 'A';
				all[a].adj[all[a].adjSize++] = b;
				all[b].adj[all[b].adjSize++] = a;
			}
		}
	}

	return 0;
}

