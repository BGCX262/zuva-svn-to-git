#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * 437
 */

typedef struct Tower {
	int x, y, z;
} Tower;

static int n, allSize, height[200];
static Tower all[200];

void add(int x, int y, int z) {
	all[allSize].x = x;
	all[allSize].y = y;
	all[allSize].z = z;
	allSize++;
}

int cmp(const void * a, const void * b) {
	Tower * ta = (Tower *) a;
	Tower * tb = (Tower *) b;
	if (ta->x != tb->x) {
		return ta->x - tb->x;
	} else {
		return ta->y - tb->y;
	}
}

int main(int argc, char * argv[]) {
	int i, j, caseNum = 1, x, y, z;
	for (;;) {
		scanf("%d\n", &n);
		if (n == 0) {
			break;
		}
		allSize = 0;
		for (i = 0; i < n; i++) {
			scanf("%d %d %d\n", &x, &y, &z);
			add(x, y, z);
			add(y, x, z);
			add(z, x, y);
			add(x, z, y);
			add(y, z, x);
			add(z, y, x);
		}
		qsort(all, allSize, sizeof(Tower), cmp);

		for (i = 0; i < allSize; i++) {
			height[i] = all[i].z;
		}
		if (DEBUG) {
			printf("all\n");
			for (i = 0; i < allSize; i++) {
				printf("all[%d] %d %d %d\n", i, all[i].x, all[i].y, all[i].z);
			}
		}

		for (i = 0; i < allSize; i++) {
			for (j = 0; j < i; j++) {
				if (all[j].x < all[i].x && all[j].y < all[i].y && height[i] < height[j] + all[i].z) {
					height[i] = height[j] + all[i].z;
				}
			}
		}
		if (DEBUG) {
			printf("height\n");
			for (i = 0; i < allSize; i++) {
				printf("height[%d] %d \n", i, height[i]);
			}
		}
		int max = height[0];
		for (i = 0; i < allSize; i++) {
			if (max < height[i]) {
				max = height[i];
			}
		}
		printf("Case %d: maximum height = %d\n", caseNum, max);
		caseNum++;
	}
	return 0;
}

