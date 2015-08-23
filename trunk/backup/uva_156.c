#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

struct Sig {
	char sig[256];
	int sigSize;
	int sigHit[256];
	char word[256];
	int anag;
};

void getSigStr(struct Sig * s) {
	int i;
	int alp[26];
	memset(alp, 0, 26 * sizeof(int));
	int wordSize = strlen(s->word);
	for (i = 0; i < wordSize; i++) {
		if (s->word[i] >= 'a') {
			++alp[s->word[i] - 'a'];
		} else {
			++alp[s->word[i] - 'A'];
		}
	}
	int j = 0;
	for (i = 0; i < 26; i++) {
		if (alp[i] > 0) {
			s->sig[j] = 'a' + i;
			s->sigHit[j] = alp[i];
			++j;
		}
	}
	s->sig[j] = '\0';
	s->sigSize = j;
}

struct Sig * alloc(char * word) {
	struct Sig * s = (struct Sig *) malloc(sizeof(struct Sig));
	strcpy(s->word, word);
	s->anag = 0;
	getSigStr(s);
	return s;
}

int sigcmp(struct Sig * s1, struct Sig * s2) {
	int re = strcmp(s1->sig, s2->sig);
	if (re == 0) {
		int i = 0;
		for (i = 0; i < s1->sigSize; i++) {
			re = s1->sigHit[i] - s2->sigHit[i];
			if (re != 0)
				break;
		}
	}
	return re;
}

int find(struct Sig **all, int allSize, struct Sig * s) {
	int low = 0;
	int high = allSize - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		int re = sigcmp(all[mid], s);
		if (re < 0) {
			low = mid + 1;
		} else if (re > 0) {
			high = mid - 1;
		} else {
			return mid;
		}
	}
	return -1;
}

void printSig(struct Sig * s) {
	printf("%s anagrams:%d ", s->word, s->anag);
	int i;
	for (i = 0; i < s->sigSize; i++) {
		printf("%c", s->sig[i]);
		printf("%d", s->sigHit[i]);
	}

	printf("\n");
}

int partition(struct Sig ** noanag, int left, int right) {
	int pivot = right;
	int i, j;
	for (i = left - 1, j = left; j < right; j++) {
		if (strcmp(noanag[j]->word, noanag[pivot]->word) < 0) {
			/*exchange i+1 and j*/
			++i;
			struct Sig * t = noanag[i];
			noanag[i] = noanag[j];
			noanag[j] = t;
		}
	}
	++i;
	struct Sig * t = noanag[i];
	noanag[i] = noanag[pivot];
	noanag[pivot] = t;
	return i;
}

void quicksort_word(struct Sig ** noanag, int left, int right) {
	if (left < right) {
		int pivot = partition(noanag, left, right);
		quicksort_word(noanag, left, pivot - 1);
		quicksort_word(noanag, pivot + 1, right);
	}
}

int main(int argv, char * argc[]) {
	char word[256];
	struct Sig * allSig[2048];
	int allSigSize = 0;
	while (scanf("%s", word)) {
		if (strcmp(word, "#") == 0)
			break;
		struct Sig * s = alloc(word);
		int in = find(allSig, allSigSize, s);
		if (DEBUG) {
			printf("find:%d for word:%s\n", in, word);
		}
		if (in == -1) {
			allSig[allSigSize] = s;
			++allSigSize;
			int j;
			for (j = allSigSize - 1; j > 0 && sigcmp(allSig[j - 1], allSig[j]) > 0; j--) {
				struct Sig * t = allSig[j];
				allSig[j] = allSig[j - 1];
				allSig[j - 1] = t;
			}
		} else {
			++allSig[in]->anag;
			free(s);
		}

		if (DEBUG) {
			int i;
			for (i = 0; i < allSigSize; i++) {
				printf("%d ", i);
				printSig(allSig[i]);
			}
		}
	}

	struct Sig * noanag[2048];
	int noanagSize = 0;
	int i;
	for (i = 0; i < allSigSize; i++) {
		if (allSig[i]->anag == 0) {
			noanag[noanagSize] = allSig[i];
			++noanagSize;
		}
	}
	quicksort_word(noanag, 0, noanagSize - 1);
	for (i = 0; i < noanagSize; i++) {
		printf("%s\n", noanag[i]->word);
	}

	for (i = 0; i < allSigSize; i++) {
		free(allSig[i]);
	}

	return 0;
}
