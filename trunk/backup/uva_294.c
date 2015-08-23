#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 102
#define NUL -1

int prime[3401], boolean[31622];

void setPrimeNumbers() {
	int i, primeSize = 0, j;
	for (i = 2; i <= 31622; i++) {
		if (!boolean[i]) {
			prime[primeSize++] = i;
			for (j = i; j <= 31622; j += i) {
				boolean[j] = 1;
			}
		}
	}
}

/**
 * 294
 */
int main(int argc, char * argv[]) {
	int testNum;
	setPrimeNumbers();
	scanf("%d", &testNum);
	for (; testNum > 0; testNum--) {
		int from, to, max = 0, maxDivisor = 0, curr;
		scanf("%d %d", &from, &to);
		if (DEBUG) {
			printf("from %d to %d\n", from, to);
		}

		for (curr = from; curr <= to; curr++) {
			int divisor = 1, i, n = curr;
			for (i = 0; i < 3401 && prime[i] <= n; i++) {
				int count = 0;
				while (n % prime[i] == 0) {
					count++;
					n /= prime[i];
				}
				divisor *= (count + 1);
			}
			if (n > 1)
				divisor *= 2;
			if (divisor > maxDivisor) {
				maxDivisor = divisor;
				max = curr;
			}
		}
		printf("Between %d and %d, %d has a maximum of %d divisors.\n", from, to, max, maxDivisor);
	}
	return 0;
}

