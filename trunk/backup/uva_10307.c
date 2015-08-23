#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

#define BOARD_MAX 51
#define NODE_MAX 2500
#define EDGE_MAX 100000
#define ALIAN_MAX 101

enum TYPE {
	ALIAN, BLANK, WALL
};

typedef struct Edge {
	int index1, index2, dis;
} EDGE;

typedef struct Node {
	int row, col, index, visited, dis;
	enum TYPE type;
} NODE;

NODE * newNode(int r, int c, enum TYPE t) {
	NODE * pNode = malloc(sizeof(NODE));
	pNode->row = r;
	pNode->col = c;
	pNode->type = t;
	pNode->dis = 0;
	return pNode;
}

static NODE * alians[ALIAN_MAX], *queue[NODE_MAX], *board[BOARD_MAX][BOARD_MAX];
static EDGE edges[EDGE_MAX];
static int edgesSize, aliansSize, left, distance[ALIAN_MAX][ALIAN_MAX], right, root[ALIAN_MAX], step[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

int cmp(const void *a, const void *b) {
	return ((EDGE *) a)->dis - ((EDGE *) b)->dis;
}

void add(NODE * node) {
	if (left == -1 && right == -1) {
		left = 0;
		right = 0;
		queue[0] = node;
	} else {
		right = (right + 1) % NODE_MAX;
		queue[right] = node;
	}
}

struct Node * delete() {
	NODE * node = NULL;
	if (left == right && left != -1) {
		node = queue[left];
		left = right = -1;
	} else if (left != right) {
		node = queue[left];
		left = (left + 1) % NODE_MAX;
	}
	return node;
}

void bfs(NODE * source) {
	int i, j;
	left = right = -1;
	add(source);
	struct Node * curr = NULL;
	while ((curr = delete()) != NULL) {
		curr->visited = 1;
		if (curr->type == ALIAN && curr != source) {
			distance[source->index][curr->index] = curr->dis;
			continue;
		}
		for (j = 0; j < 4; ++j) {
			NODE * next = board[curr->row + step[j][0]][curr->col + step[j][1]];
			if (!next->visited && (next->type == ALIAN || next->type == BLANK)) {
				next->dis = curr->dis + 1;
				add(next);
			}
		}
	}
}

void initVisited() {
	int i, j;
	for (i = 0; i < BOARD_MAX; i++) {
		for (j = 0; j < BOARD_MAX; j++) {
			board[i][j]->visited = 0;
			board[i][j]->dis = 0;
		}
	}
}

int find(int n) {
	if (root[n] != n) {
		root[n] = find(root[n]);
	}
	return root[n];
}

/**
 * 10307
 */
int main(int argc, char * argv[]) {
	int test;

	scanf("%d", &test);
	while (test-- > 0) {
		int row, col, i, j;
		scanf("%d %d\n", &col, &row);
		for (i = 0; i < BOARD_MAX; i++) {
			for (j = 0; j < BOARD_MAX; j++) {
				board[i][j] = newNode(i, j, WALL);
			}
		}

		char line[256];
		for (i = 0; i < row; i++) {
			fgets(line, 256, stdin);
			int colIndex = 0;
			for (j = 0; j < strlen(line); j++) {
				if (line[j] == 'S' || line[j] == 'A') {
					board[i][j]->type = ALIAN;
					board[i][j]->index = aliansSize;
					alians[aliansSize++] = board[i][j];
				} else if (line[j] == ' ') {
					board[i][j]->type = BLANK;
				}
			}
		}

		for (i = 0; i < aliansSize; i++) {
			for (j = 0; j < aliansSize; j++) {
				distance[i][j] = 0;
			}
		}
		for (i = 0; i < aliansSize; i++) {
			initVisited();
			bfs(alians[i]);
		}

		edgesSize = 0;
		for (i = 0; i < aliansSize - 1; i++) {
			for (j = i + 1; j < aliansSize; j++) {
				if (distance[i][j] > 0) {
					edges[edgesSize].index1 = i;
					edges[edgesSize].index2 = j;
					edges[edgesSize].dis = distance[i][j];
					edgesSize++;
				}
			}
		}
		qsort(edges, edgesSize, sizeof(EDGE), cmp);
		for (i = 0; i < aliansSize; i++) {
			root[i] = i;
		}
		int mst = 0;
		for (i = 0; i < edgesSize; i++) {
			int r1 = find(edges[i].index1);
			int r2 = find(edges[i].index2);
			if (r1 != r2) {
				mst += edges[i].dis;
				root[r1] = r2;
			}
		}
		printf("%d\n", mst);
	}

	return 0;
}
