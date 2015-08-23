#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

#define NULL_JUMP -1

struct Vertex {
	int x, y, isSet;
	double jump;
}typedef VERTEX;

int set[200], setSize, vertexSize, neighbors[200][200];
VERTEX vertex[200];

double max(double a, double b) {
	return (a > b) ? a : b;
}

int compare(const void * a, const void * b) {
	double a_jump = vertex[*(int *) a].jump;
	double b_jump = vertex[*(int *) b].jump;

	if (DEBUG) {
		printf("a %d %.3f b %d %.3f\n", *(int *) a, a_jump, *(int *) a, b_jump);
	}
	if (a_jump == NULL_JUMP && b_jump == NULL_JUMP) {
		return 0;
	} else if (a_jump != NULL_JUMP && b_jump == NULL_JUMP) {
		return -1;
	} else if (a_jump == NULL_JUMP && b_jump != NULL_JUMP) {
		return 1;
	} else {
		if (a_jump < b_jump) {
			return -1;
		} else if (a_jump > b_jump) {
			return 1;
		} else {
			return 0;
		}
	}
}

double distance(int a, int b) {
	return sqrt((vertex[a].x - vertex[b].x) * (vertex[a].x - vertex[b].x) + (vertex[a].y - vertex[b].y) * (vertex[a].y - vertex[b].y));
}

void removeSet(int a) {
	int i;
	for (i = a; i < setSize - 1; i++) {
		set[i] = set[i + 1];
	}
	setSize--;
}

int main() {
	int i, j, t, x = 0;
	for (;;) {

		x++;
		scanf("%d\n", &vertexSize);
		if (vertexSize == 0)
			break;
		setSize = 0;
		for (i = 0; i < vertexSize; i++) {
			for (j = 0; j < vertexSize; j++) {
				neighbors[i][j] = 0;
			}
		}

		for (i = 0; i < vertexSize; i++) {
			scanf("%d %d\n", &vertex[i].x, &vertex[i].y);
		}

		if (DEBUG) {
			printf("vertex:\n");
			for (i = 0; i < vertexSize; i++) {
				printf("%d %d\n", vertex[i].x, vertex[i].y);
			}
		}

		double Freddy_Fiona = distance(0, 1);
		for (i = 0; i < vertexSize - 1; i++) {
			for (j = i + 1; j < vertexSize; j++) {
				double dist = distance(i, j);
				if (dist < Freddy_Fiona) {
					neighbors[i][j] = neighbors[j][i] = 1;
				}
			}
		}

		if (DEBUG) {
			printf("neighbors:\n");
			for (i = 0; i < vertexSize; i++) {
				for (j = 0; j < vertexSize; j++) {
					printf("[%d][%d]%d ", i, j, neighbors[i][j]);
				}
				printf("\n");
			}
		}

		vertex[0].jump = 0;
		set[setSize++] = 0;
		vertex[0].isSet = 1;
		for (i = 1; i < vertexSize; i++) {
			vertex[i].jump = NULL_JUMP;
			set[setSize++] = i;
			vertex[i].isSet = 1;
		}

		while (setSize > 0) {
			qsort(set, setSize, sizeof(int), compare);

			if (DEBUG) {
				printf("set\n");
				for (i = 0; i < setSize; i++) {
					printf("[%d].jump %.3f  ", set[i], vertex[set[i]].jump);
				}
				printf("\n");
			}

			int curr = set[0];

			if (curr == 1) {
				break;
			}

			removeSet(0);
			vertex[curr].isSet = 0;
			for (i = 0; i < vertexSize; i++) {
				if (neighbors[curr][i] && vertex[i].isSet) {
					if (vertex[i].jump == NULL_JUMP || vertex[i].jump > max(distance(curr, i), vertex[curr].jump)) {
						if (DEBUG) {
							printf("curr [%d]%.3f i [%d]%.3f distance %.3f max %.3f\n", curr, vertex[curr].jump, i, vertex[i].jump, distance(curr, i),
									max(distance(curr, i), vertex[curr].jump));
						}
						vertex[i].jump = max(distance(curr, i), vertex[curr].jump);
					}
				}
			}
		}
		printf("Scenario #%d\n", x);
		printf("Frog Distance = %.3f\n\n", vertex[1].jump != NULL_JUMP ? vertex[1].jump : Freddy_Fiona);
	}
	return 0;
}
