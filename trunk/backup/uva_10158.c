#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int n;

int findRoot(int root[], int i) {
	if (root[i] == i)
		return i;
	int t = findRoot(root, root[i]);
	root[i] = t;
	return root[i];
}

/**
 * 10158
 */
int main(int argc, char * argv[]) {
	int i, c, x, y, j;
	scanf("%d", &n);
	int p[2 * n + 5];
	for (i = 0; i < 2 * n + 5; i++) {
		p[i] = i;
	}
	for (;;) {
		scanf("%d %d %d", &c, &x, &y);
		if (c == 0 && x == 0 && y == 0)
			break;
		int xFriendRoot = findRoot(p, x);
		int xEnimyRoot = findRoot(p, x + n);
		int yFriendRoot = findRoot(p, y);
		int yEnimyRoot = findRoot(p, y + n);
		if (c == 1) {
			if (xFriendRoot == yEnimyRoot) {
				printf("-1\n");
			} else {
				p[xFriendRoot] = yFriendRoot;
				p[xEnimyRoot] = yEnimyRoot;
			}
		} else if (c == 2) {
			if (xFriendRoot == yFriendRoot) {
				printf("-1\n");
			} else {
				p[xEnimyRoot] = yFriendRoot;
				p[yEnimyRoot] = xFriendRoot;
			}
		} else if (c == 3) {
			if (xFriendRoot == yFriendRoot) {
				printf("1\n");
			} else {
				printf("0\n");
			}
		} else if (c == 4) {
			if (xFriendRoot == yEnimyRoot) {
				printf("1\n");
			} else {
				printf("0\n");
			}
		}
	}
	return 0;
}
