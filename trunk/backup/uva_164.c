//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define DEBUG 0
///**
// * lcs1 for string 1 which longest common sequence position,
// */
//int lcs1[32], lcs2[32];
//int str1Len, str2Len;
//char str1[32], str2[32];
//
///**
// * for lcsDir, 0 = left, 1 = upleft, 2 = up
// */
//int lcsLen[32][32], lcsDir[32][32];
//
//void findLCS(int i, int j) {
//	if (i == 0 || j == 0)
//		return;
//	if (lcsDir[i][j] == 1) {
//		lcs1[i - 1] = 1;
//		lcs2[j - 1] = 1;
//		findLCS(i - 1, j - 1);
//	} else if (lcsDir[i][j] == 2) {
//		findLCS(i - 1, j);
//	} else {
//		findLCS(i, j - 1);
//	}
//}
//
//void findLCSLen() {
//	int i, j;
//	for (i = 1; i <= str2Len; i++) {
//		lcsLen[0][i] = 0;
//	}
//	for (i = 1; i <= str1Len; i++) {
//		lcsLen[i][0] = 0;
//	}
//	for (i = 1; i <= str1Len; i++) {
//		for (j = 1; j <= str2Len; j++) {
//			if (str1[i - 1] == str2[j - 1]) {
//				lcsLen[i][j] = lcsLen[i - 1][j - 1] + 1;
//				lcsDir[i][j] = 1;
//			} else if (lcsLen[i - 1][j] >= lcsLen[i][j - 1]) {
//				lcsLen[i][j] = lcsLen[i - 1][j];
//				lcsDir[i][j] = 2;
//			} else {
//				lcsLen[i][j] = lcsLen[i][j - 1];
//				lcsDir[i][j] = 0;
//			}
//		}
//	}
//}
//
//void printLCS() {
//	int i;
//	printf("str1:%s\n", str1);
//	printf("LCS1:");
//	for (i = 0; i < str1Len; i++) {
//		printf("%d", lcs1[i]);
//	}
//	printf("\n");
//	printf("str2:%s\n", str2);
//	printf("LCS2:");
//	for (i = 0; i < str2Len; i++) {
//		printf("%d", lcs2[i]);
//	}
//	printf("\n");
//}
//
//int main() {
//	int i, j, r, idx;
//	for (;;) {
//		for (i = 0; i < 32; i++) {
//			lcs1[i] = 0;
//			lcs2[i] = 0;
//		}
//		str1Len = 0;
//		str2Len = 0;
//		r = scanf("%s%s", str1, str2);
//		if (r == 1 && strcmp(str1, "#") == 0)
//			break;
//		str1Len = strlen(str1);
//		str2Len = strlen(str2);
//		findLCSLen();
//		findLCS(str1Len, str2Len);
//
//		i = 0;
//		j = 0;
//
//		while (i < strlen(str1) && j < strlen(str2)) {
//
//			if (DEBUG) {
//				printLCS();
//				printf("i:%d, j:%d\n",i,j);
//			}
//
//			if (lcs1[i] == 1 && lcs2[j] == 1) {
//				i++;
//				j++;
//			} else if (lcs1[i] == 1 && lcs2[j] == 0) {
//				/**
//				 * insert a str2 char to str1
//				 */
//				printf("I%c", str2[j]);
//				if (i + 1 < 10) {
//					printf("0");
//				}
//				printf("%d", i + 1);
//				int len = strlen(str1);
//				for (idx = len; idx > i; idx--) {
//					str1[idx] = str1[idx - 1];
//					lcs1[idx] = lcs1[idx - 1];
//				}
//				str1[idx] = str2[j];
//				str1[len] = '\0';
//				lcs1[idx] = lcs2[j];
//				i++;
//				j++;
//				if (DEBUG) {
//					printf("\n");
//				}
//			} else if (lcs1[i] == 0 && lcs2[j] == 1) {
//				/**
//				 * delete a str1 char
//				 */
//				printf("D%c", str1[i]);
//				if (i + 1 < 10) {
//					printf("0");
//				}
//				printf("%d", i + 1);
//				int len = strlen(str1);
//				for (idx = i; idx < len - 1; idx++) {
//					str1[idx] = str1[idx + 1];
//					lcs1[idx] = lcs1[idx + 1];
//				}
//				str1[idx] = '\0';
//				lcs1[idx] = 0;
//				if (DEBUG) {
//					printf("\n");
//				}
//			} else if (lcs1[i] == 0 && lcs2[j] == 0) {
//				/**
//				 * replace str1 char with str2 char
//				 */
//				printf("C%c", str2[j]);
//				if (i + 1 < 10) {
//					printf("0");
//				}
//				printf("%d", i + 1);
//				str1[i] = str2[j];
//				lcs1[i] = lcs2[j];
//				i++;
//				j++;
//				if (DEBUG) {
//					printf("\n");
//				}
//			}
//		}
//		if (i >= strlen(str1) && j < strlen(str2)) {
//			/*
//			 * append all the rest of str2 to str1
//			 */
//			for (idx = j; idx < strlen(str2); idx++) {
//				printf("I%c", str2[idx]);
//				if (i + 1 < 10) {
//					printf("0");
//				}
//				printf("%d", i + 1);
//				i++;
//			}
//		} else if (i < strlen(str1) && j >= strlen(str2)) {
//			/*
//			 * delete all rest of str1
//			 */
//			for (idx = i; idx < strlen(str1); idx++) {
//				printf("D%c", str1[i]);
//				if (i + 1 < 10) {
//					printf("0");
//				}
//				printf("%d", i + 1);
//			}
//		}
//
//		printf("E\n");
//	}
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
/**
 * edit Distance
 */
int ed[32][32];
int str1Len, str2Len;
char str1[32], str2[32];

void printEditDist() {
	int i, j;
	printf("str1:%s\n", str1);
	printf("str2:%s\n", str2);
	printf("editDist:\n");
	for (i = 0; i <= str1Len; i++) {
		for (j = 0; j <= str2Len; j++) {
			printf("%d ", ed[i][j]);
		}
		printf("\n");
	}
}

int min(int x, int y, int z) {
	if (x <= y && x <= z)
		return x;
	if (y <= x && y <= z)
		return y;
	if (z <= x && z <= y)
		return z;
}

int backTrack(int i, int j) {
	int r = 1;
	if (i == 0 && j == 0) {
		return r;
	}

	if (j == 0) {
		r = backTrack(i - 1, 0);
		if (DEBUG) {
			printf("D:%c\n", str1[i - 1]);
		} else {
			printf("D%c", str1[i - 1]);
			if (r < 10) {
				printf("0");
			}
			printf("%d", r);
		}
		return r;
	}
	if (i == 0) {
		r = backTrack(0, j - 1);
		if (DEBUG) {
			printf("I:%c\n", str2[j - 1]);
		} else {
			printf("I%c", str2[j - 1]);
			if (r < 10) {
				printf("0");
			}
			printf("%d", r);
		}
		return r + 1;
	}
	if (ed[i - 1][j - 1] <= ed[i - 1][j] && ed[i - 1][j - 1] <= ed[i][j - 1]) {
		/**
		 * no change
		 */
		r = backTrack(i - 1, j - 1);
		if (ed[i - 1][j - 1] < ed[i][j]) {
			if (DEBUG) {
				printf("C:%c to %c\n", str1[i - 1], str2[j - 1]);
			} else {
				printf("C%c", str2[j - 1]);
				if (r < 10) {
					printf("0");
				}
				printf("%d", r);
			}
		}
		return r + 1;
	}
	if (ed[i - 1][j] <= ed[i][j - 1]) {
		/**
		 * delete
		 */
		r = backTrack(i - 1, j);
		if (DEBUG) {
			printf("D:%c\n", str1[i - 1]);
		} else {
			printf("D%c", str1[i - 1]);
			if (r < 10) {
				printf("0");
			}
			printf("%d", r);
		}
		return r;
	}
	r = backTrack(i, j - 1);
	if (DEBUG) {
		printf("I:%c\n", str2[j]);
	} else {
		printf("I%c", str2[j - 1]);
		if (r < 10) {
			printf("0");
		}
		printf("%d", r);
	}
	return r + 1;
}

void editDistance() {
	int i, j;
	for (i = 0; i <= str1Len; i++) {
		ed[i][0] = i;
	}
	for (j = 0; j <= str2Len; j++) {
		ed[0][j] = j;
	}
	for (i = 1; i <= str1Len; i++) {
		for (j = 1; j <= str2Len; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				/**
				 * no change
				 */
				ed[i][j] = ed[i - 1][j - 1];
			} else {
				ed[i][j] = min(ed[i - 1][j], ed[i][j - 1], ed[i - 1][j - 1]) + 1;
			}
		}
	}
	if (DEBUG) {
		printEditDist();
	}

}

int main() {
	int i, j, r, idx;
	for (;;) {
		for (i = 0; i < 32; i++) {
			for (j = 0; j < 32; j++) {
				ed[i][j] = 0;
			}
		}
		str1Len = 0;
		str2Len = 0;
		r = scanf("%s%s", str1, str2);
		if (strcmp(str1, "#") == 0)
			break;
		str1Len = strlen(str1);
		str2Len = strlen(str2);
		editDistance();
		backTrack(str1Len, str2Len);
		printf("E\n");
	}
	return 0;
}
