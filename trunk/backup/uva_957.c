#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

#define max(a,b) (a>b)?a:b

int main() {
	int y, i, j, first, last, max, n;
	while (scanf("%d", &y) != EOF) {
		y--;
		int p;
		scanf("%d", &p);
		int a[p];
		for (i = 0; i < p; i++)
			scanf("%d", &a[i]);
		max = 0;
		for (i = 0; i < p; i++) {
			n = 0;
			for (j = i; j < p; j++) {
				if (a[j] - a[i] <= y) {
					n++;
				} else {
					break;
				}
			}
			if (max == 0 || n > max) {
				max = n;
				first = a[i];
				last = a[j - 1];
			}
		}
		printf("%d %d %d\n", max, first, last);
	}
	return 0;
}
