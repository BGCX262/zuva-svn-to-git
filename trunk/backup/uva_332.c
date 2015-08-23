#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 102
#define NUL -1

long gcd(long p, long q) {
	long m;
	while (p != 0) {
		m = p;
		p = q % p;
		q = m;
	}
	return q;
}

int main() {
	int i, j, k;
	double d;
	long p, q, m;
	char buf[15];
	int ct = 1;
	int pos;
	while (1) {
		scanf("%d", &j);
		if (j == -1)
			break;
		scanf("%s", buf);
		k = strlen(buf) - j;
		for (pos = 0; buf[pos] != '.' && buf[pos] != 0; pos++)
			;
		k -= pos + 1;
		p = atol(buf + pos + 1);
		if (!j)
			m = 0;
		else {
			m = p;
			for (i = 0; i < j; m /= 10, i++)
				;
		}
		p -= m;
		if (!j)
			q = 1;
		else
			q = 0;
		for (i = 0; i < j; i++)
			q = q * 10 + 9;
		for (i = 0; i < k; i++)
			q *= 10;
		m = gcd(q, p);
		printf("Case %d: %ld/%ld\n", ct, p / m, q / m);
		ct++;
	}

	return 0;
}

