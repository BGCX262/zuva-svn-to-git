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
 * 459
 */
int main(int argc, char * argv[]) {
	int caseNum;
	char line[8];
	scanf("%d", &caseNum);
	gets(line);
	gets(line);
	while (caseNum-- > 0) {
		int i, max = -1;
		int root[26];
		while (gets(line) != NULL && line[0] >= 'A' && line[0] <= 'Z') {
			/*while (gets(line) && line[0]) {*/
			int r1, r2, n1, n2;
			if (line[1] >= 'A' && line[1] <= 'Z') {
				n1 = line[0] - 'A';
				n2 = line[1] - 'A';
				r1 = findRoot(root, n1);
				r2 = findRoot(root, n2);
				if (r1 != r2) {
					root[r1] = r2;
				}
			} else {
				max = line[0] - 'A';
				for (i = 0; i <= max; i++) {
					root[i] = i;
				}
			}
			if (DEBUG) {
				printf("n1 %d n2 %d\n", n1, n2);
				for (i = 0; i <= max; i++) {
					printf("%d ", root[i]);
				}
				printf("\n");
			}

		}
		for (i = 0; i <= max; i++) {
			findRoot(root, i);
		}

		int diff[26];
		int diffSize = 0;
		diff[diffSize++] = root[0];

		for (i = 0; i <= max; i++) {
			int j, same = 0;
			for (j = 0; j < diffSize; j++) {
				if (root[i] == diff[j]) {
					same = 1;
					break;
				}
			}
			if (same == 0) {
				diff[diffSize++] = root[i];
			}
		}
		printf("%d\n", diffSize);
		if (caseNum > 0) {
			printf("\n");
		}
	}
	return 0;
}

