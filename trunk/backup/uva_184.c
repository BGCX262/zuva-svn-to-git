#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

struct Point {
	int x;
	int y;
};
struct Point points[300];
int pointsSize, linesSize, lines[300][12], relation[300][300];

void makeLines() {
	if (DEBUG)
		printf("makeLines\n");

	int a, b, c, linesIndex = 0;
	for (a = 0; a < pointsSize - 2; a++) {
		for (b = a + 1; b < pointsSize - 1; b++) {
			if (relation[a][b] == 1)
				continue;

			if (lines[linesIndex][0] > 0) {
				linesIndex++;
			}

			for (c = b + 1; c < pointsSize; c++) {
				if (relation[a][c] == 1 || relation[b][c] == 1)
					continue;

				int pos = points[a].x * points[b].y + points[b].x * points[c].y + points[c].x * points[a].y;
				int neg = points[a].x * points[c].y + points[b].x * points[a].y + points[c].x * points[b].y;
				if (pos == neg) {
					if (DEBUG)
						printf("find a line %d, %d, %d\n", a, b, c);
					if (lines[linesIndex][0] == 0) {
						lines[linesIndex][0] = 3;
						lines[linesIndex][1] = a;
						lines[linesIndex][2] = b;
						lines[linesIndex][3] = c;
					} else {
						lines[linesIndex][lines[linesIndex][0] + 1] = c;
						lines[linesIndex][0]++;
					}
					relation[a][b] = relation[b][c] = relation[a][c] = 1;
				}
			}
		}
	}
	if (lines[linesIndex][0] == 0) {
		linesSize = linesIndex;
	} else {
		linesSize = linesIndex + 1;
	}
}

int compareInLine(const void * a, const void * b) {
	int i = *(int*) a;
	int j = *(int*) b;
	if (points[i].x != points[j].x) {
		return points[i].x - points[j].x;
	}
	return points[i].y - points[j].y;
}

int compareBetweenLine(const void * a, const void * b) {
	int * i = (int*) a;
	int * j = (int*) b;
	struct Point p1 = points[i[1]];
	struct Point p2 = points[j[1]];
	if (p1.x != p2.x) {
		return p1.x - p2.x;
	}
	if (p1.y != p2.y) {
		return p1.y - p2.y;
	}
	p1 = points[i[2]];
	p2 = points[j[2]];
	if (p1.x != p2.x) {
		return p1.x - p2.x;
	}
	if (p1.y != p2.y) {
		return p1.y - p2.y;
	}
	return 0;
}

void sortLines() {
	int i, j;
	for (i = 0; i < linesSize; i++) {
		qsort(&lines[i][1], lines[i][0], sizeof(int), compareInLine);
	}

	qsort(&lines[0][0], linesSize, sizeof(int) * 12, compareBetweenLine);
}

void printLines() {
	int i, j;
	if (DEBUG)
		printf("linesSize:%d\n", linesSize);
	if (linesSize > 0) {
		printf("The following lines were found:\n");
		for (i = 0; i < linesSize; i++) {
			for (j = 1; j <= lines[i][0]; j++) {
				printf("(%4d,%4d)", points[lines[i][j]].x, points[lines[i][j]].y);
			}
			if (i < linesSize - 1)
				printf("\n");
		}
	} else {
		printf("No lines were found");
	}

}

void printPoints() {
	if (!DEBUG) {
		return;
	}

	int i, j;
	printf("points:\n");
	for (i = 0; i < pointsSize; i++) {
		printf("(%4d,%4d)\n", points[i].x, points[i].y);
	}
}

/**
 * 184
 */
int main(int argc, char * argv[]) {
	int i, j, x, y, k = 0;
	for (;;) {
		if (k == 0) {
			k = 1;
		} else {
			printf("\n");
		}

		pointsSize = 0;
		linesSize = 0;
		for (i = 0; i < 300; i++) {
			for (j = 0; j < 300; j++) {
				relation[i][j] = 0;
			}
		}
		for (i = 0; i < 300; i++) {
			for (j = 0; j < 12; j++) {
				lines[i][j] = 0;
			}
		}

		scanf("%d", &x);
		scanf("%d", &y);
		if (x == 0 && y == 0) {
			break;
		}
		points[pointsSize].x = x;
		points[pointsSize].y = y;
		pointsSize++;

		for (;;) {
			scanf("%d", &x);
			scanf("%d", &y);
			if (x == 0 && y == 0) {
				printPoints();
				makeLines();
				sortLines();
				printLines();
				break;
			}
			points[pointsSize].x = x;
			points[pointsSize].y = y;
			pointsSize++;
		}

	}
	return 0;
}
