#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

enum Color {
	BLACK, WHITE
};

typedef struct NODE {
	int row, column, adjSize, visited;
	enum Color color;
	struct NODE * adj[256];

} Node;

static Node * board[256][256];
static int n;
static enum Color win;

Node * new(int r, int c, enum Color cl) {
	Node * p = malloc(sizeof(Node));
	p->row = r;
	p->column = c;
	p->color = cl;
	p->adjSize = 0;
	p->visited = 0;
	return p;
}

void makeConnection(int i, int j) {
	if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1]->color == board[i][j]->color) {
		board[i][j]->adj[board[i][j]->adjSize++] = board[i - 1][j - 1];
	}
	if (i - 1 >= 0 && board[i - 1][j]->color == board[i][j]->color) {
		board[i][j]->adj[board[i][j]->adjSize++] = board[i - 1][j];
	}
	if (j - 1 >= 0 && board[i][j - 1]->color == board[i][j]->color) {
		board[i][j]->adj[board[i][j]->adjSize++] = board[i][j - 1];
	}

	if (j + 1 < n && board[i][j + 1]->color == board[i][j]->color) {
		board[i][j]->adj[board[i][j]->adjSize++] = board[i][j + 1];
	}
	if (i + 1 < n && board[i + 1][j]->color == board[i][j]->color) {
		board[i][j]->adj[board[i][j]->adjSize++] = board[i + 1][j];
	}

	if (i + 1 < n && j + 1 < n && board[i + 1][j + 1]->color == board[i][j]->color) {
		board[i][j]->adj[board[i][j]->adjSize++] = board[i + 1][j + 1];
	}

}

void dfsBlack(Node * node) {
	if (DEBUG) {
		printf("dfsBlack %d %d %d\n", node->row, node->column, node->color);
	}

	node->visited = 1;
	if (node->row == n - 1) {
		win = BLACK;
		return;
	}
	int aI;
	for (aI = 0; aI < node->adjSize; aI++) {
		if (node->adj[aI]->visited == 0) {
			dfsBlack(node->adj[aI]);
		}
	}
}

/**
 * 260
 */
int main(int argc, char * argv[]) {
	int test, i, j;
	for (test = 1;; test++) {
		scanf("%d", &n);
		if (n == 0)
			break;

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				char c;
				while (1) {
					c = getchar();
					if (c == 'b' || c == 'w')
						break;
				}

				if (c == 'b') {
					board[i][j] = new(i, j, BLACK);
				} else if (c == 'w') {
					board[i][j] = new(i, j, WHITE);
				}
			}
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				makeConnection(i, j);
			}
		}
		if (DEBUG) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					printf("[[%d][%d]color:%d,adjSize:%d] ", i, j, board[i][j]->color, board[i][j]->adjSize);
				}
				printf("\n");
			}
			printf("\n");
		}

		win = WHITE;
		for (j = 0; j < n; j++) {
			if (win == WHITE && board[0][j]->visited == 0 && board[0][j]->color == BLACK) {
				dfsBlack(board[0][j]);
			}
		}
		if (win == BLACK) {
			printf("%d B\n", test);
		} else {
			printf("%d W\n", test);
		}

	}
	return 0;
}
