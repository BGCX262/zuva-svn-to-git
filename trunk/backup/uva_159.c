#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int findCom(char hword[], char vword[], int * hId, int * vId) {
	int i, j;
	for (i = 0; i < strlen(hword); i++) {
		for (j = 0; j < strlen(vword); j++) {
			if (hword[i] == vword[j]) {
				*hId = i;
				*vId = j;
				return 1;
			}
		}
	}
	return 0;
}

int main(int argv, char * argc[]) {
	int pair;
	for (pair = 0;; pair++) {
		int r, hId1, hId2, vId1, vId2;
		char hword1[32], vword1[32], hword2[32], vword2[32];
		char panel[32][68];
		int rowSize, colSize, row, i, j, id1, id2;

		r = scanf("%s", hword1);
		if (strcmp(hword1, "#") == 0)
			break;
		r = scanf("%s", vword1);
		r = scanf("%s", hword2);
		r = scanf("%s", vword2);

		if (pair > 0)
			printf("\n");
		if (findCom(hword1, vword1, &hId1, &vId1) == 0 || findCom(hword2, vword2, &hId2, &vId2) == 0) {
			printf("Unable to make two crosses\n");
			continue;
		}
		if (DEBUG) {
			memset(panel, '\'', 32 * 68 * sizeof(char));
		} else {
			memset(panel, ' ', 32 * 68 * sizeof(char));
		}
		rowSize = (vId1 > vId2 ? vId1 : vId2) + ((strlen(vword1) - 1 - vId1) > (strlen(vword2) - 1 - vId2) ? (strlen(vword1) - 1 - vId1) : (strlen(vword2) - 1
				- vId2)) + 1;
		colSize = strlen(hword1) + 3 + strlen(hword2);

		row = vId1 > vId2 ? vId1 : vId2;
		for (i = 0, id1 = 0, id2 = 0; i < strlen(hword1) + 3 + strlen(hword2); i++) {
			if (i < strlen(hword1)) {
				panel[row][i] = hword1[id1++];
			} else if (i > strlen(hword1) + 2) {
				panel[row][i] = hword2[id2++];
			}
		}

		for (i = row - vId1, id1 = 0; i < strlen(vword1) + row - vId1; i++) {
			panel[i][hId1] = vword1[id1++];
		}

		for (i = row - vId2, id2 = 0; i < strlen(vword2) + row - vId2; i++) {
			panel[i][hId2 + strlen(hword1) + 3] = vword2[id2++];
		}

		for (i = 0; i < rowSize; i++) {
			int lastWord = 0;
			for (j = 0; j < colSize; j++) {
				if (panel[i][j] != ' ')
					lastWord = j;
			}
			panel[i][lastWord + 1] = '\n';
		}

		for (i = 0; i < rowSize; i++) {
			for (j = 0; j < colSize + 1; j++) {
				printf("%c", panel[i][j]);
				if (panel[i][j] == '\n')
					break;
			}

		}

		if (DEBUG) {
			printf("%s and %s 's comm is %c at %d %d\n", hword1, vword1, hword1[hId1], hId1, vId1);
			printf("%s and %s 's comm is %c at %d %d\n", hword2, vword2, hword2[hId2], hId2, vId2);
			printf("row size %d and col size %d\n", rowSize, colSize);
		}
	}
	return 0;
}
