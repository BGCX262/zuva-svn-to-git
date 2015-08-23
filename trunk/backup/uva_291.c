#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct NODE {
	int num;
	int nei[6];
} Node;

Node * new(int w) {
	Node * p = malloc(sizeof(Node));
	p->num = w;
	memset(p->nei, 0, 6 * sizeof(int));
	return p;
}

void dfs(Node * nodes[], int n, int path[], int pathSize) {
	if (DEBUG) {
		printf("n %d pathSize %d", n, pathSize);
		printf(" path ");
		int i;
		for (i = 0; i < pathSize; i++) {
			printf("%d ", path[i]);
		}
		printf("\n");
	}

	if (pathSize == 9) {
		int i;
		for (i = 0; i < 9; i++) {
			printf("%d", path[i]);
		}
		printf("\n");
		return;
	}
	Node * curr = nodes[n];
	int i;
	for (i = 1; i <= 5; i++) {
		if (curr->nei[i] == 1) {
			path[pathSize++] = i;
			curr->nei[i] = 0;
			nodes[i]->nei[n] = 0;
			dfs(nodes, i, path, pathSize);
			curr->nei[i] = 1;
			nodes[i]->nei[n] = 1;
			pathSize--;
		}
	}
}

/**
 * 291
 */
int main(int argc, char * argv[]) {
	int path[8], i;
	memset(path, 0, 8 * sizeof(int));
	Node * nodes[6];
	Node * n = new(1);
	n->nei[2] = 1;
	n->nei[3] = 1;
	n->nei[5] = 1;
	nodes[1] = n;
	n = new(2);
	n->nei[1] = 1;
	n->nei[3] = 1;
	n->nei[5] = 1;
	nodes[2] = n;
	n = new(3);
	n->nei[1] = 1;
	n->nei[2] = 1;
	n->nei[4] = 1;
	n->nei[5] = 1;
	nodes[3] = n;
	n = new(4);
	n->nei[3] = 1;
	n->nei[5] = 1;
	nodes[4] = n;
	n = new(5);
	n->nei[1] = 1;
	n->nei[2] = 1;
	n->nei[3] = 1;
	n->nei[4] = 1;
	nodes[5] = n;
	path[0] = 1;
	dfs(nodes, 1, path, 1);
	return 0;
}
