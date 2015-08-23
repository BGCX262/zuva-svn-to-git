#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * uva 494
 */
int main() {
	int i, n, startWord;
	char line[256];
	for (; fgets(line, 1028, stdin) != NULL;) {
		n = 0;
		startWord = 0;
		for (i = 0; i < strlen(line); i++) {
			char c = line[i];
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
				if (!startWord) {
					startWord = 1;
				}
			} else {
				if (startWord)
					n++;
				startWord = 0;
			}
		}
		printf("%d\n", n);
	}
	return 0;
}

