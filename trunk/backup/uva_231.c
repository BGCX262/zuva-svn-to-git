#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

int compare(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

/**
 * 231
 */
int main(int argc, char * argv[]) {
	int m[1028], m2[1028], mSize = 0, height, i, j, test = 0;
	for (;;) {
		scanf("%d", &height);
		if (height == -1 && mSize == 0) {
			break;
		} else if (height == -1 && mSize > 0) {
			test++;
			if (DEBUG) {
				printf("missile:\n");
				for (i = 0; i < mSize; i++) {
					printf("%d ", m[i]);
				}
				printf("\n");
			}
			for (i = 0; i < mSize / 2; i++) {
				int t = m[i];
				m[i] = m[mSize - 1 - i];
				m[mSize - 1 - i] = t;
			}
			memcpy(m2, m, sizeof(int) * mSize);
			qsort(m2, mSize, sizeof(int), compare);
			int lcs[mSize + 1][mSize + 1];
			for (i = 0; i <= mSize; i++) {
				lcs[i][0] = 0;
				lcs[0][i] = 0;
			}
			for (i = 1; i <= mSize; i++) {
				for (j = 1; j <= mSize; j++) {
					if (m[j - 1] == m2[i - 1]) {
						lcs[i][j] = lcs[i - 1][j - 1] + 1;
					} else {
						lcs[i][j] = lcs[i - 1][j] >= lcs[i][j - 1] ? lcs[i - 1][j] : lcs[i][j - 1];
					}
				}
			}
			if (test > 1) {
				printf("\n");
			}
			printf("Test #%d:\n", test);
			printf("  maximum possible interceptions: %d\n", lcs[mSize][mSize]);
			if (DEBUG) {
				printf("m2:\n");
				for (i = 0; i < mSize; i++) {
					printf("%d ", m2[i]);
				}
				printf("\n");
				printf("missile:\n");
				for (i = 0; i < mSize; i++) {
					printf("%d ", m[i]);
				}
				printf("\n");
			}
			mSize = 0;
		} else {
			m[mSize++] = height;
		}
	}
	return 0;
}
