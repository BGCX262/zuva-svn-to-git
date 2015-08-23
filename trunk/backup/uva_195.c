#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

/**
 * uva 195
 */
static char word[1024], sol[1024];
static int wordSize, visited[1024];

char getUpperCase(char a) {
	if (a >= 'a') {
		return a - 32;
	}
	return a;
}

int cmp(const void * a, const void * b) {
	char c1 = *(char *) a;
	char c2 = *(char *) b;
	char u1 = getUpperCase(c1);
	char u2 = getUpperCase(c2);
	if (u1 != u2) {
		return u1 - u2;
	} else {
		if ((c1 != u1 && c2 != u2) || (c1 == u1 && c2 == u2)) {
			return 0;
		} else if (c1 != u1 && c2 == u2) {
			return 1;
		} else if (c1 == u1 && c2 != u2) {
			return -1;
		}
	}
}

void permut(int curr) {
	if (curr == wordSize) {
		sol[curr] = '\0';
		printf("%s\n", sol);
		return;
	}
	int i;
	for (i = 0; i < wordSize; i++) {
		if (!visited[i]) {
			if (i > 0 && word[i - 1] == word[i] && !visited[i - 1]) {
				continue;
			} else {
				visited[i] = 1;
				sol[curr] = word[i];
				permut(curr + 1);
				visited[i] = 0;
			}
		}
	}
}

int main() {
	int test;
	char line[1024];
	fgets(line, 1024, stdin);
	for (sscanf(line, "%d", &test); test > 0; test--) {
		int i, j, size;
		wordSize = 0;
		for (i = 0; i < 1024; i++) {
			visited[i] = 0;
		}
		fgets(line, 1024, stdin);
		size = strlen(line);
		for (i = 0; i < size; i++) {
			if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) {
				word[wordSize++] = line[i];
			}
		}
		/**
		 * order the word string
		 */
		qsort(word, wordSize, sizeof(char), cmp);
		permut(0);
	}

	return 0;
}

