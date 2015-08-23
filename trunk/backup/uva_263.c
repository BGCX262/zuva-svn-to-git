#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

int chain[5001], chainSize;

int descend(int n) {
	char c[10];
	int cSize = 0;
	if (n == 0)
		return 0;

	while (n != 0) {
		int d = n - (n / 10) * 10;
		c[cSize++] = '0' + d;
		n /= 10;
	}

	int i, j;
	for (i = 0; i < cSize - 1; i++) {
		int pivot = c[i] - '0';
		int pivotIndex = i;
		for (j = i + 1; j < cSize; j++) {
			int t = c[j] - '0';
			if (t > pivot) {
				pivotIndex = j;
				pivot = t;
			}
		}
		char cTemp = c[i];
		c[i] = c[pivotIndex];
		c[pivotIndex] = cTemp;
	}

	int re = 0;
	for (i = 0; i < cSize; i++) {
		int t = cSize - 1 - i;
		int base = 1;
		for (j = 0; j < t; j++) {
			base *= 10;
		}
		re += ((c[i] - '0') * base);
	}
	return re;
}

int ascend(int n) {
	char c[10];
	int cSize = 0;
	if (n == 0)
		return 0;

	while (n != 0) {
		int d = n - (n / 10) * 10;
		c[cSize++] = '0' + d;
		n /= 10;
	}

	int i, j;
	for (i = 0; i < cSize - 1; i++) {
		int pivot = c[i] - '0';
		int pivotIndex = i;
		for (j = i + 1; j < cSize; j++) {
			int t = c[j] - '0';
			if (t < pivot) {
				pivotIndex = j;
				pivot = t;
			}
		}
		char cTemp = c[i];
		c[i] = c[pivotIndex];
		c[pivotIndex] = cTemp;
	}

	int re = 0;
	for (i = 0; i < cSize; i++) {
		int t = cSize - 1 - i;
		int base = 1;
		for (j = 0; j < t; j++) {
			base *= 10;
		}
		re += ((c[i] - '0') * base);
	}
	return re;

}

int main(int argc, char * argv[]) {
	int i, j, n;
	for (;;) {
		scanf("%d", &n);
		if (n == 0)
			break;
		chainSize = 0;
		printf("Original number was %d\n", n);

		for (;;) {
			int desc = descend(n);
			int asc = ascend(n);
			int sub = (desc - asc);
			chain[chainSize++] = sub;
			printf("%d - %d = %d\n", desc, asc, sub);
			n = sub;
			if (chainSize == 1)
				continue;
			int found = 0;
			for (i = 0; i < chainSize - 1; i++) {
				if (chain[i] == chain[chainSize - 1]) {
					found = 1;
					break;
				}
			}
			if (found)
				break;
		}
		printf("Chain length %d\n\n", chainSize);

	}
	return 0;
}
