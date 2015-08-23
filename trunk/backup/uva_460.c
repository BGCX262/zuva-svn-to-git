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

static struct Point leftBottom1, rightTop1, leftTop1, rightBottom1, leftTop2, rightBottom2, leftBottom2, rightTop2;

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
/**
 * set point p is the crossing point
 */
int segcross(struct Point* a, struct Point* b, struct Point* c, struct Point * d, struct Point * p) {
	double s1, s2, s3, s4;
	int d1, d2, d3, d4;
	d1 = dblcmp(s1 = cross(a, b, c));
	d2 = dblcmp(s2 = cross(a, b, d));
	d3 = dblcmp(s3 = cross(c, d, a));
	d4 = dblcmp(s4 = cross(c, d, b));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) {
		p->x = (c->x * s2 - d->x * s1) / (s2 - s1);
		p->y = (c->y * s2 - d->y * s1) / (s2 - s1);
		return 1;
	}

	if ((d1 == 0 && betweenCmp(c, a, b) <= 0) || (d2 == 0 && betweenCmp(d, a, b) <= 0) || (d3 == 0 && betweenCmp(a, c, d) <= 0)
			|| (d4 == 0 && betweenCmp(b, c, d) <= 0)) {
		p->x = (c->x * s2 - d->x * s1) / (s2 - s1);
		p->y = (c->y * s2 - d->y * s1) / (s2 - s1);
		return 2;
	}
	return 0;
}

int isIn(struct Point * p) {
	return dblcmp(cross(&rightBottom1, &rightTop1, p)) == 1 && dblcmp(cross(&rightTop1, &leftTop1, p)) == 1 && dblcmp(cross(&leftTop1, &leftBottom1, p)) == 1
			&& dblcmp(cross(&leftBottom1, &rightBottom1, p)) == 1;
}

double max(double a, double b) {
	return a > b ? a : b;
}

double min(double a, double b) {
	return a < b ? a : b;
}

int isOn(struct Point* p1, struct Point * p2, struct Point * p) {
	return dblcmp(cross(p1, p2, p)) == 0 && p->x <= max(p1->x, p2->x) && p->x >= min(p1->x, p2->x) && p->y <= max(p1->y, p2->y) && p->y >= min(p1->y, p2->y);
}

/**
 * uva 460
 */
int main() {
	int n, i, leftBottomX, leftBottomY, rightTopX, rightTopY, leftX, rightX, topY, bottomY;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d %d %d", &leftBottomX, &leftBottomY, &rightTopX, &rightTopY);
		leftBottom1.x = leftBottomX;
		leftBottom1.y = leftBottomY;
		rightTop1.x = rightTopX;
		rightTop1.y = rightTopY;
		leftTop1.x = leftBottomX;
		leftTop1.y = rightTopY;
		rightBottom1.x = rightTopX;
		rightBottom1.y = leftBottomY;

		scanf("%d %d %d %d", &leftBottomX, &leftBottomY, &rightTopX, &rightTopY);
		leftBottom2.x = leftBottomX;
		leftBottom2.y = leftBottomY;
		rightTop2.x = rightTopX;
		rightTop2.y = rightTopY;
		leftTop2.x = leftBottomX;
		leftTop2.y = rightTopY;
		rightBottom2.x = rightTopX;
		rightBottom2.y = leftBottomY;

		leftX = rightX = topY = bottomY = 0;
		leftX = max(leftBottom1.x, leftBottom2.x);
		rightX = min(rightTop1.x, rightTop2.x);
		bottomY = max(leftBottom1.y, leftBottom2.y);
		topY = min(rightTop1.y, rightTop2.y);
		if (i > 0)
			printf("\n");
		if (leftX < rightX && bottomY < topY) {
			printf("%d %d %d %d\n", leftX, bottomY, rightX, topY);
		} else {
			printf("No Overlap\n");
		}

		/*if (isIn(&leftTop2)) {
		 if (isIn(&rightTop2)) {
		 printf("%.0f %.0f %.0f %.0f\n", leftBottom2.x, max(leftBottom2.y, leftBottom1.y), rightTop2.x, rightTop2.y);
		 } else if (isOn(&rightBottom1, &rightTop1, &rightTop2)) {
		 printf("%.0f %.0f %.0f %.0f\n", leftBottom2.x, max(leftBottom2.y, leftBottom1.y), rightTop2.x, rightTop2.y);
		 } else {
		 printf("%.0f %.0f %.0f %.0f\n", leftBottom2.x, max(leftBottom2.y, leftBottom1.y), min(rightTop1.x, rightTop2.x), rightTop2.y);
		 }
		 } else if (isOn(&rightBottom1, &rightTop1, &leftTop2)) {
		 printf("No Overlap\n");
		 } else if (isOn(&rightTop1, &leftTop1, &leftTop2)) {
		 printf("%.0f %.0f %.0f %.0f\n", max(leftTop2.x, leftTop1.x), max(leftBottom2.y, leftBottom1.y), min(rightTop2.x, rightTop1.x), rightTop2.y);
		 } else if (isOn(&leftTop1, &leftBottom1, &leftTop2)) {
		 printf("%.0f %.0f %.0f %.0f\n", leftTop2.x, max(leftBottom2.y, leftBottom1.y), min(rightTop2.x, rightTop1.x), rightTop2.y);
		 } else if (isOn(&leftBottom1, &rightBottom1, &leftTop2)) {
		 printf("No Overlap\n");
		 } else {
		 printf("No Overlap\n");
		 }*/

	}
	return 0;
}

