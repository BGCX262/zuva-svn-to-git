#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DEBUG 0
static int arr[100][100];
static int ver_sum[100][100];
static int dimen;
static int maxI1, maxI2, maxJ1, maxJ2, maxSum = -128;

void printArr() {
	int i, j;
	printf("Array ==============================\n");
	for (i = 0; i < dimen; i++) {
		for (j = 0; j < dimen; j++) {
			printf("[%2d][%2d]:%2d  ", i, j, arr[i][j]);
		}
		printf("\n");
	}
	printf("Vertical Sum =======================\n");
	for (i = 0; i < dimen; i++) {
		for (j = 0; j < dimen; j++) {
			printf("[%2d][%2d]:%2d  ", i, j, ver_sum[i][j]);
		}
		printf("\n");
	}
}

void initVerSum() {
	int i, j;
	for (i = 0; i < dimen; i++) {
		for (j = 0; j < dimen; j++) {
			if (i == 0) {
				ver_sum[i][j] = arr[i][j];
			} else {
				ver_sum[i][j] = arr[i][j] + ver_sum[i - 1][j];
			}
		}
	}

}

int calHorSubMax(int arr_t[]) {
	int j, result = 0, currMax = 0, currBegin = 0, currEnd = 0;
	if (DEBUG) {
		printf("cal max sub seq of ");
		for (j = 0; j < dimen; j++) {
			printf("%d ", arr_t[j]);
		}
		printf("\n");
	}
	for (currEnd = 0; currEnd < dimen; currEnd++) {
		currMax += arr_t[currEnd];
		if (currMax > maxSum) {
			result = 1;
			maxSum = currMax;
			maxJ1 = currBegin;
			maxJ2 = currEnd;
		}
		if (currMax < 0) {
			currMax = 0;
			currBegin = currEnd + 1;
		}
	}
	return result;

}

void calMax(int i1, int i2) {
	if (DEBUG) {
		printf("i1:%d, i2:%d\n", i1, i2);
	}
	int arr_t[dimen], j;
	if (i1 == i2) {
		for (j = 0; j < dimen; j++) {
			arr_t[j] = arr[i1][j];
		}
	} else if (i1 != i2 && i1 == 0) {
		for (j = 0; j < dimen; j++) {
			arr_t[j] = ver_sum[i2][j];
		}
	} else {
		for (j = 0; j < dimen; j++) {
			arr_t[j] = ver_sum[i2][j] - ver_sum[i1 - 1][j];
		}
	}
	if (calHorSubMax(arr_t) == 1) {
		maxI1 = i1;
		maxI2 = i2;
	}
}

void cal() {
	int i1, i2;
	for (i1 = 0; i1 < dimen; i1++) {
		for (i2 = i1; i2 < dimen; i2++) {
			calMax(i1, i2);
		}
	}
	printf("%d\n", maxSum);
}

int main(int argc, char * argv[]) {
	int i, j, num, rt;
	rt = scanf("%d", &dimen);
	for (i = 0; i < dimen; i++) {
		for (j = 0; j < dimen; j++) {
			rt = scanf("%d", &arr[i][j]);
		}
	}
	initVerSum();
	if (DEBUG) {
		printArr();
	}
	cal();
	if (DEBUG) {
		printf("maxI1:%d, maxI2:%d, maxJ1:%d, maxJ2:%d, maxSum:%d\n", maxI1,
				maxI2, maxJ1, maxJ2, maxSum);
	}

	return 0;
}
