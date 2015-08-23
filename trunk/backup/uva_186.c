#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

struct edge {
	int len;
	char name[26];
}typedef EDGE;

int INF = 1000000000;
int citySize;
char * city[101];
int cost[101][101];
int predecessor[101][101];
EDGE edges[101][101];

int addCity(char * name) {
	int i;
	for (i = 0; i < citySize; i++) {
		if (strcmp(city[i], name) == 0) {
			return i;
		}
	}

	city[citySize++] = name;
	return citySize - 1;
}

int getCity(char * name) {
	int i;
	for (i = 0; i < citySize; i++) {
		if (strcmp(city[i], name) == 0) {
			return i;
		}
	}
	return -1;
}

int main() {
	int i, j, k, second = 0, from, to;
	char line[256], line_temp[256];
	char * token, *name;
	for (i = 0; i < 101; i++) {
		for (j = 0; j < 101; j++) {
			edges[i][j].len = 0;
			cost[i][j] = INF;
			if (i == j) {
				cost[i][j] = 0;
			}
			predecessor[i][j] = -1;
		}
	}
	while (fgets(line, 256, stdin) != NULL) {
		j = 0;
		for (i = 0; i < strlen(line); i++) {
			if (isalpha(line[i]) || isdigit(line[i]) || line[i] == ' ' || line[i] == ',' || line[i] == '-') {
				line_temp[j++] = line[i];
			}
		}
		line_temp[j++] = '\0';

		strcpy(line, line_temp);

		if (strlen(line) <= 2) {
			second = 1;
			for (i = 0; i < citySize; i++) {
				for (j = 0; j < citySize; j++) {
					if (edges[i][j].len != 0) {
						cost[i][j] = edges[i][j].len;
					}
				}
			}

			for (k = 0; k < citySize; k++) {
				for (i = 0; i < citySize; i++) {
					for (j = 0; j < citySize; j++) {
						if (cost[i][j] > cost[i][k] + cost[k][j]) {
							cost[i][j] = cost[i][k] + cost[k][j];
							predecessor[i][j] = predecessor[k][j];
						}
					}
				}
			}

			if (DEBUG) {
				printf("city\n");
				for (i = 0; i < citySize; i++) {
					printf("[%d]%s\n", i, city[i]);

				}
				printf("edges\n");
				for (i = 0; i < citySize; i++) {
					for (j = 0; j < citySize; j++) {
						printf("[%d][%d]%d ", i, j, edges[i][j].len);
					}
					printf("\n");
				}
				printf("cost\n");
				for (i = 0; i < citySize; i++) {
					for (j = 0; j < citySize; j++) {
						printf("[%d][%d]%d ", i, j, cost[i][j]);
					}
					printf("\n");
				}
				printf("predecessor\n");
				for (i = 0; i < citySize; i++) {
					for (j = 0; j < citySize; j++) {
						printf("[%d][%d]%d ", i, j, predecessor[i][j]);
					}
					printf("\n");
				}
			}

			continue;
		}

		if (second == 0) {
			token = strtok(line, ",");
			name = (char*) malloc(strlen(token) * sizeof(char));
			strcpy(name, token);
			from = addCity(name);
			token = strtok(NULL, ",");
			name = (char*) malloc(strlen(token) * sizeof(char));
			strcpy(name, token);
			to = addCity(name);
			token = strtok(NULL, ",");
			name = (char*) malloc(strlen(token) * sizeof(char));
			strcpy(name, token);

			token = strtok(NULL, ",");
			int l = atoi(token);
			if (edges[from][to].len == 0 || edges[from][to].len > l) {
				strcpy(edges[from][to].name, name);
				strcpy(edges[to][from].name, name);
				edges[from][to].len = edges[to][from].len = l;
				predecessor[from][to] = from;
				predecessor[to][from] = to;
			}

		} else {

			token = strtok(line, ",");
			int src = getCity(token);
			token = strtok(NULL, ",");
			int tar = getCity(token);
			if (DEBUG)
				printf("src %d tar %d\n", src, tar);
			printf("\n\nFrom                 To                   Route      Miles\n");
			printf("-------------------- -------------------- ---------- -----\n");

			to = tar;
			int hubs[101], hubsSize = 0;
			hubs[hubsSize++] = to;

			while (predecessor[src][to] != src && predecessor[src][to] != -1) {

				hubs[hubsSize++] = predecessor[src][to];
				to = predecessor[src][to];
			}
			hubs[hubsSize++] = src;

			if (DEBUG) {
				for (i = 0; i < hubsSize; i++) {
					printf("[%d]%d ", i, hubs[i]);
				}
				printf("\n");
			}
			for (i = hubsSize - 1; i > 0; i--) {
				from = hubs[i];
				to = hubs[i - 1];
				printf("%-20s %-20s %-10s %5d\n", city[from], city[to], edges[from][to].name, edges[from][to].len);
			}
			printf("                                                     -----\n");
			printf("                                          Total      %5d\n", cost[src][tar]);
		}
	}

	return 0;
}
