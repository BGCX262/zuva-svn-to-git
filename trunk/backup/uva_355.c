#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

void add(char * c1, char * c2) {
	int i, n1, n2, r, b = 0;
	int len1 = strlen(c1);
	int len2 = strlen(c2);
	int len = len1 > len2 ? len1 : len2;

	for (i = 0; i < len; i++) {
		if (i < len1) {
			n1 = c1[i] - '0';
		} else {
			n1 = 0;
		}
		if (i < len2) {
			n2 = c2[i] - '0';
		} else {
			n2 = 0;
		}
		r = n1 + n2 + b;
		if (r > 9) {
			b = 1;
			r -= 10;
		} else {
			b = 0;
		}
		c1[i] = ('0' + r);
	}
	if (b)
		c1[i++] = ('0' + b);
	c1[i] = '\0';
}

void nextBase(int base, char * r) {
	int i;
	char b[256];
	strcpy(b, r);
	r[0] = '0';
	r[1] = '\0';
	for (i = 0; i < base; i++) {
		add(r, b);
	}
}

int getNumber(int base, char c) {
	if (c >= '0' && c <= '9') {
		if (c - '0' >= base)
			return -1;
		return c - '0';
	} else if (c >= 'A' && c <= 'F') {
		if (c - 'A' >= base - 10)
			return -1;
		return 10 + (c - 'A');
	} else
		return -1;

}

void multiply(char * base, int n, char * value) {
	char t[256];
	int i;
	t[0] = '0';
	t[1] = '\0';
	for (i = 0; i < n; i++) {
		add(t, base);
	}
	add(value, t);
}

char getChar(int n) {
	if (n < 10) {
		return '0' + n;
	}

	return 'A' + (n - 10);
}

unsigned long long int strToLong(char * d) {
	unsigned long long int r = 0, base = 1;
	int i;
	for (i = 0; i < strlen(d); i++) {
		if (i == 0) {
			base = 1;
		} else {
			base = base * 10;
		}
		r += ((d[i] - '0') * base);
	}
	return r;
}

void convert(int base, char * d) {
	unsigned long long int n = strToLong(d);
	char t[256];
	int i = 0;
	while (n != 0) {
		unsigned long long int r = (n % base);
		t[i++] = getChar(r);
		n /= base;
	}
	t[i] = '\0';
	strcpy(d, t);
}

int main() {
	int i, j, baseFrom, baseTo;
	char line[256];

	while (fgets(line, 256, stdin) != NULL) {
		char s[12], value[256], base[256];
		int n[12], t, nSize = 0;
		sscanf(line, "%d %d %s", &baseFrom, &baseTo, s);
		for (i = strlen(s) - 1; i >= 0; i--) {
			t = getNumber(baseFrom, s[i]);
			if (t == -1)
				break;
			n[nSize++] = t;
		}

		if (t == -1) {
			printf("%s is an illegal base %d number\n", s, baseFrom);
			continue;
		}
		value[0] = '0';
		value[1] = '\0';

		for (i = 0; i < nSize; i++) {
			if (i == 0) {
				base[0] = '1';
				base[1] = '\0';
			} else {
				nextBase(baseFrom, base);
			}
			multiply(base, n[i], value);
		}

		convert(baseTo, value);
		printf("%s base %d = ", s, baseFrom);
		if (strlen(value) == 0) {
			printf("0");
		} else {
			for (i = strlen(value) - 1; i >= 0; i--) {
				printf("%c", value[i]);
			}
		}
		printf(" base %d\n", baseTo);
	}

	return 0;
}
