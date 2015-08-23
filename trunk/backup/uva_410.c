#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

int compare(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

double getABS(double in) {
	if (in > 0)
		return in;
	return -in;
}

/**
 * 410
 */
int main(int argc, char * argv[]) {
	int n, i, chamberSize, massSize, set = 0;
	while (scanf("%d %d", &chamberSize, &massSize) == 2) {
		set++;
		n = chamberSize << 1;
		int mass[n];
		for (i = 0; i < n - massSize; i++) {
			mass[i] = 0;
		}
		for (i = n - massSize; i < n; i++) {
			scanf("%d", &mass[i]);
		}
		qsort(mass, n, sizeof(int), compare);
		double total = 0;
		for (i = 0; i < n; i++) {
			total += mass[i];
		}

		double ave = total / (double) chamberSize;
		double imbalance = 0;
		for (i = 0; i < chamberSize; i++) {
			imbalance += getABS(((double) (mass[i] + mass[n - 1 - i]) - ave));
		}
		if (DEBUG) {
			printf("imbalance %f ave %f\n", imbalance, ave);
			for (i = 0; i < n; i++) {
				printf("%d ", mass[i]);
			}
			printf("\n");
		}

		printf("Set #%d\n", set);
		for (i = 0; i < chamberSize; i++) {
			int first = mass[i];
			int last = mass[n - 1 - i];
			if (first == 0 && last == 0) {
				printf(" %d:\n", i);
			} else if (first == 0 && last != 0) {
				printf(" %d: %d\n", i, last);
			} else if (first != 0 && last != 0) {
				printf(" %d: %d %d\n", i, first, last);
			}
		}
		printf("IMBALANCE = %0.5f\n\n", imbalance);
	}

	return 0;
}
