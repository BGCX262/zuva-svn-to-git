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

int findRoot(int root[], int i) {
	if (DEBUG) {
		printf("findRoot root[%d] %d\n", root[i], i);
	}

	if (root[i] == i)
		return i;
	int t = findRoot(root, root[i]);
	root[i] = t;
	return root[i];
}

/**
 * 793
 */
int main(int argc, char * argv[]) {
	int caseNum;
	char line[32];
	scanf("%d", &caseNum);
	gets(line);
	gets(line);
	while (caseNum-- > 0) {

		int nodeNum = 0;
		scanf("%d", &nodeNum);
		if (DEBUG) {
			printf("nodeNum %d\n", nodeNum);
		}

		int root[nodeNum + 1];
		int i;
		for (i = 0; i < nodeNum + 1; i++) {
			root[i] = i;
		}
		gets(line);
		int right = 0, wrong = 0;
		while (gets(line) != NULL && (line[0] == 'c' || line[0] == 'q')) {
			char opr;
			int n1, n2;
			sscanf(line, "%c %d %d", &opr, &n1, &n2);
			int r1 = findRoot(root, n1);
			int r2 = findRoot(root, n2);
			if (opr == 'c') {
				if (r1 != r2) {
					root[r1] = r2;
				}
			} else if (opr == 'q') {
				if (r1 == r2) {
					right++;
				} else {
					wrong++;
				}
			}
			if (DEBUG) {
				printf("%d %c n1 %d n2 %d\n", caseNum, opr, n1, n2);
			}
		}

		printf("%d,%d\n", right, wrong);
		if (caseNum > 0)
			printf("\n");

		if (DEBUG) {
			printf("line:[%s]\n", line);
		}

	}
	return 0;
}

