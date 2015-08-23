#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
/**
 * 787
 */
static char result[1024], max[1024];

void multiple(char b[]) {
	int i, j, neg = 0, aSize = 0, bSize = 0;
	if ((result[0] == '-' && b[0] != '-') || (result[0] != '-' && b[0] == '-')) {
		neg = 1;
	}
	int aLen = strlen(result);
	int bLen = strlen(b);
	int intA[aLen], intB[bLen];
	for (i = 0; i < aLen; i++) {
		if (result[i] != '-')
			intA[aSize++] = result[i] - '0';
	}
	for (i = 0; i < bLen; i++) {
		if (b[i] != '-')
			intB[bSize++] = b[i] - '0';
	}

	int tempIndex = 0, r;
	int temp[1024];
	for (i = 0; i < 1024; i++) {
		temp[i] = 0;
	}
	for (i = aSize - 1; i >= 0; i--) {
		r = 0;
		tempIndex = (aSize - 1 - i);
		for (j = bSize - 1; j >= 0; j--) {
			int t = (temp[tempIndex] + intA[i] * intB[j] + r) % 10;
			r = (temp[tempIndex] + intA[i] * intB[j] + r) / 10;
			temp[tempIndex] = t;
			tempIndex++;
		}
		temp[tempIndex] += r;
	}
	int resultIndex = 0;
	if (neg) {
		result[resultIndex++] = '-';
	}
	int begin = 1;
	for (i = tempIndex; i >= 0; i--) {
		if (begin && temp[i] == 0) {
			continue;
		}
		begin = 0;
		result[resultIndex++] = '0' + temp[i];
	}
	result[resultIndex] = '\0';
	if (result[0] == '\0' || (result[0] == '-' && result[1] == '\0')) {
		result[0] = '0';
		result[1] = '\0';
	}
	if (DEBUG) {
		printf("multiple with %s result %s\n", b, result);
	}

}

int compare(char a[], char b[]) {
	int i, j;
	int aLen = strlen(a);
	int bLen = strlen(b);
	if (a[0] == '-' && b[0] != '-') {
		return -1;
	} else if (a[0] != '-' && b[0] == '-') {
		return 1;
	} else if (a[0] != '-' && b[0] != '-') {
		if (aLen != bLen) {
			return aLen - bLen;
		}
		for (i = 0; i < aLen; i++) {
			if (a[i] != b[i]) {
				return a[i] - b[i];
			}
		}
		return 0;

	} else {
		if (aLen != bLen) {
			return bLen - aLen;
		}
		for (i = 0; i < aLen; i++) {
			if (a[i] != b[i]) {
				return b[i] - a[i];
			}
		}
		return 0;
	}
}

int main(int argc, char * argv[]) {
	int i, j;
	char in[128][8], inSize = 0;

	while (scanf("%s", in[inSize]) != EOF) {
		if (strcmp(in[inSize], "-999999") == 0) {
			if (DEBUG) {
				printf("in: ");
				for (i = 0; i < inSize; i++) {
					printf("%s ", in[i]);
				}
				printf("\n");
			}

			strcpy(max, in[0]);
			for (i = 0; i < inSize - 1; i++) {
				strcpy(result, in[i]);
				for (j = i + 1; j < inSize; j++) {
					multiple(in[j]);
					if (compare(result, max) > 0) {
						strcpy(max, result);
					}
				}
			}
			printf("%s\n", max);

			inSize = 0;
			continue;
		}
		inSize++;
	}
	return 0;
}

