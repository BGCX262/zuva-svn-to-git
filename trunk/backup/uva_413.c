#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 1

int main() {
	int i, j, k, num[30], numSize, up[30], upSize, down[30], downSize;
	float upAve, downAve;

	for (;;) {
		upSize = downSize = numSize = 0;
		upAve = downAve = 0;
		memset(num, 0, 30 * sizeof(int));
		memset(up, 0, 30 * sizeof(int));
		memset(down, 0, 30 * sizeof(int));

		scanf("%d", &num[numSize++]);
		if (num[numSize - 1] == 0)
			break;
		for (;;) {
			scanf("%d", &num[numSize++]);
			if (num[numSize - 1] == 0) {
				numSize--;
				break;
			}
		}

		int prev = 0;
		int prevEqNum = 0;

		for (i = 1; i < numSize; i++) {
			if (num[i] > num[i - 1]) {
				if (prev == 1) {
					up[upSize - 1]++;
				} else {
					up[upSize++] = 1 + prevEqNum;
				}
				prev = 1;
				prevEqNum = 0;
			} else if (num[i] < num[i - 1]) {
				if (prev == -1) {
					down[downSize - 1]++;
				} else {
					down[downSize++] = 1 + prevEqNum;
				}
				prev = -1;
				prevEqNum = 0;
			} else {
				if (prev == 0)
					prevEqNum++;
				else if (prev == 1) {
					up[upSize - 1]++;
				} else {
					down[downSize - 1]++;
				}
			}
		}
		int n = 0;
		if (upSize > 0) {
			for (i = 0; i < upSize; i++) {
				n += up[i];
			}
			upAve = (float) n / (float) upSize;
		}
		n = 0;
		if (downSize > 0) {
			for (i = 0; i < downSize; i++) {
				n += down[i];
			}
			downAve = (float) n / (float) downSize;
		}
		printf("Nr values = %d:  %.6f %.6f\n", numSize, upAve, downAve);

	}

	return 0;
}
