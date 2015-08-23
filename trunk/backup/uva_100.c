#include <stdio.h>

int cycle_length(int n) {
	int result = 1;
	while (n != 1) {
		result++;
		if ((n % 2) == 0) {
			n = n / 2;
		} else {
			n = 3 * n + 1;
		}
	}
	return result;
}

int main(int argc, char * argv[]) {
	int m, n, i, max = 0, t, origm, orign;
	while (scanf("%d %d\n", &m, &n) == 2) {
		max = 0;
		origm = m;
		orign = n;
		if (m > n) {
			t = m;
			m = n;
			n = t;
		}
		for (i = m; i <= n; i++) {
			t = cycle_length(i);
			if (t > max) {
				max = t;
			}
		}
		printf("%d %d %d\n", origm, orign, max);
	}
	return 0;
}

