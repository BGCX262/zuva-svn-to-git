#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int order[26][26], visited[26], finish[26];
static int time;

void dfs(int curr) {
	int i, j;
	visited[curr] = 1;
	for (j = 0; j < 26; j++) {
		if (j == curr)
			continue;

		if (visited[j] == 0 && order[curr][j]) {
			dfs(j);
		}
	}

	visited[curr] = 2;
	finish[curr] = ++time;
}

/**
 * 200
 */
int main(int argc, char * argv[]) {
	int i, j, input[5000][20], inputSize, letter[26];
	char line[32];
	memset(order, 0, 26 * 26 * sizeof(int));
	memset(visited, 0, 26 * sizeof(int));
	memset(input, -1, 20 * 256 * sizeof(int));
	memset(finish, 0, 26 * sizeof(int));
	memset(letter, 0, 26 * sizeof(int));
	time = 0;
	inputSize = 0;
	for (;;) {
		gets(line);
		if (line[0] == '#')
			break;
		for (i = 0; i < strlen(line) - 1; i++) {
			if (line[i] >= 'A' && line[i] <= 'Z')
				input[inputSize][i] = line[i] - 'A';
		}
		inputSize++;
	}

	if (inputSize == 1) {
		printf("%c\n", input[0][0] + 'A');
		return 0;
	}

	for (i = 0; i < inputSize - 1; i++) {
		for (j = 0; j < 20; j++) {
			if (input[i][j] == -1)
				continue;
			if (j == 0) {
				if (input[i + 1][j] != -1 && input[i][j] != -1 && input[i][j] != input[i + 1][j]) {
					order[input[i][j]][input[i + 1][j]] = 1;
					letter[input[i][j]] = 1;
					letter[input[i + 1][j]] = 1;
				}
			} else {
				if (input[i][j - 1] != -1 && input[i + 1][j - 1] != -1 && input[i][j] != -1 && input[i + 1][j] != -1 && input[i][j - 1] == input[i + 1][j - 1]
						&& input[i][j] != input[i + 1][j]) {
					letter[input[i][j]] = 1;
					letter[input[i + 1][j]] = 1;
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

		printf("letter \n");
		for (i = 0; i < 26; i++) {
			if (letter[i]) {
				printf("%c ", 'A' + i);
			}

		}
		printf("\n");
	}

	for (i = 0; i < 26; i++) {
		if (letter[i] && visited[i] == 0) {
			int root = 1;
			for (j = 0; j < 26; j++) {
				if (order[j][i]) {
					root = 0;
					break;
				}
			}
			if (root)
				dfs(i);
		}
	}
	if (DEBUG) {
		printf("finish time \n");
		for (i = 0; i < 26; i++) {
			if (letter[i])
				printf("%c %d\n", 'A' + i, finish[i]);

		}
		printf("\n");
	}

	int maxFinish = 0;
	int max = -1;
	for (;;) {
		maxFinish = 0;
		max = -1;
		for (j = 0; j < 26; j++) {
			if (finish[j] > maxFinish) {
				max = j;
				maxFinish = finish[j];
			}
		}
		if (max == -1)
			break;
		finish[max] = 0;
		printf("%c", 'A' + max);
	}
	printf("\n");

	return 0;
}
