#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 1

#define max(a,b) (a>b)?a:b

typedef struct Array {
	int row, col;
} ARRAY;

ARRAY all[11];
int min[11][11], split[11][11];

int dfs(int left, int right) {
	int m = 0;
	if (min[left][right]) {
		return min[left][right];
	} else if (left == right) {
		min[left][right] = m;
		split[left][right] = left;
		return m;
	} else if (left == right - 1) {
		m = all[left].row * all[right].col * all[left].col;
		min[left][right] = m;
		split[left][right] = left;
		return m;
	}

	int i;
	for (i = left; i < right; i++) {
		int leftM = dfs(left, i);
		int rightM = dfs(i+1, right);
		int multi = leftM + rightM + all[left].row * all[i].col * all[right].col;
		if (m == 0 || m > multi) {
			m = multi;
			min[left][right] = m;
			split[left][right] = i;
		}
	}
	/*if (DEBUG) {
	 printf("dfs left %d right %d ", left, right);
	 printf(" arr row %d col %d ", arr->row, arr->col);
	 printf(" return %d\n", m);
	 }*/

	return m;
}

void build(int left, int right, char rep[]) {
	int m = 0;
	if (left == right) {
		strcpy(rep, "A");
		char str[15];
		sprintf(str, "%d", left + 1);
		strcat(rep, str);
		return;
	} else if (left == right - 1) {
		strcpy(rep, "(A");
		char str[15];
		sprintf(str, "%d", left + 1);
		strcat(rep, str);
		strcat(rep, " x ");
		strcat(rep, "A");
		sprintf(str, "%d", right + 1);
		strcat(rep, str);
		strcat(rep, ")");
		return;
	}

	int i;
	char repLeft[64], repRight[64];
	build(left, split[left][right], repLeft);
	build(split[left][right] + 1, right, repRight);
	strcpy(rep, "(");
	strcat(rep, repLeft);
	strcat(rep, " x ");
	strcat(rep, repRight);
	strcat(rep, ")");
	return;
}

int main() {
	int n, i, j, count = 0;
	for (;;) {
		count++;
		scanf("%d\n", &n);
		if (n == 0)
			break;

		for (i = 0; i < n; i++) {
			scanf("%d %d\n", &all[i].row, &all[i].col);
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				min[i][j] = split[i][j] = 0;
			}
		}

		char rep[64];
		dfs(0, n - 1);
		build(0, n - 1, rep);
		printf("Case %d: %s\n", count, rep);
	}
	return 0;
}
