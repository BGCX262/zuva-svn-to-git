#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

#define MAX_CHAR 60000

struct Infringe {
	int from, len;
};

struct Infringe infringes[MAX_CHAR];
char tdp[MAX_CHAR], jcn[MAX_CHAR];
int tdpSize, jcnSize, tdpSuffixSize, tdpSuffix[MAX_CHAR], infringesSize;

int infringe_cmp(const void * a, const void * b) {
	struct Infringe * i1 = (struct Infringe *) a;
	struct Infringe * i2 = (struct Infringe *) b;

	if (i1->len > i2->len) {
		return -1;
	} else if (i1->len < i2->len) {
		return 1;
	} else {
		if (i1->from < i2->from) {
			return -1;
		} else if (i1->from > i2->from) {
			return 1;
		} else {
			return 0;
		}
	}
}

int tdpSuffix_cmp(const void * a, const void * b) {
	int c1 = *(int*) a;
	int c2 = *(int*) b;

	return strcmp(tdp + c1, tdp + c2);
}

void makeTdpSuffixArr() {
	int i, j;
	for (i = 0; i < tdpSize - 1; i++) {
		tdpSuffix[i] = i;
	}
	tdpSuffixSize = tdpSize - 1;

	qsort(tdpSuffix, tdpSuffixSize, sizeof(int), tdpSuffix_cmp);
}
/**
 * -1 = tdpSuffix is less than jcn string, or jcn string is including tdpSuffix
 *  0 = tdpSuffix is including jcn string
 *  1 = tdpSuffix is larger than jcn string
 */
int tdp_cmp(int tdpFrom, int jcnFrom, int jcnTo) {
	int tdpTo = tdpFrom + (jcnTo - jcnFrom);
	if (jcnTo - jcnFrom > tdpSize - 1 - tdpFrom) {
		tdpTo = tdpSize - 1;
	}
	int i;
	for (i = 0; (i + tdpFrom) <= tdpTo; i++) {
		int re = tdp[tdpFrom + i] - jcn[jcnFrom + i];
		if (re > 0) {
			return 1;
		} else if (re < 0) {
			return -1;
		}
	}
	if (jcnTo - jcnFrom > tdpSize - 1 - tdpFrom) {
		return -1;
	} else {
		return 0;
	}
}

/**
 * 1 = find
 * 0 = not find
 */
int binary_search_tdpSuffix(int jcnFrom, int jcnTo) {
	int low = 0, high = tdpSuffixSize - 1;

	while (low <= high) {
		int middle = low + (high - low) / 2;
		int re = tdp_cmp(tdpSuffix[middle], jcnFrom, jcnTo);
		/*
		 if (DEBUG) {
		 printf("low %d high %d middle %d re %d\n", low, high, middle, re);
		 }*/

		if (re == 1)
			high = middle - 1;
		else if (re == -1)
			low = middle + 1;
		else if (re == 0)
			return 1;
	}
	return 0;
}

int isI1SubStringOfI2(int from1, int len1, int from2, int len2) {
	/*
	 if (DEBUG) {
	 printf("isI1SubStringOfI2 from1 %d len1 %d from2 %d len2 %d\n", from1, len1, from2, len2);
	 }*/

	if (len1 > len2 || from1 < from2 || from2 + len2 - 1 < from1)
		return 0;
	int i2, i1;
	for (i2 = 0; i2 < len2; i2++) {
		if (jcn[from2 + i2] == jcn[from1]) {
			int isMatch = 1;
			for (i1 = 1; i1 < len1; i1++) {
				if (from2 + i2 + i1 > from2 + len2 - 1) {
					isMatch = 0;
					break;
				}

				if (jcn[from2 + i2 + i1] != jcn[from1 + i1]) {
					isMatch = 0;
					break;
				}
			}
			if (isMatch && len1 != len2)
				return 1;
		}

	}
	return 0;
}

void makeInfringes() {
	int i, j, m, n, find;
	for (i = 0; i < jcnSize; i++) {
		find = 0;
		for (j = i; j < jcnSize; j++) {

			/*if (DEBUG) {
			 printf("binary search [");
			 int d = 0;
			 for (d = i; d <= j; d++) {
			 printf("%c", jcn[d]);
			 }
			 printf("]\n");
			 }*/

			find = binary_search_tdpSuffix(i, j);

			/*if (DEBUG) {
			 printf("get binary search result %d\n", find);
			 }*/

			if (!find)
				break;

			int from = i;
			int len = j - i + 1;
			int newOne = 1;
			int isNull = 1;

			for (m = 0; m < len; m++) {
				if (jcn[from + m] != ' ' && jcn[from + m] != '\n' && jcn[from + m] != '\r') {
					isNull = 0;
					break;
				}
			}

			if (isNull)
				continue;

			for (m = 0; m < infringesSize; m++) {
				if (isI1SubStringOfI2(from, len, infringes[m].from, infringes[m].len)) {
					if (DEBUG) {
						printf("infringe %d len %d is substring of %d len %d\n", from, len, infringes[m].from, infringes[m].len);
					}

					newOne = 0;
					break;
				} else if (isI1SubStringOfI2(infringes[m].from, infringes[m].len, from, len)) {

					if (DEBUG) {
						printf("infringe %d len %d is including str %d len %d\n", from, len, infringes[m].from, infringes[m].len);
					}
					newOne = 0;
					infringes[m].from = from;
					infringes[m].len = len;
					break;
				}
			}
			if (newOne) {

				if (DEBUG) {
					printf("infringe add %d len %d\n", from, len);
				}

				infringes[infringesSize].from = from;
				infringes[infringesSize].len = len;
				infringesSize++;
			}
		}
	}

	qsort(infringes, infringesSize, sizeof(struct Infringe), infringe_cmp);
}

void print_debug() {
	int i, j;
	printf("tdp:\n");
	for (i = 0; i < tdpSize; i++) {
		printf("%c", tdp[i]);
	}
	printf("jcn:\n");
	for (i = 0; i < jcnSize; i++) {
		printf("[%d]%c\n", i, jcn[i]);
	}
	printf("\n");
	printf("tdpSufix:\n");
	for (i = 0; i < tdpSuffixSize; i++) {
		printf("[%d]%d %s\n", i, tdpSuffix[i], tdp + tdpSuffix[i]);
	}

	printf("infringes:\n");
	for (i = 0; i < infringesSize; i++) {
		printf("from %d len %d ", infringes[i].from, infringes[i].len);
		for (j = 0; j < infringes[i].len; j++) {
			printf("%c", jcn[infringes[i].from + j]);
		}
		printf("\n");
	}
}

int main(int argc, char * argv[]) {
	int i, j, n, k, startTdp, test = 0;

	/*for(i=0;i<MAX_CHAR;i++) {
	 printf("1");
	 }
	 return 1;*/

	char line[MAX_CHAR];
	char beginTdp[] = "BEGIN TDP CODEBASE\r\n";
	char endTdp[] = "END TDP CODEBASE\r\n";
	char beginJcn[] = "BEGIN JCN CODEBASE\r\n";
	char endJcn[] = "END JCN CODEBASE\r\n";

	for (;;) {
		test++;
		scanf("%d\n", &k);
		if (k == 0) {
			break;
		}
		startTdp = 1;
		tdpSuffixSize = tdpSize = jcnSize = infringesSize = 0;

		for (;;) {
			fgets(line, MAX_CHAR, stdin);

			/*printf("line:%s", line);*/

			if (strcmp(line, beginTdp) == 0) {
				startTdp = 1;
			} else if (strcmp(line, endTdp) == 0 || strcmp(line, beginJcn) == 0) {
				startTdp = 0;
			} else if (strcmp(line, endJcn) == 0) {
				tdp[tdpSize++] = '\0';

				makeTdpSuffixArr();

				makeInfringes();

				if (DEBUG)
					print_debug();

				if (test > 1) {
					printf("\n");
				}
				printf("CASE %d\n", test);
				int printSize = (k < infringesSize ? k : infringesSize);
				for (i = 0; i < printSize; i++) {
					printf("INFRINGING SEGMENT %d LENGTH %d POSITION %d\n", i + 1, infringes[i].len, infringes[i].from);
					for (j = 0; j < infringes[i].len; j++) {
						printf("%c", jcn[infringes[i].from + j]);
					}
					printf("\n");
				}

				break;
			} else {
				if (startTdp) {
					for (i = 0; i < strlen(line); i++) {
						if (line[i] != '\r')
							tdp[tdpSize++] = line[i];
					}
				} else {
					for (i = 0; i < strlen(line); i++) {
						if (line[i] != '\r')
							jcn[jcnSize++] = line[i];
					}
				}
			}
		}
	}
	return 0;
}
