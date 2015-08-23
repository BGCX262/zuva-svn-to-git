#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static int lec[1028], di[1028], topic[1028], topicSize, lecLen, C;

void printDP() {
	int i, j, k;
	printf("topic ...\n");
	for (i = 0; i <= topicSize; i++) {
		printf("%d ", topic[i]);
	}
	printf("\n");
	printf("lec ...\n");
	for (i = 0; i <= topicSize; i++) {
		printf("[%d]%d ", i, lec[i]);
	}
	printf("\n");
	printf("di ...\n");
	for (i = 0; i <= topicSize; i++) {
		printf("[%d]%d ", i, di[i]);
	}
	printf("\n");

}

int getDI(int t) {
	if (t == 0)
		return 0;
	if (t >= 1 && t <= 10)
		return -C;
	return (t - 10) * (t - 10);
}

/**
 * 607
 */
int main(int argc, char * argv[]) {

	int test, i, j, k;
	char c;
	for (test = 1;; test++) {
		scanf("%d", &topicSize);
		if (topicSize == 0)
			break;
		scanf("%d %d", &lecLen, &C);
		for (i = 1; i <= topicSize; i++) {
			scanf("%d", &topic[i]);
		}

		memset(lec, -1, sizeof(int) * (topicSize + 1));
		memset(di, 0, sizeof(int) * (topicSize + 1));

		lec[0] = di[0] = 0;

		for (i = 1; i <= topicSize; i++) {
			lec[i] = lec[i - 1] + 1;
			di[i] = getDI(lecLen - topic[i]) + di[i - 1];
			int sum = topic[i];
			for (j = i - 1; j >= 0; j--) {
				sum += topic[j];
				if (sum <= lecLen) {
					int lecTemp = lec[j - 1] + 1;
					int diTemp = getDI(lecLen - sum) + di[j - 1];
					if (lecTemp < lec[i]) {
						lec[i] = lecTemp;
						di[i] = diTemp;
					} else if (lecTemp == lec[i] && diTemp < di[i]) {
						di[i] = diTemp;
					}
				} else
					break;
			}
		}

		if (DEBUG)
			printDP();

		if (test > 1) {
			printf("\n");
		}
		printf("Case %d:\n", test);
		printf("Minimum number of lectures: %d\n", lec[topicSize]);
		printf("Total dissatisfaction index: %d\n", di[topicSize]);
	}
	return 0;
}
