#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct NODE {
	int left, right, height, leaf;
} Node;
Node all[5000005];
void cut(int r, int c) {
	int leftSon = r * 2;
	int rightSon = r * 2 + 1;
	all[leftSon].left = all[r].left;
	all[leftSon].right = c;
	all[leftSon].height = all[r].height;
	all[leftSon].leaf = 1;

	all[rightSon].left = c;
	all[rightSon].right = all[r].right;
	all[rightSon].height = all[r].height;
	all[rightSon].leaf = 1;

	all[r].leaf = 0;

}

int dfs(int root, int l, int r, int h) {
	if (DEBUG)
		printf("dfs %d %d %d\n", root, l, r);

	int leftOverlap = all[root].left > l ? all[root].left : l;
	int rightOverlap = all[root].right < r ? all[root].right : r;
	if (leftOverlap >= rightOverlap) {
		return 0;
	}

	if (all[root].leaf == 0) {
		return dfs(root * 2, l, r, h) + dfs(root * 2 + 1, l, r, h);
	}

	if (all[root].height > h) {
		return 0;
	}

	if (all[root].left < l) {
		cut(root, l);
		return dfs(root, l, r, h);
	}

	if (all[root].right > r) {
		cut(root, r);
		return dfs(root, l, r, h);
	}
	all[root].height = h;
	return all[root].right - all[root].left;
}

/**
 * 1232
 */
int main(int argc, char * argv[]) {
	int t, i, n, num, l, r, h, sum;
	scanf("%d\n", &n);
	for (t = 0; t < n; t++) {
		sum = 0;
		all[1].left = 0;
		all[1].right = 100000;
		all[1].height = 0;
		all[1].leaf = 1;
		scanf("%d\n", &num);

		for (i = 0; i < num; i++) {
			scanf("%d %d %d\n", &l, &r, &h);
			sum += dfs(1, l, r, h);
			if (DEBUG)
				printf("sum:%d\n", sum);

		}
		printf("%d\n", sum);
	}
	return 0;
}

