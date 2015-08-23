#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define EPS 0.000000001

struct Point {
	double x, y;
};

struct Point points[100];

double ax, bx, cx, ay, by, cy;

/*********************
 * Line intersection *
 *********************
 * Returns the point of intersection of two lines:
 * (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3]).
 * Puts the result (x, y) into (r[0], r[1]) and returns true.
 * If there is no intersection, return false;
 * USED BY: circle3pts
 * #include <math.h>
 * #define EPS ...
 **/
int lineIntersect(double x[], double y[], double r[]) {
	double n[2];
	n[0] = y[3] - y[2];
	n[1] = x[2] - x[3];
	double denom = n[0] * (x[1] - x[0]) + n[1] * (y[1] - y[0]);
	if (fabs(denom) < EPS)
		return 0;
	double num = n[0] * (x[0] - x[2]) + n[1] * (y[0] - y[2]);
	double t = -num / denom;
	r[0] = x[0] + t * (x[1] - x[0]);
	r[1] = y[0] + t * (y[1] - y[0]);
	return 1;
}

/***************************
 * Circle through 3 points *
 ***************************
 * Computes the circle containing the 3 given points.
 * The 3 points are
 *      (x[0], y[0]), (x[1], y[1]) and (x[2], y[2]).
 * The centre of the circle is returned as (r[0], r[1]).
 * The radius is returned normally. If the circle is
 * undefined (the points are collinear), -1.0 is returned.
 * #include <math.h>
 * REQUIRES: lineIntersect
 * FIELD TESTING: Passed UVA 190
 **/
double circle3pts(double x[], double y[], double r[]) {
	double lix[4], liy[4];
	lix[0] = 0.5 * (x[0] + x[1]);
	liy[0] = 0.5 * (y[0] + y[1]);
	lix[1] = lix[0] + y[1] - y[0];
	liy[1] = liy[0] + x[0] - x[1];
	lix[2] = 0.5 * (x[1] + x[2]);
	liy[2] = 0.5 * (y[1] + y[2]);
	lix[3] = lix[2] + y[2] - y[1];
	liy[3] = liy[2] + x[1] - x[2];
	if (!lineIntersect(lix, liy, r))
		return -1.0;
	return sqrt((r[0] - x[0]) * (r[0] - x[0]) + (r[1] - y[0]) * (r[1] - y[0]));
}

void toStr(double x, char c[]) {
	if (x < 0) {
		sprintf(c, "- %.3f", -x);
	} else {
		sprintf(c, "+ %.3f", x);
	}

}

/**
 * 190
 */
int main(int argc, char * argv[]) {
	int i, j, m, n;
	while (scanf("%lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy) == 6) {
		double x[3], y[3], r[2];
		x[0] = ax;
		y[0] = ay;
		x[1] = bx;
		y[1] = by;
		x[2] = cx;
		y[2] = cy;
		double radius = circle3pts(x, y, r);
		char s[5][24];

		toStr(0 - r[0], s[0]);
		toStr(0 - r[1], s[1]);
		toStr(-2. * r[0], s[2]);
		toStr(-2. * r[1], s[3]);
		toStr((r[0] * r[0] + r[1] * r[1] - radius * radius), s[4]);
		printf("(x %s)^2 + (y %s)^2 = %.3f^2\n", s[0], s[1], radius);
		printf("x^2 + y^2 %sx %sy %s = 0\n\n", s[2], s[3], s[4]);
	}

	return 0;
}
