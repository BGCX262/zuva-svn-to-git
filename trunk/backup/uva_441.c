#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct NODE {
	int from, to, num;
	struct NODE * left;
	struct NODE * right;
} Node;

Node * new(int n, int f, int t) {
	Node * p = malloc(sizeof(Node));
	p->from = f;
	p->to = t;
	p->num = n;
	p->left = NULL;
	p->right = NULL;
	return p;
}

/**
 * 11235
 */
int main(int argc, char * argv[]) {
	int k, first = 0, i, i1, i2, i3, i4, i5, i6, j;

	for (scanf("%d", &k); k != 0; scanf("%d", &k)) {
		if (first != 0) {
			printf("\n");
		} else {
			first = 1;
		}
		int s[k];
		for (i = 0; i < k; i++) {
			scanf("%d", &s[i]);
		}

		for (i1 = 0; i1 <= k - 6; i1++) {
			for (i2 = i1 + 1; i2 <= k - 5; i2++) {
				for (i3 = i2 + 1; i3 <= k - 4; i3++) {
					for (i4 = i3 + 1; i4 <= k - 3; i4++) {
						for (i5 = i4 + 1; i5 <= k - 2; i5++) {
							for (i6 = i5 + 1; i6 <= k - 1; i6++) {
								printf("%d %d %d %d %d %d\n", s[i1], s[i2], s[i3], s[i4], s[i5], s[i6]);
							}
						}
					}
				}
			}
		}
	}

	return 0;
}

