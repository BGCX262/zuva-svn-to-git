#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

int main() {
	int i, j, k, Z, I, M, L, L2;

	for (j = 1;; j++) {
		scanf("%d %d %d %d", &Z, &I, &M, &L);
		if (Z == 0 && I == 0 && M == 0 && L == 0)
			break;

		L2 = L;
		int LArr[M], LArrSize = 0;
		LArr[LArrSize++] = L;

		for (i = 1;; i++) {
			int nextL = (Z * L2 + I) % M;

			for (k = 0; k < LArrSize; k++) {
				if (nextL == LArr[k])
					break;
			}

			if (k < LArrSize)
				break;
			LArr[LArrSize++] = nextL;
			L2 = nextL;
		}

		printf("Case %d: %d\n", j, (LArrSize - k));
	}

	return 0;
}
