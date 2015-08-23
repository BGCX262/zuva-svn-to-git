#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

static char nodeName[30][2];
static int numNode, numEdge, numReq, path[30][30], MAX_PATH = 9999;

int getNodeIndex(char c1, char c2) {
	int i;
	for (i = 0; i < numNode; i++) {
		if (c1 == nodeName[i][0] && c2 == nodeName[i][1])
			return i;
	}
	return -1;
}

/**
 * 383
 */
int main(int argc, char * argv[]) {
	int numTest, i, j, k, r, test;
	scanf("%d", &numTest);

	printf("SHIPPING ROUTES OUTPUT\n\n");

	for (test = 1; test <= numTest; test++) {

		printf("DATA SET  %d\n\n", test);

		scanf("%d %d %d\n", &numNode, &numEdge, &numReq);
		char line[256];
		fgets(line, 256, stdin);
		for (i = 0; i < 30; i++) {
			for (j = 0; j < 30; j++) {
				path[i][j] = MAX_PATH;
			}
		}

		int nodeNameSize = 0;
		char c1 = '0', c2 = '0';

		for (i = 0; i < strlen(line); i++) {
			if (line[i] == ' ' && c1 != '0') {
				nodeName[nodeNameSize][0] = c1;
				nodeName[nodeNameSize][1] = c2;
				c1 = '0';
				c2 = '0';
				nodeNameSize++;
			} else if (line[i] <= 'Z' && line[i] >= 'A') {
				if (c1 == '0') {
					c1 = line[i];
				} else {
					c2 = line[i];
				}
			}
		}
		nodeName[nodeNameSize][0] = c1;
		nodeName[nodeNameSize][1] = c2;
		nodeNameSize++;

		if (DEBUG) {
			printf("Node name\n");
			for (i = 0; i < numNode; i++) {
				printf("%c%c ", nodeName[i][0], nodeName[i][1]);
			}
			printf("\n");
		}

		for (i = 0; i < numEdge; i++) {
			char line[256];
			fgets(line, 256, stdin);
			int index1 = getNodeIndex(line[0], line[1]);
			int index2 = getNodeIndex(line[3], line[4]);
			path[index1][index2] = 1;
			path[index2][index1] = 1;
		}
		/**
		 * calculate shortest path
		 */
		for (k = 0; k < numNode; k++) {
			for (i = 0; i < numNode; i++) {
				for (j = 0; j < numNode; j++) {
					if (path[i][k] + path[k][j] < path[i][j]) {
						path[i][j] = path[i][k] + path[k][j];
					}
				}
			}
		}

		if (DEBUG) {
			printf("path\n");
			for (i = 0; i < numNode; i++) {
				for (j = 0; j < numNode; j++) {
					printf("%d ", path[i][j]);
				}
				printf("\n");
			}
		}

		for (i = 0; i < numReq; i++) {
			char line[256];
			fgets(line, 256, stdin);
			int sizeOfShip = 0;

			if (DEBUG) {
				printf("line:%s", line);
			}

			char c1 = '0', c2 = '0', c3 = '0', c4 = '0';
			for (j = 0; j < strlen(line); j++) {
				if (line[j] >= '0' && line[j] <= '9') {
					sizeOfShip = sizeOfShip * 10 + (line[j] - '0');
				} else if (line[j] >= 'A' && line[j] <= 'Z') {
					if (c1 == '0') {
						c1 = line[j];
					} else if (c2 == '0') {
						c2 = line[j];
					} else if (c3 == '0') {
						c3 = line[j];
					} else if (c4 == '0') {
						c4 = line[j];
					}
				}
			}

			if (DEBUG) {
				printf("size %d from %c%c to %c%c \n", sizeOfShip, c1, c2, c3, c4);
			}

			int index1 = getNodeIndex(c1, c2);
			int index2 = getNodeIndex(c3, c4);
			if (path[index1][index2] != MAX_PATH) {
				printf("$%d\n", sizeOfShip * 100 * path[index1][index2]);
			} else {
				printf("NO SHIPMENT POSSIBLE\n");
			}
		}
		printf("\n");
	}
	printf("END OF OUTPUT\n");

	return 0;
}
