#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define EPS 0.000000001
#define PI 3.141592653589793
#define EARTH_RAD 6378
#define MAXN 10010

struct Point {
	double x, y;
};

static struct Point p[MAXN];
static int n;

double max(double a, double b) {
	return a > b ? a : b;
}

double min(double a, double b) {
	return a < b ? a : b;
}

int cmp_x(const void * a, const void * b) {
	return ((struct Point *) a)->x - ((struct Point *) b)->x;
}

int cmp_y(const void * a, const void * b) {
	return p[*((int *) a)].y - p[*((int *) b)].y;
}

double dis(int i, int j) {
	return sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
}

double findMin(int left, int right) {

	if (left == right)
		return MAXN;

	if (left == right - 1) {
		return dis(left, right);
	}

	int mid = (right + left) >> 1;
	double min1 = findMin(left, mid);
	double min2 = findMin(mid, right);
	double min = min1 < min2 ? min1 : min2;
	int tmp[MAXN], tn = 0, i, j;
	for (i = left; i <= right; i++) {
		if (fabs(p[i].x - p[mid].x) <= min) {
			tmp[tn++] = i;
		}
	}
	qsort(tmp, tn, sizeof(int), cmp_y);

	for (i = 0; i < tn - 1; i++) {
		for (j = i + 1; j < tn; j++) {
			if (fabs(p[tmp[i]].y - p[tmp[j]].y) > min) {
				break;
			}
			double m = dis(tmp[i], tmp[j]);
			if (m < min - EPS) {
				min = m;
			}
		}
	}
	return min;
}

/**
 * uva 10245
 */
int main() {
	int i, x, y;

	while (scanf("%d", &n) == 1 && n != 0) {
		for (i = 0; i < n; i++) {
			scanf("%lf %lf\n", &(p[i].x), &(p[i].y));
			/*scanf("%lf %lf\n", &x, &y);
			 p[i].x = x;
			 p[i].y = y;*/
		}
		if (DEBUG) {
			for (i = 0; i < n; i++) {
				printf("[%d]%f,%f ", i, p[i].x, p[i].y);
			}
			printf("\n");
		}
		qsort(p, n, sizeof(p[0]), cmp_x);

		if (DEBUG) {
			for (i = 0; i < n; i++) {
				printf("[%d]%f,%f ", i, p[i].x, p[i].y);
			}
			printf("\n");
		}

		double min = findMin(0, n - 1);
		if (min < 10000) {
			printf("%.4lf\n", min);
		} else {
			printf("INFINITY\n");
		}
	}
	return 0;
}

