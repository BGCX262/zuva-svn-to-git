#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define EPS 0.000000001
#define PI 3.141592653589793
#define EARTH_RAD 6378

#include <stdio.h>
#include <stdlib.h>
struct Point {
	double x, y;
};

int dblcmp(double d) {
	if (fabs(d) < EPS) {
		return 0;
	}
	return (d > 0) ? 1 : -1;
}

double det(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}

double cross(struct Point* a, struct Point* b, struct Point* c) {
	return det(b->x - a->x, b->y - a->y, c->x - a->x, c->y - a->y);
}

double dotdet(double x1, double y1, double x2, double y2) {
	return x1 * x2 + y1 * y2;
}

double dot(struct Point *a, struct Point* b, struct Point* c) {
	return dotdet(b->x - a->x, b->y - a->y, c->x - a->x, c->y - a->y);
}

double betweenCmp(struct Point * a, struct Point * b, struct Point * c) {
	return dblcmp(dot(a, b, c));
}

int segcross(struct Point* a, struct Point* b, struct Point* c, struct Point * d) {
	double s1, s2, s3, s4;
	int d1, d2, d3, d4;
	d1 = dblcmp(s1 = cross(a, b, c));
	d2 = dblcmp(s2 = cross(a, b, d));
	d3 = dblcmp(s3 = cross(c, d, a));
	d4 = dblcmp(s4 = cross(c, d, b));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) {
		return 1;
	}

	if ((d1 == 0 && betweenCmp(c, a, b) <= 0) || (d2 == 0 && betweenCmp(d, a, b) <= 0) || (d3 == 0 && betweenCmp(a, c, d) <= 0)
			|| (d4 == 0 && betweenCmp(b, c, d) <= 0)) {
		return 2;
	}
	return 0;
}

/**
 * uva 191
 */
int main() {
	int n, i, startX, startY, endX, endY, leftX, topY, rightX, bottomY;
	struct Point start, end, leftTop, rightBottom, leftBottom, rightTop;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d %d %d %d %d %d %d", &startX, &startY, &endX, &endY, &leftX, &topY, &rightX, &bottomY);
		start.x = startX;
		start.y = startY;
		end.x = endX;
		end.y = endY;
		leftTop.x = leftX < rightX ? leftX : rightX;
		leftTop.y = topY > bottomY ? topY : bottomY;
		rightBottom.x = rightX > leftX ? rightX : leftX;
		rightBottom.y = bottomY < topY ? bottomY : topY;
		rightTop.x = rightX > leftX ? rightX : leftX;
		rightTop.y = topY > bottomY ? topY : bottomY;
		leftBottom.x = leftX < rightX ? leftX : rightX;
		leftBottom.y = bottomY < topY ? bottomY : topY;

		if ((start.x >= leftTop.x) && (start.x <= rightBottom.x) && (end.x >= leftTop.x) && (end.x <= rightBottom.x) && (start.y <= leftTop.y)
				&& (start.y >= rightBottom.y) && (end.y <= leftTop.y) && (end.y >= rightBottom.y)) {
			printf("T\n");
		} else if (segcross(&start, &end, &leftTop, &rightTop) > 0 || segcross(&start, &end, &rightTop, &rightBottom) > 0
				|| segcross(&start, &end, &rightBottom, &leftBottom) > 0 || segcross(&start, &end, &leftBottom, &leftTop) > 0) {
			printf("T\n");
		} else {
			printf("F\n");
		}

	}
	return 0;
}

