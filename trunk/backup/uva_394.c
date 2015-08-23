#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

/**
 * uva 394
 */

struct Arr {
	char name[16];
	int basicAddr;
	int sizeEle;
	int dimensionSize;
	int dimensionLower[11], dimensionUpper[11], C[11];
};

static struct Arr arrs[128];

int main() {
	int arrsSize, R, i, j, k;
	char s[16];
	scanf("%d %d\n", &arrsSize, &R);
	for (i = 0; i < arrsSize; i++) {
		struct Arr * a = &(arrs[i]);
		scanf("%s %d %d %d", s, &(a->basicAddr), &(a->sizeEle), &(a->dimensionSize));
		strcpy(a->name, s);
		for (j = 1; j <= a->dimensionSize; j++) {
			scanf("%d %d", &(a->dimensionLower[j]), &(a->dimensionUpper[j]));
			a->C[a->dimensionSize] = a->sizeEle;
			for (k = a->dimensionSize - 1; k >= 1; k--) {
				a->C[k] = a->C[k + 1] * (a->dimensionUpper[k + 1] - a->dimensionLower[k + 1] + 1);
			}
			a->C[0] = a->basicAddr;
			for (k = 1; k <= a->dimensionSize - 1; k++) {
				a->C[0] -= (a->C[k] * a->dimensionLower[k]);
			}
			a->C[0] -= (a->C[a->dimensionSize] * a->dimensionLower[a->dimensionSize]);
		}

	}
	while (R-- > 0) {
		char name[16];
		scanf("%s", name);
		for (i = 0; i < arrsSize; i++) {
			struct Arr * a = &(arrs[i]);
			if (strcmp(a->name, name) == 0) {
				int in[11];
				for (j = 1; j <= a->dimensionSize; j++) {
					scanf("%d", &(in[j]));
				}
				int r = a->C[0];
				for (j = 1; j <= a->dimensionSize; j++) {
					r += (in[j] * a->C[j]);
				}
				printf("%s[", name);
				for (j = 1; j <= a->dimensionSize; j++) {
					printf("%d", in[j]);
					if (j < a->dimensionSize) {
						printf(", ");
					}
				}
				printf("] = %d\n", r);
				break;
			}
		}

	}

	return 0;
}

