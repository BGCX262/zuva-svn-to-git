#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

int minimum_expression(char *s, int len) {
	if (DEBUG)
		printf("s:%s, size:%d\n", s, len);

	int i = 0, j = 1, k = 0, t;
	while (i < len && j < len && k < len) {
		t = s[(i + k) % len] - s[(j + k) % len];
		if (t == 0)
			k++;
		else {
			if (t > 0)
				i += k + 1;
			else
				j += k + 1;
			if (i == j)
				j++;
			k = 0;
		}
	}
	return i;
}

int main(int argc, char * argv[]) {
	int i, j, n;
	char line[10001];
	scanf("%d", &n);
	getchar();
	for (; n > 0; n--) {
		gets(line);
		printf("%d\n", minimum_expression(line, strlen(line)) + 1);
	}
	return 0;
}
