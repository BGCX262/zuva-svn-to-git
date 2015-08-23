#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct Carr {
	int index;
	int num;
} Carr;

static Carr * train[64];
static int trainSize;
static int swap;

Carr * new(int i, int n) {
	Carr *pC = malloc(sizeof(Carr));
	pC->index = i;
	pC->num = n;
	return pC;
}

int compare(const void * a, const void * b) {
	return ((*(Carr **) b)->num - (*(Carr **) a)->num);
}

int main(int argc, char * argv[]) {
	int testN, test, i, j, len;
	scanf("%d\n", &testN);
	for (test = 0; test < testN; test++) {
		scanf("%d\n", &len);
		trainSize = 0;
		swap = 0;
		for (i = 0; i < len; i++) {
			int num;
			scanf("%d", &num);
			Carr * pCarr = new(i, num);
			train[trainSize++] = pCarr;
		}

		if (DEBUG) {
			printf("================= Train =================================\n");
			for (i = 0; i < trainSize; i++) {
				printf("index %d num %d\n", train[i]->index, train[i]->num);
			}
		}

		Carr * sortedTrain[trainSize];
		memcpy(sortedTrain, train, sizeof(Carr*) * trainSize);
		qsort(sortedTrain, trainSize, sizeof(Carr *), compare);
		if (DEBUG) {
			printf("================= Sorted Train =================================\n");
			for (i = 0; i < trainSize; i++) {
				printf("index %d num %d\n", sortedTrain[i]->index, sortedTrain[i]->num);
			}
		}

		for (i = 0; i < trainSize; i++) {
			Carr * cur = sortedTrain[i];
			/*to (num -1) and swap (num -1 - index) times*/
			int to = cur->num - 1;
			swap += (cur->num - 1 - cur->index > 0 ? cur->num - 1 - cur->index : -(cur->num - 1 - cur->index));
			for (j = cur->index; j < to; j++) {
				train[j] = train[j + 1];
				train[j]->index--;
			}
			train[to] = cur;
			cur->index = to;
		}
		printf("Optimal train swapping takes %d swaps.\n", swap);
		for (i = 0; i < trainSize; i++) {
			free(train[i]);
		}
	}
	return 0;
}
