#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
#define N_MAX 100

int isGreen(int time, int cycle) {

	if ((time / cycle) % 2 == 0) {
		if ((time % cycle) < (cycle - 5))
			return 1;
	}

	return 0;
}
int main(int argv, char * argc[]) {
	int i, j, now, min, nSize = 0, n, r, isAllGreen = 1;
	int arrN[N_MAX];
	while (1) {
		r = scanf("%d", &n);
		if (n == 0 && nSize == 0) {
			r = scanf("%d", &n);
			r = scanf("%d", &n);
			break;
		}

		arrN[nSize++] = n;
		if (n == 0) {
			/*
			 * calculate
			 */

			if (DEBUG) {
				printf("calculate arrN:\n");
				for (i = 0; i < nSize; i++) {
					printf("%d ", arrN[i]);
				}
				printf("\n");
				printf("5h:%d\n", 5 * 60 * 60);
			}
			min = 90;
			for (i = 0; i < nSize - 1; i++) {
				if (arrN[i] < min)
					min = arrN[i];
			}

			for (now = min * 2; now <= 18000;) {
				for (i = 0; i < nSize - 1; i++) {
					if (!isGreen(now, arrN[i])) {
						if (DEBUG) {
							printf("now:%d arrN:%d is not green\n", now, arrN[i]);
						}

						isAllGreen = 0;
						break;
					}
					if (DEBUG) {
						printf("now:%d arrN:%d is green\n", now, arrN[i]);
					}

				}
				if (!isAllGreen) {
					if (DEBUG) {
						printf("now %d to ", now);
					}
					now = arrN[i] * ((now / arrN[i]) + 1);
					if (DEBUG) {
						printf("%d\n", now);
					}
					isAllGreen = 1;
				} else
					break;
			}

			if (isAllGreen && now <= 18000) {
				if (DEBUG) {
					printf("all green at %d\n", now);
				}
				printf("0%d:", now / 3600);
				now = now - (now / 3600) * 3600;
				if (now / 60 < 10) {
					printf("0");
				}
				printf("%d:", now / 60);
				now = now - (now / 60) * 60;
				if (now < 10) {
					printf("0");
				}
				printf("%d\n", now);
			} else {
				printf("Signals fail to synchronise in 5 hours\n");
			}

			nSize = 0;
		}

	}
	return 0;
}
