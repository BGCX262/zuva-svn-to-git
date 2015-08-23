#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int order[26][26], visited[26], topSort[26];
static int topSortSize;

void dfs(int curr) {
	if (DEBUG) {
		printf("dfs %c\n", curr + 'A');
	}
	int i, j;
	visited[curr] = 1;
	for (j = 0; j < 26; j++) {
		if (visited[j] == 0 && order[curr][j]) {
			dfs(j);
		}
	}
	topSort[topSortSize++] = curr;
	visited[curr] = 2;
}

/**
 * 200
 */
int main(int argc, char * argv[]) {
	int i, j, input[5000][20], inputSize, noIncomingNode[26];
	char line[32];
	memset(order, 0, 26 * 26 * sizeof(int));
	memset(visited, 0, 26 * sizeof(int));
	memset(input, -1, 5000 * 20 * sizeof(int));
	memset(topSort, 0, 26 * sizeof(int));
	memset(noIncomingNode, 0, 26 * sizeof(int));
	inputSize = 0;
	topSortSize = 0;
	for (;;) {
		gets(line);
		if (line[0] == '#')
			break;
		for (i = 0; i < strlen(line); i++) {
			if (line[i] >= 'A' && line[i] <= 'Z') {
				noIncomingNode[line[i] - 'A'] = 1;
				input[inputSize][i] = line[i] - 'A';
			}

		}
		inputSize++;
	}

	for (i = 0; i < inputSize - 1; i++) {
		for (j = 0; j < 20; j++) {
			if (input[i][j] == -1)
				continue;
			if (j == 0) {
				if (input[i + 1][j] != -1 && input[i][j] != -1
						&& input[i][j] != input[i + 1][j]) {
					order[input[i][j]][input[i + 1][j]] = 1;
					noIncomingNode[input[i + 1][j]] = 0;
				}
			} else {
				if (input[i][j - 1] != -1 && input[i + 1][j - 1] != -1
						&& input[i][j] != -1 && input[i + 1][j] != -1
						&& input[i][j - 1] == input[i + 1][j - 1]
						&& input[i][j] != input[i + 1][j]) {
					noIncomingNode[input[i + 1][j]] = 0;
					order[input[i][j]][input[i + 1][j]] = 1;
				}
			}
		}
	}

	if (DEBUG) {
		printf("input \n");
		for (i = 0; i < inputSize; i++) {
			for (j = 0; j < 20; j++) {
				if (input[i][j] != -1) {
					printf("%c ", 'A' + input[i][j]);
				}
			}
			printf("\n");
		}
		printf("order \n");
		for (i = 0; i < 26; i++) {
			for (j = 0; j < 26; j++) {
				if (order[i][j]) {
					printf("%c over %c\n ", 'A' + i, 'A' + j);
				}
			}
		}
		printf("\n");

		printf("noIncomingNode \n");
		for (i = 0; i < 26; i++) {
			if (noIncomingNode[i]) {
				printf("%c ", 'A' + i);
			}

		}
		printf("\n");
	}

	for (i = 0; i < 26; i++) {
		if (noIncomingNode[i] && visited[i] == 0) {
			dfs(i);
		}
		for (j = topSortSize - 1; j >= 0; j--) {
			printf("%c", topSort[j] + 'A');
		}
		topSortSize = 0;
	}

	printf("\n");

	return 0;
}
