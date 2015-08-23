#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct Carr {
	int index;
	int num;
} Carr;

Carr * new(int i, int n) {
	Carr *pC = malloc(sizeof(Carr));
	pC->index = i;
	pC->num = n;
	return pC;
}

static int station[1000];
static int stationSize;

void dequeue() {
	if (stationSize > 0) {
		stationSize--;
	}
}

void enqueue(int n) {
	station[stationSize++] = n;
}

int main(int argc, char * argv[]) {
	int n, test, i, j, len;
	for (;;) {
		scanf("%d\n", &n);
		if (n == 0)
			break;
		int output[n], input[n];
		for (i = 0; i < n; i++) {
			input[i] = i + 1;
		}
		for (;;) {
			int stop = 0;
			for (i = 0; i < n; i++) {
				scanf("%d", &output[i]);
				if (i == 0 && output[i] == 0) {
					stop = 1;
					break;
				}
			}
			if (stop == 1) {
				break;
			}
			int inIndex, outIndex;

			stationSize = 0;

			for (inIndex = 0, outIndex = 0; inIndex < n && outIndex < n;) {

				if (DEBUG) {
					printf("outIndex %d \n", outIndex);
					for (i = 0; i < n; i++) {
						printf("%d ", output[i]);
					}
					printf("\n");
					printf("inIndex %d\n", inIndex);
					for (i = 0; i < n; i++) {
						printf("%d ", input[i]);
					}
					printf("\n");
					printf("station %d items\n", stationSize);
					for (i = 0; i < stationSize; i++) {
						printf(" %d ", station[i]);
					}
					printf("\n");
				}

				if (input[inIndex] == output[outIndex]) {
					inIndex++;
					outIndex++;
					continue;
				}

				if (stationSize > 0 && output[outIndex] == station[stationSize - 1]) {
					dequeue();
					outIndex++;
					continue;
				}
				enqueue(input[inIndex++]);
			}

			if (inIndex == n) {
				for (; outIndex < n; outIndex++) {
					if (station[stationSize - 1] == output[outIndex]) {
						dequeue();
					}
				}
			}

			if (inIndex == n && outIndex == n && stationSize == 0) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
		}
		printf("\n");
	}

	return 0;
}
