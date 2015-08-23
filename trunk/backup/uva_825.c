#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 1000

#define NUL -1
static int board[NODE_MAX][NODE_MAX], rowSize, colSize, pathSize;

void dfs(int x, int y) {
	if (board[x][y] || y > colSize || x > rowSize) {
		return;
	}

	if (x == rowSize && y == colSize) {
		pathSize++;
		return;
	}

	dfs(x, y + 1);
	dfs(x + 1, y);
}

/**
 * 825
 */
int main(int argc, char * argv[]) {
	int i, j, testCase, testCaseNum;
	scanf("%d", &testCaseNum);
	for (testCase = 0; testCase < testCaseNum; testCase++) {

		scanf("%d %d", &rowSize, &colSize);
		for (i = 1; i <= rowSize; i++) {
			for (j = 1; j <= colSize; j++) {
				board[i][j] = 0;
			}
		}

		char line[256];
		fgets(line, 256, stdin);
		for (i = 0; i < rowSize; i++) {
			fgets(line, 256, stdin);
			int n[colSize];
			int nSize = 0, num = 0;
			for (j = 0; j < strlen(line); j++) {
				if (line[j] <= '9' && line[j] >= '0') {
					num = num * 10 + (line[j] - '0');
				} else if (line[j] == ' ') {
					n[nSize++] = num;
					num = 0;
				}
			}
			n[nSize++] = num;
			for (j = 1; j < nSize; j++) {
				board[n[0]][n[j]] = 1;
			}
		}

		if (DEBUG) {
			for (i = 1; i <= rowSize; i++) {
				for (j = 1; j <= colSize; j++) {
					printf("[%d][%d]%d  ", i, j, board[i][j]);
				}
				printf("\n");
			}
		}
		pathSize = 0;
		dfs(1, 1);
		if (testCase > 0) {
			printf("\n");
		}
		printf("%d\n", pathSize);
	}
	return 0;
}
