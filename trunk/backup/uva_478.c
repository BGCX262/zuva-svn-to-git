#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define EPS 0.000000001
#define PI 3.141592653589793
#define EARTH_RAD 6378

struct Point {
	double x, y;
};

struct Polygon {
	char type;
	struct Point upperLeft, lowerRight, center, v1, v2, v3;
	double radius;
};
struct Polygon pol[36];
int polSize;

int isLeftForLine(double x, double y, double x1, double y1, double x2, double y2) {
	double A, B, C;
	A = -(y2 - y1);
	B = x2 - x1;
	C = -(A * x1 + B * y1);
	if (A * x + B * y + C >= EPS)
		return 1;
	return 0;
}

int isInRectangle(double x, double y, struct Polygon * r) {
	if (isLeftForLine(x, y, r->upperLeft.x, r->upperLeft.y, r->upperLeft.x, r->lowerRight.y) == 0)
		return 0;
	if (isLeftForLine(x, y, r->upperLeft.x, r->lowerRight.y, r->lowerRight.x, r->lowerRight.y) == 0)
		return 0;
	if (isLeftForLine(x, y, r->lowerRight.x, r->lowerRight.y, r->lowerRight.x, r->upperLeft.y) == 0)
		return 0;
	if (isLeftForLine(x, y, r->lowerRight.x, r->upperLeft.y, r->upperLeft.x, r->upperLeft.y) == 0)
		return 0;
	return 1;
}

int isInCircle(double x, double y, struct Polygon * c) {
	if ((x - c->center.x) * (x - c->center.x) + (y - c->center.y) * (y - c->center.y) > c->radius * c->radius)
		return 0;

	return 1;
}

int isInTriangle(double x, double y, struct Polygon * t) {
	if (isLeftForLine(x, y, t->v1.x, t->v1.y, t->v2.x, t->v2.y) == 1 && isLeftForLine(x, y, t->v2.x, t->v2.y, t->v3.x, t->v3.y) == 1
			&& isLeftForLine(x, y, t->v3.x, t->v3.y, t->v1.x, t->v1.y) == 1) {
		return 1;
	}

	if (isLeftForLine(x, y, t->v1.x, t->v1.y, t->v2.x, t->v2.y) == 0 && isLeftForLine(x, y, t->v2.x, t->v2.y, t->v3.x, t->v3.y) == 0
			&& isLeftForLine(x, y, t->v3.x, t->v3.y, t->v1.x, t->v1.y) == 0) {
		return 1;
	}

	return 0;
}
/**
 * 535
 */
int main(int argc, char * argv[]) {
	int i, j;
	char s[36];
	double a, b, c, d, e, f;
	polSize = 0;
	while (scanf("%s", s) && s[0] != '*') {

		pol[polSize].type = s[0];
		if (s[0] == 'r') {
			scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
			pol[polSize].upperLeft.x = a;
			pol[polSize].upperLeft.y = b;
			pol[polSize].lowerRight.x = c;
			pol[polSize].lowerRight.y = d;
		} else if (s[0] == 'c') {
			scanf("%lf %lf %lf", &a, &b, &c);
			pol[polSize].center.x = a;
			pol[polSize].center.y = b;
			pol[polSize].radius = c;
		} else if (s[0] == 't') {
			scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);
			pol[polSize].v1.x = a;
			pol[polSize].v1.y = b;
			pol[polSize].v2.x = c;
			pol[polSize].v2.y = d;
			pol[polSize].v3.x = e;
			pol[polSize].v3.y = f;
		}
		polSize++;
	}
	if (DEBUG) {
		for (i = 0; i < polSize; i++) {

		}
	}

	int pointIndex = 0;
	while (scanf("%lf %lf", &a, &b) && a != 9999.9 && b != 9999.9) {
		int find = 0;
		pointIndex++;
		for (i = 0; i < polSize; i++) {
			if (pol[i].type == 'r' && isInRectangle(a, b, &pol[i])) {
				find = 1;
				printf("Point %d is contained in figure %d\n", pointIndex, i + 1);
			} else if (pol[i].type == 'c' && isInCircle(a, b, &pol[i])) {
				find = 1;
				printf("Point %d is contained in figure %d\n", pointIndex, i + 1);
			} else if (pol[i].type == 't' && isInTriangle(a, b, &pol[i])) {
				find = 1;
				printf("Point %d is contained in figure %d\n", pointIndex, i + 1);
			}
		}
		if (find == 0) {
			printf("Point %d is not contained in any figure\n", pointIndex);
		}
	}
	return 0;
}
