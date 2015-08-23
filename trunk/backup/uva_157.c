#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
struct Station {
	char route;
	char name;
	int left;
	int right;
};

struct Station * alloc(char r, char s) {
	struct Station * n = (struct Station *) malloc(sizeof(struct Station));
	n->route = r;
	n->name = s;
	n->left = -1;
	n->right = -1;
	return n;
}

static struct Station * S[26 * 26];
static int sSize = 0;
/**
 * station distance matrix
 */
static int SD[26 * 26][26 * 26];
/**
 * station pre relation matrix
 */
static int SP[26 * 26][26 * 26];
static struct Station * IC[26 * 26][26 * 26];
static int ICRowSize = 0;
static int ICColSize[26 * 26];

int getStation(char r, char n) {
	int i = -1;
	for (i = 0; i < sSize; i++) {
		if (S[i]->route == r && S[i]->name == n) {
			return i;
		}
	}
	return i;
}

void printInfo() {
	int i, j;
	printf("stations\n");
	for (i = 0; i < sSize; i++) {
		if (S[i]->left != -1 || S[i]->right != -1)
			printf("[%d]%c%c(%d%d) ", i, S[i]->route, S[i]->name, S[i]->left, S[i]->right);
		else
			printf("[%d]%c%c ", i, S[i]->route, S[i]->name);
		if (i % 10 == 0 && i > 0)
			printf("\n");
	}
	printf("\n");
	printf("station distance\n");
	for (i = 0; i < sSize; i++) {
		for (j = 0; j < sSize; j++) {
			if (SD[i][j] > -1)
				printf("[%d][%d]%d ", i, j, SD[i][j]);
		}
	}
	printf("\n");
	printf("station pre\n");
	for (i = 0; i < sSize; i++) {
		for (j = 0; j < sSize; j++) {
			if (SP[i][j] != -1)
				printf("[%d][%d]%d ", i, j, SP[i][j]);
		}
	}
	printf("\n");
}

void setDistanceMatrix() {
	int i, j;
	for (i = 0; i < sSize; i++) {
		/*
		 * set 0 to self distance
		 */
		SD[i][i] = 0;
		SP[i][i] = i;
	}

	for (i = 0; i < sSize; i++) {
		/*
		 * set left station relation
		 */
		if (S[i]->left != -1) {
			SD[i][i + S[i]->left] = 1;
			SP[i][i + S[i]->left] = i;
		} else {
			if (i > 0 && S[i - 1]->route == S[i]->route) {
				SD[i][i - 1] = 1;
				SP[i][i - 1] = i;
			}
		}
		/*
		 * set right station relation
		 */
		if (S[i]->right != -1) {
			SD[i][i - S[i]->right] = 1;
			SP[i][i - S[i]->right] = i;
		} else {
			if (i < sSize - 1 && S[i]->route == S[i + 1]->route) {
				SD[i][i + 1] = 1;
				SP[i][i + 1] = i;
			}
		}
	}

	int m, n, x, k;
	/*
	 * merge interchange station set
	 */
	for (m = 0; m < ICRowSize - 1; m++) {
		for (i = 0; i < ICColSize[m]; i++) {
			for (n = m + 1; n < ICRowSize; n++) {
				for (j = 0; j < ICColSize[n]; j++) {
					if (IC[m][i]->route == IC[n][j]->route && IC[m][i]->name == IC[n][j]->name) {
						for (x = 0; x < ICColSize[n]; x++) {
							IC[m][ICColSize[m]++] = IC[n][x];
						}
						ICColSize[n] = 0;
					}
				}
			}
		}
	}
	/*
	 * set interchange station path
	 */
	for (k = 0; k < ICRowSize; k++) {
		for (i = 0; i < ICColSize[k] - 1; i++) {
			for (j = i + 1; j < ICColSize[k]; j++) {
				int m = getStation(IC[k][i]->route, IC[k][i]->name);
				int n = getStation(IC[k][j]->route, IC[k][j]->name);

				if (DEBUG) {
					printf("set %c%c to %c%c\n", S[m]->route, S[m]->name, S[n]->route, S[n]->name);
				}
				SD[m][n] = 3;
				SP[m][n] = m;
				SD[n][m] = 3;
				SP[n][m] = n;
			}
		}
	}
}

void findAllLeastDistance() {
	int i, j, k;
	for (k = 0; k < sSize; k++) {
		for (i = 0; i < sSize; i++) {
			for (j = 0; j < sSize; j++) {
				if ((SD[i][j] == -1 && SD[i][k] != -1 && SD[k][j] != -1) || (SD[i][j] != -1 && SD[i][k] != -1 && SD[k][j] != -1 && SD[i][k] + SD[k][j]
						< SD[i][j])) {
					SD[i][j] = SD[i][k] + SD[k][j];
					SP[i][j] = SP[k][j];
				}
			}
		}
	}
}

void getShortestPath(char p[], int s1, int s2) {
	int size = 0, pSize = 0;
	int s[256], r[256];
	int i, j;
	i = s2;
	s[size++] = i;
	while (SP[s1][i] != s1) {
		s[size++] = SP[s1][i];
		i = SP[s1][i];
	}
	s[size++] = s1;
	for (i = size - 1; i >= 0; i--) {
		if (i == size - 1) {
			p[pSize++] = S[s[i]]->route;
			p[pSize++] = S[s[i]]->name;
			continue;
		}
		if (S[s[i]]->route != S[s[i + 1]]->route) {
			p[pSize++] = '=';
			p[pSize++] = S[s[i]]->route;
		}
		p[pSize++] = S[s[i]]->name;
	}
	p[pSize] = '\0';
}

int main(int argv, char * argc[]) {
	int routeNum = 0, r;
	r = scanf("%d", &routeNum);
	int i, j, size;
	char routeChar;
	char route[256];
	memset(ICColSize, 0, 26 * 26 * sizeof(int));
	memset(SD, -1, 26 * 26 * 26 * 26 * sizeof(int));
	memset(SP, -1, 26 * 26 * 26 * 26 * sizeof(int));

	for (i = 0; i < routeNum; i++) {
		r = scanf("%s", route);
		size = strlen(route);
		struct Station * tempRoute[26 * 26];
		int tempRouteSize = 0;
		if (DEBUG) {
			printf("\nget route:%s\n", route);
		}
		routeChar = route[0];
		for (j = 2; j < size;) {
			if (route[j] == '=') {
				if (ICColSize[ICRowSize] == 0) {
					IC[ICRowSize][ICColSize[ICRowSize]++] = alloc(routeChar, route[j - 1]);
				}
				IC[ICRowSize][ICColSize[ICRowSize]++] = alloc(route[j + 1], route[j + 2]);
				j += 3;
				if (j >= size) {
					ICRowSize++;
				}

			} else {
				if (ICColSize[ICRowSize] > 0) {
					ICRowSize++;
				}
				if (j == size - 1 && route[2] == route[j]) {
					tempRoute[0]->left = tempRouteSize - 1;
					tempRoute[tempRouteSize - 1]->right = tempRouteSize - 1;
				} else {
					tempRoute[tempRouteSize++] = alloc(routeChar, route[j]);
				}
				j++;
			}
		}
		for (j = 0; j < tempRouteSize; j++) {
			S[sSize++] = tempRoute[j];
		}
	}

	setDistanceMatrix();
	findAllLeastDistance();

	if (DEBUG) {
		printInfo();
	}

	char pair[4];
	for (r = scanf("%s", pair); strcmp(pair, "#") != 0; r = scanf("%s", pair)) {
		if (DEBUG) {
			printf("pair:%s\n", pair);
		}
		int s1, s2;
		for (i = 0; i < sSize; i++) {
			if (S[i]->route == pair[0] && S[i]->name == pair[1]) {
				s1 = i;
			} else if (S[i]->route == pair[2] && S[i]->name == pair[3]) {
				s2 = i;
			}
		}
		char sPath[1024];
		getShortestPath(sPath, s1, s2);
		printf("%3d: %s\n", SD[s1][s2], sPath);
	}
	return 0;
}
