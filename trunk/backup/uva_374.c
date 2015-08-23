#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

long long rec(long long base, long long power, long long mod) {
	if (power == 0) {
		return 1;
	}

	if (power == 1) {
		return base;
	}

	if (power % 2) {
		long long p = rec((base * base) % mod, (power - 1) / 2, mod);
		return  ((base % mod) * (p)) % mod;
	} else {
		return rec((base * base) % mod, power / 2, mod);
	}
}

int main() {
	long long base, power, mod;
	while (scanf("%lld %lld %lld", &base, &power, &mod) == 3) {
		printf("%lld\n", rec(base, power, mod));
	}
	return 0;
}
