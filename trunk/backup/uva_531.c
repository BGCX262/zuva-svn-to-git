#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

char t1[1028][200], t2[1028][200];
int t1Size, t2Size;
int b[1028][200], c[1028][200];
int lcsArr[1028];
int lcsArrSize;

void printDebug() {
	int i;
	printf("t1:\n");
	for (i = 0; i < t1Size; i++) {
		printf("[%d]%s\n", i, t1[i]);
	}
	printf("t2:\n");
	for (i = 0; i < t2Size; i++) {
		printf("[%d]%s\n", i, t2[i]);
	}
}

void lcs() {
	int i, j;

	for (i = 1; i <= t1Size; i++) {
		c[i][0] = 0;
	}
	for (j = 1; j <= t2Size; j++) {
		c[0][j] = 0;
	}

	for (i = 1; i <= t1Size; i++) {
		for (j = 1; j <= t2Size; j++) {
			if (strcmp(t1[i - 1], t2[j - 1]) == 0) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 2;
			} else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 3;
			} else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 1;
			}
		}
	}
}

void print_lcs(int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (b[i][j] == 2) {
		print_lcs(i - 1, j - 1);
		lcsArr[lcsArrSize++] = i - 1;
	} else if (b[i][j] == 3) {
		print_lcs(i - 1, j);
	} else {
		print_lcs(i, j - 1);
	}
}

int main(int argc, char * argv[]) {
	int i, j, n;
	char line[1028];
	char text[1028][200];
	int textSize;
	t1Size = 0;
	t2Size = 0;
	textSize = 0;

	for (; fgets(line, 1028, stdin) != NULL;) {
		if (line[0] == '#') {
			if (t1Size == 0) {
				for (i = 0; i < textSize; i++) {
					strcpy(t1[i], text[i]);
				}
				t1Size = textSize;
			} else {
				for (i = 0; i < textSize; i++) {
					strcpy(t2[i], text[i]);
				}
				t2Size = textSize;

				if (DEBUG)
					printDebug();

				/*begin LCS here*/
				lcs();
				lcsArrSize = 0;
				print_lcs(t1Size, t2Size);
				for (i = 0; i < lcsArrSize; i++) {
					printf("%s", t1[lcsArr[i]]);
					if (i < lcsArrSize - 1) {
						printf(" ");
					}
				}
				printf("\n");

				t1Size = t2Size = 0;
			}
			textSize = 0;
		} else {
			int wordSize = 0;
			for (i = 0; i < strlen(line) - 1; i++) {
				char c = line[i];
				if (isalnum(c)) {
					text[textSize][wordSize++] = c;
				} else {
					if (wordSize > 0) {
						text[textSize++][wordSize] = '\0';
						wordSize = 0;
					}
				}
			}
			if (wordSize > 0) {
				text[textSize++][wordSize] = '\0';
				wordSize = 0;
			}
		}
	}
	return 0;
}
