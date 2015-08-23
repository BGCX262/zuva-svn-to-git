#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define MAX 1048576

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

static int * treePosition[20];
static int maxLeafNum, maxDepth;
static int flag[MAX];

void drop() {
	int i;
	for (i = 1; i < 20; i++) {
		int currLeafNum = 1 << i;
		int currDepth = i + 1;
		int maxNotLeafNode = (1 << (currDepth - 1)) - 1;
		memset(flag, 0, sizeof(int) * (1 << (currDepth - 1)));
		int j;
		for (j = 0; j < currLeafNum; j++) {
			int position = 1;
			while (position <= maxNotLeafNode) {
				flag[position] = (!flag[position]);
				position = 2 * position + (!flag[position]);
			}
			treePosition[i][j] = position;
		}
	}
}

/**
 * 679
 */
int main(int argc, char * argv[]) {
	int I, m, i;
	for (i = 1; i < 20; i++) {
		treePosition[i] = (int*) malloc(((1 << (i))) * sizeof(int));
	}
	drop();
	for (scanf("%d", &m); m > 0; m--) {
		scanf("%d", &maxDepth);
		if (maxDepth == -1)
			break;
		scanf("%d", &I);
		maxLeafNum = 1 << (maxDepth - 1);
		printf("%d\n", treePosition[maxDepth - 1][(I - 1) % (1 << (maxDepth - 1))]);
	}

	return 0;
}
