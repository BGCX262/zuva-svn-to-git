#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int stick[32], stickNum, sum, visited[32];

int compare(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

int dp(int curr, int currSum, int lnum) {
	if (currSum == sum) {
		curr = 0;
		currSum = 0;
		lnum++;
	}
	if (lnum == 4) {
		return 1;
	}

	int i, j;
	for (i = curr; i < stickNum; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			if (currSum + stick[i] <= sum) {
				if (dp(i, currSum + stick[i], lnum)) {
					return 1;
				}
			} else {
				visited[i] = 0;
				break;
			}
			visited[i] = 0;
		}
	}
	return 0;

}

/**
 * 10364
 */
int main(int argc, char * argv[]) {
	int test, i, j, k;
	char c;
	for (scanf("%d", &test); test > 0; test--) {
		scanf("%d", &stickNum);
		sum = 0;
		for (i = 0; i < stickNum; i++) {
			scanf("%d", &stick[i]);
			sum += stick[i];
			visited[i] = 0;
		}
		if (sum % 4 != 0) {
			printf("no\n");
			continue;
		}
		sum = sum >> 2;

		qsort(stick, stickNum, sizeof(int), compare);
		if (dp(0, 0, 0)) {
			printf("yes\n");
		} else {
			printf("no\n");
		}
	}
	return 0;
}
