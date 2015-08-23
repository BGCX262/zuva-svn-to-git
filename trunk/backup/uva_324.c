#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 1

char fat[367][783];

void add(int n) {
	int i, n1, n2, r, b = 0;
	int len1 = strlen(fat[n - 1]);
	int len2 = strlen(fat[n]);
	int len = len1 > len2 ? len1 : len2;

	for (i = 0; i < len; i++) {
		if (i < len1) {
			n1 = fat[n - 1][i] - '0';
		} else {
			n1 = 0;
		}
		if (i < len2) {
			n2 = fat[n][i] - '0';
		} else {
			n2 = 0;
		}
		r = n1 + n2 + b;
		if (r > 9) {
			b = 1;
			r -= 10;
		} else {
			b = 0;
		}
		fat[n][i] = ('0' + r);
	}
	if (b)
		fat[n][i++] = ('0' + b);
	fat[n][i] = '\0';
}

void calculateFactorial() {
	int i, j;
	char * c;
	fat[1][0] = '1';
	fat[1][1] = '\0';

	for (i = 2; i <= 366; i++) {
		for (j = 0; j < i; j++) {
			add(i);
		}
	}
}

int main() {
	int i, j;
	calculateFactorial();

	for (scanf("%d", &i); i != 0; scanf("%d", &i)) {
		int cn[10];
		memset(cn, 0, 10 * sizeof(int));
		int len = strlen(fat[i]);
		for (j = 0; j < len; j++) {
			cn[fat[i][j] - '0']++;
		}

		printf("%d! --\n", i);
		printf("   (0)%5d    (1)%5d    (2)%5d    (3)%5d    (4)%5d\n", cn[0], cn[1], cn[2], cn[3], cn[4]);
		printf("   (5)%5d    (6)%5d    (7)%5d    (8)%5d    (9)%5d\n", cn[5], cn[6], cn[7], cn[8], cn[9]);
	}

	return 0;
}
