#include<stdio.h>
#include<string.h>
#define DEBUG 0

int traceLen, counter, carvens[26][26], carvensLen[26], kTh, minotaur, theseus;
char trace[26];

void printCavern() {
	int i, j;
	printf("cavern:\n");
	for (i = 0; i < 26; i++) {
		if (carvensLen[i] > 0) {
			printf("%c %d => ", 'A' + i, i);
			for (j = 0; j < carvensLen[i]; j++) {
				printf("%d ", carvens[i][j]);
			}
			printf("\n");
		}
	}
	printf("minotaur:%c theseus:%c\n", 'A' + minotaur, 'A' + theseus);
}

void setCarvens(char s[]) {
	int i, j, len, begin;
	char from;
	len = strlen(s);
	begin = 0;
	for (i = 0; i < len; i++) {
		if (s[i] == ':') {
			from = s[i - 1];
			begin = 1;
			continue;
		} else if (s[i] == ';') {
			begin = 0;
			continue;
		} else if (s[i] == '.') {
			break;
		}
		if (begin) {
			carvens[from - 'A'][carvensLen[from - 'A']++] = s[i] - 'A';
		}
	}
}

void lightCarven() {
/*	if (DEBUG) {
		printf("light Carven %d:\n", theseus);
	}*/

	int i, j, k;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < carvensLen[i]; j++) {
			if (carvens[i][j] == theseus) {
				k = j;
				while (k < carvensLen[i]) {
					carvens[i][k] = carvens[i][k + 1];
					k++;
				}
				carvensLen[i]--;
				break;
			}
		}
	}

/*	if (DEBUG) {
		printCavern();
	}*/
}

int theseusDFS() {
/*
	if (DEBUG) {
		printCavern();
	}
*/

	if (counter == kTh) {
		lightCarven();
		trace[traceLen++] = 'A' + theseus;
		counter = 0;
	}

	int i, j, trapped = 1;
	for (j = 0; j < carvensLen[minotaur]; j++) {
		if (carvens[minotaur][j] != -1 && carvens[minotaur][j] != theseus) {
			trapped = 0;
			break;
		}
	}
	if (trapped) {
		trace[traceLen++] = 'A' + minotaur;
		return 1;
	}

	for (j = 0; j < carvensLen[minotaur]; j++) {
		if (carvens[minotaur][j] != -1 && carvens[minotaur][j] != theseus) {
			theseus = minotaur;
			minotaur = carvens[minotaur][j];
			counter++;
			if (theseusDFS())
				return 1;
		}
	}
	return 0;
}

int main() {
	int r, i, j, g[26][26];
	char str[256];
	char startTheseus[2], startMinotaur[2];
	for (;;) {
		r = scanf("%s", str);
		if (strcmp(str, "#") == 0)
			break;
		r = scanf("%s", startMinotaur);
		r = scanf("%s", startTheseus);
		r = scanf("%d", &kTh);
		theseus = startTheseus[0] - 'A';
		minotaur = startMinotaur[0] - 'A';
		traceLen = 0;
		counter = 0;
		memset(carvens, -1, sizeof(int) * 26 * 26);
		memset(carvensLen, 0, sizeof(int) * 26);
		setCarvens(str);
		theseusDFS();
		for (i = 0; i < traceLen - 1; i++) {
			printf("%c ", trace[i]);
		}
		printf("/%c\n", trace[traceLen - 1]);
	}
	return 0;
}

