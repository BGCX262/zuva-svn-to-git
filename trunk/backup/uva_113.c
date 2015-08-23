#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0

int main(int argc, char * argv[]) {
	long double p = 0, n = 0, k = 0, in = 0;
	while (scanf("%Lf", &in) != EOF) {
		if (n == 0) {
			n = in;
		} else {
			p = in;
			k = log(p);
			k /= n;
			k = exp(k);
			printf("%.0Lf\n", k);
			n = 0;
			p = 0;
		}
	}
	return 0;
}
