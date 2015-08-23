#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

long step, initFloor;
long c1, n1, c2, n2, n;

void ex_gcd(long a, long b, long * d, long * x, long * y) {
	if (b == 0) {
		*x = 1, *y = 0, *d = a;
		return;
	}
	long x1, y1;
	ex_gcd(b, a % b, d, &x1, &y1);
	*x = y1;
	*y = x1 - (a / b) * y1;
}

int check() {
	long gcd, m1, m2;
	ex_gcd(n1, n2, &gcd, &m1, &m2);
	if (n % gcd != 0)
		return 0;
	m1 *= n / gcd, m2 *= n / gcd;
	n2 /= gcd, n1 /= gcd;
	long c = ceil(-(double) m1 / n2), f = floor((double) m2 / n1);
	if (c > f)
		return 0;
	long cost = c1 * n2 - c2 * n1;
	if (cost * c < cost * f)
		step = m1 + n2 * c, initFloor = m2 - n1 * c;
	else
		step = m1 + n2 * f, initFloor = m2 - n1 * f;
	return 1;
}

int main() {
	while (scanf("%ld", &n) != EOF && n != 0) {
		scanf("%ld%ld%ld%ld", &c1, &n1, &c2, &n2);
		if (check())
			printf("%ld %ld\n", step, initFloor);
		else
			printf("failed\n");
	}
	return 0;
}
