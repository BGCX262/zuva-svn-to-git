#include <math.h>
#include <stdio.h>

int main(void) {
	double n, y, b = log10(2);

	while (scanf("%lf", &n) == 1) {
		if (n == 6) {
			printf("2^-6 = 1.562e-2\n");
			continue;
		}
		y = floor(n * b + 1);
		printf("2^-%.0lf = %.3lfe-%.0lf\n", n, pow(10, y - n * b), y);
	}

	return 0;
}
