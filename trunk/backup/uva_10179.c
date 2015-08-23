#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define PRIME_MAX 900000
#define PRIME_NUM_MAX 40000
#define NUL -1

int phi(int n) {
	if (n == 1)
		return 1;
	int re = n, i;
	if (n % 2 == 0) {
		re -= (re / 2);
		while (n % 2 == 0) {
			n /= 2;
		}
	}

	for (i = 3; i * i <= n; i += 2) {
		if (n % i == 0) {
			re -= (re / i);
			while (n % i == 0) {
				n /= i;
			}
		}
	}

	if (n > 1) {
		re -= (re / n);
	}
	return re;
}
int main() {
	int n;
	while (scanf("%d", &n) && n) {
		printf("%d\n", phi(n));
	}
	return 0;
}

