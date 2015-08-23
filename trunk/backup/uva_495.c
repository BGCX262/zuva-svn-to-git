#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define MAX 5001

char * fib[MAX];

char * add(char * c1, char * c2) {
	int len1, len2, len, i, n1, n2, b = 0, n;
	char * c;
	len1 = strlen(c1);
	len2 = strlen(c2);
	len = len1 > len2 ? len1 : len2;
	c = malloc(len + 2);

	for (i = 0; i < len; i++) {
		if (i < len1) {
			n1 = c1[i] - '0';
		} else {
			n1 = 0;
		}
		if (i < len2) {
			n2 = c2[i] - '0';
		} else {
			n2 = 0;
		}
		n = n1 + n2 + b;
		if (n > 9) {
			b = 1;
			n -= 10;
		} else {
			b = 0;
		}
		c[i] = ('0' + n);
	}
	if (b)
		c[i++] = ('0' + b);
	c[i] = '\0';
	return c;
}

int main() {
	int i, j;
	char buffer[256];
	fib[0] = malloc(sizeof(char) * 2);
	fib[0][0] = '0';
	fib[0][1] = '\0';
	fib[1] = malloc(sizeof(char) * 2);
	fib[1][0] = '1';
	fib[1][1] = '\0';

	for (i = 2; i < MAX; i++) {
		fib[i] = add(fib[i - 2], fib[i - 1]);
	}

	while (fgets(buffer, 256, stdin) != NULL) {
		i = atoi(buffer);
		printf("The Fibonacci number for %d is ", i);
		for (j = strlen(fib[i]) - 1; j >= 0; j--) {
			printf("%c", fib[i][j]);
		}
		printf("\n");
	}

	return 0;
}
