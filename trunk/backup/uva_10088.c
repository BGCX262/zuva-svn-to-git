#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define EPS 0.000000001
#define PI 3.141592653589793
#define EARTH_RAD 6378

#include <stdio.h>
#include <stdlib.h>
struct Pt {
	long long x, y;
};
long long gcd(long long x, long long y) {
	if (x == 0)
		return y;
	if (y == 0)
		return x;
	long long t;
	while (x % y)
		t = x, x = y, y = t % y;
	return y;
}

/**
 * uva 10088 , Pick's theorem
 */
int main() {
	int n, i;
	struct Pt D[1005];
	while (scanf("%d", &n) == 1 && n) {
		for (i = 0; i < n; i++)
			scanf("%lld %lld", &D[i].x, &D[i].y);
		D[n] = D[0];
		long long area = 0, b = 0;
		for (i = 0; i < n; i++)
			area += (D[i].x * D[i + 1].y) - (D[i].y * D[i + 1].x);
		if (area < 0)
			area = -area;
		for (i = 0; i < n; i++)
			b += gcd(llabs(D[i].x - D[i + 1].x), llabs(D[i].y - D[i + 1].y)) - 1;
		b += n;
		printf("%lld\n", (area + 2 - b) / 2);
	}
	return 0;
}

