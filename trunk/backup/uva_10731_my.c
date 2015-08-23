#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

#define MAX 26
#define DEF -1

static int adj[MAX][MAX], stack[MAX], stackSize, nodeIndex[MAX], low[MAX],
		node[MAX], result[MAX][MAX], resultColumnSize[MAX], resultRowSize,
		index;

int isInStack(int curr) {
	int i;
	for (i = 0; i < stackSize; i++) {
		if (stack[i] == curr) {
			return 1;
		}
	}
	return 0;
}

int dequeue() {
	if (stackSize > 0) {
		stackSize--;
		return stack[stackSize];
	} else {
		return DEF;
	}
}

void dfs(int curr) {
	int i, j;
	nodeIndex[curr] = low[curr] = index;
	index++;
	stack[stackSize++] = curr;
	for (i = 0; i < MAX; i++) {
		if (node[i] != DEF && adj[curr][i] != DEF && i != curr) {
			if (nodeIndex[i] == DEF) {
				dfs(i);
				low[curr] = low[i] < low[curr] ? low[i] : low[curr];
			} else if (isInStack(i)) {
				low[curr] = nodeIndex[i] < low[curr] ? nodeIndex[i] : low[curr];
			}
		}
	}

	if (low[curr] == nodeIndex[curr]) {
		/*pop stack */
		int top;
		while (1) {
			top = dequeue();
			if (top == curr) {
				result[resultRowSize][resultColumnSize[resultRowSize]++] = top;
				resultRowSize++;
				break;
			}
			result[resultRowSize][resultColumnSize[resultRowSize]++] = top;
		}
	}
}

/**
 * 10731
 */
int main(int argc, char * argv[]) {

	int i, j, k, nQuestion, question;
	char line[16];
	for (question = 0;; question++) {
		scanf("%d", &nQuestion);
		if (nQuestion == 0)
			break;
		if (question > 0)
			printf("\n");

		memset(adj, DEF, MAX * MAX * sizeof(int));
		memset(nodeIndex, DEF, MAX * sizeof(int));
		memset(low, DEF, MAX * sizeof(int));
		memset(node, DEF, MAX * sizeof(int));
		memset(resultColumnSize, 0, MAX * sizeof(int));
		memset(result, DEF, MAX * MAX * sizeof(int));
		resultRowSize = 0;
		index = 0;
		stackSize = 0;
		gets(line);

		for (i = 0; i < nQuestion; i++) {
			char cArr[6];
			int cArrSize = 0;
			gets(line);

			if (DEBUG) {
				printf("%s\n", line);
			}

			int len = strlen(line);
			for (j = 0; j < len; j++) {
				if (line[j] >= 'A' && line[j] <= 'Z') {
					cArr[cArrSize++] = line[j];
					node[line[j] - 'A'] = 1;
				}
			}
			for (j = 0; j < 5; j++) {
				if (cArr[5] != cArr[j])
					adj[cArr[5] - 'A'][cArr[j] - 'A'] = 1;
			}
		}

		for (i = 0; i < MAX; i++) {
			if (node[i] != DEF && nodeIndex[i] == DEF) {
				dfs(i);
			}
		}

		for (i = 0; i < resultRowSize; i++) {
			for (j = 0; j < resultColumnSize[i] - 1; j++) {
				int min = j;
				for (k = j + 1; k < resultColumnSize[i]; k++) {
					if (result[i][k] < result[i][min]) {
						min = k;
					}
				}
				int t = result[i][j];
				result[i][j] = result[i][min];
				result[i][min] = t;
			}
		}
		for (i = 0; i < resultRowSize - 1; i++) {
			int min = i;
			for (j = i + 1; j < resultRowSize; j++) {
				if (result[j][0] < result[min][0]) {
					min = j;
				}
			}
			int tempSize = resultColumnSize[i];
			int temp[tempSize];
			for (j = 0; j < tempSize; j++) {
				temp[j] = result[i][j];
			}

			for (j = 0; j < resultColumnSize[min]; j++) {
				result[i][j] = result[min][j];
			}
			resultColumnSize[i] = resultColumnSize[min];

			for (j = 0; j < tempSize; j++) {
				result[min][j] = temp[j];
			}
			resultColumnSize[min] = tempSize;
		}

		for (i = 0; i < resultRowSize; i++) {
			for (j = 0; j < resultColumnSize[i]; j++) {
				if (j == 0)
					printf("%c", 'A' + result[i][j]);
				else
					printf(" %c", 'A' + result[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
