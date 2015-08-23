#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

struct Point {
	double x, y;
};

struct Point points[100];

int pointsSize;
double R;

int fcmp(double x, double y) {
	if (DEBUG) {
		printf("fcmp %f %f\n", x, y);
	}
	double r = x - y;
	if (fabs(r) < 1e-6) {
		return 0;
	}
	if (r > 0) {
		return 1;
	} else {
		return -1;
	}
}

double sqr(double x) {
	return x * x;
}

double sqr_dis(int a, int b) {
	return sqr(points[b].x - points[a].x) + sqr(points[b].y - points[a].y);
}

double sqr_dis2(int i, struct Point * p) {
	return sqr(points[i].x - p->x) + sqr(points[i].y - p->y);
}

int is_center(struct Point * p) {

	int i;
	for (i = 0; i < pointsSize; ++i) {
		if (fcmp(sqr_dis2(i, p), R * R) > 0) {
			if (DEBUG) {
				printf("is_center for (%f, %f) return 0\n", p->x, p->y);
			}
			return 0;
		}
	}
	if (DEBUG) {
		printf("is_center for (%f, %f) return 1\n", p->x, p->y);
	}
	return 1;
}

int check(int a, int b) {
	double x1 = points[a].x, x2 = points[b].x, y1 = points[a].y, y2 =
			points[b].y;
	double q = sqrt(sqr_dis(a, b));
	if (fcmp(q * q, 4 * R * R) > 0) {
		if (DEBUG) {
			printf("(%f, %f) and (%f, %f) is too long for %f\n", x1, y1, x2, y2,
					R);
		}
		return 0;
	}
	double x_part = sqrt(R * R - 0.25 * q * q) * (y1 - y2) / q;
	double y_part = sqrt(R * R - 0.25 * q * q) * (x2 - x1) / q;
	double x3 = 0.5 * (x1 + x2), y3 = 0.5 * (y1 + y2);
	struct Point p1, p2;
	p1.x = x3 + x_part;
	p1.y = y3 + y_part;
	p2.x = x3 - x_part;
	p2.y = y3 - y_part;
	return is_center(&p1) || is_center(&p2);
}

/**
 * 10005
 */
int main(int argc, char * argv[]) {
	int i, j, m, n, x, y;
	for (;;) {
		scanf("%d", &pointsSize);
		if (pointsSize == 0)
			break;
		R = 0;
		for (i = 0; i < pointsSize; i++) {
			scanf("%d %d", &x, &y);
			points[i].x = x;
			points[i].y = y;
		}
		scanf("%lf", &R);

		int ok = 0;
		if (pointsSize == 1) {
			ok = 1;
		} else if (pointsSize == 2) {
			if (sqr_dis(0, 1) > 4 * R * R) {
				ok = 0;
			}
		} else {
			for (i = 0; i < pointsSize; i++) {
				for (j = i + 1; j < pointsSize; j++) {
					if (check(i, j)) {
						ok = 1;
						break;
					}
				}
				if (ok) {
					break;
				}
			}
		}

		if (ok) {
			printf("The polygon can be packed in the circle.\n");
		} else {
			printf("There is no way of packing that polygon.\n");
		}

	}

	return 0;
}
