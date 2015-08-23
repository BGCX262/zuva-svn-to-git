#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

#define PI acos(-1)

struct Point * stack[1008], *sites[1008];
int stackSize, sitesSize;

struct Point {
	long long int x;
	long long int y;
	double angle;
};

struct Point * newPoint(long long int x, long long int y) {
	struct Point * p = malloc(sizeof(struct Point));
	p->x = x;
	p->y = y;
	return p;
}

int comp_by_cord(struct Point * p1, struct Point * p2) {
	if (p1->y > p2->y) {
		return 1;
	} else if (p1->y == p2->y) {
		if (p1->x > p2->x) {
			return 1;
		} else if (p1->x < p2->x) {
			return -1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

double cal_angle(struct Point * p1, struct Point * p2) {
	/**
	 * redians of angle = atan((y2-y1/x2-x1))
	 * degree of angle = redians * 180 / PI
	 */
	return atan2(p2->y - p1->y, p2->x - p1->x);
}

void ahead_min_y() {
	int i, min = 0;
	for (i = 1; i < sitesSize; i++) {
		if (comp_by_cord(sites[i], sites[min]) == -1) {
			min = i;
		}
	}
	struct Point * t = sites[0];
	sites[0] = sites[min];
	sites[min] = t;
}

void sort_by_angle() {
	int i, j;
	/**
	 * calculate angle between sites[0] and other points
	 */
	for (i = 1; i < sitesSize; i++) {
		sites[i]->angle = cal_angle(sites[0], sites[i]);
	}
	/*
	 * use insert sort
	 */
	double keyAngle;
	struct Point * keyPoint;
	for (j = 2; j < sitesSize; j++) {
		keyAngle = sites[j]->angle;
		keyPoint = sites[j];
		i = j - 1;
		while (i > 0 && (sites[i]->angle > keyAngle || (sites[i]->angle == keyAngle && keyPoint->x < sites[i]->x))) {
			sites[i + 1] = sites[i];
			i--;
		}
		sites[i + 1] = keyPoint;
	}
}
/**
 * return the direction of what turn
 * 1 : left
 *  0 : straight
 *  -1 : right
 */
int getTurn(struct Point * p0, struct Point * p1, struct Point * p2) {
	/*  p0->p1 cross product p0->p2 */
	/* (p1-p0)cross product(p2-p0) = (x1-x0)*(y2-y0) - (x2-x0)*(y1-y0)*/
	if (p0 == NULL || p1 == NULL || p2 == NULL)
		return 1;
	long long int r = (p1->x - p0->x) * (p2->y - p0->y) - (p2->x - p0->x) * (p1->y - p0->y);
	if (r > 0)
		return 1;
	else if (r < 0)
		return -1;
	else
		return 0;
}

int isPointInPolygon(struct Point * p) {
	/*return 1;*/
	int i, r = 1;
	struct Point * p1, *p2;

	for (i = 0; i < stackSize; i++) {
		p1 = stack[i];
		if (i == stackSize - 1) {
			p2 = stack[0];
		} else {
			p2 = stack[i + 1];
		}
		if (getTurn(p1, p2, p) == -1) {
			if (DEBUG) {
				printf("p1(%lld, %lld)->p2(%lld, %lld)->p(%lld, %lld) turn right\n", p1->x, p1->y, p2->x, p2->y, p->x, p->y);
			}
			r = 0;
			break;
		}
	}
	return r;
}

void cal_convex_hull() {
	/**
	 * use 1031 pages's Graham scan algorithm
	 */
	ahead_min_y();
	sort_by_angle();
	if (DEBUG) {
		int k = 0;
		printf("site:\n");
		for (k = 0; k < sitesSize; k++) {
			printf("[%lld,  %lld] %f  ", sites[k]->x, sites[k]->y, sites[k]->angle);
		}
		printf("\n");
	}

	stackSize = 0;
	stack[stackSize++] = sites[0];
	stack[stackSize++] = sites[1];
	stack[stackSize++] = sites[2];

	int i = 0, r;
	for (i = 3; i < sitesSize; i++) {
		r = getTurn(stack[stackSize - 2], stack[stackSize - 1], sites[i]);
		while (r == -1 || r == 0) {
			stackSize--;
			r = getTurn(stack[stackSize - 2], stack[stackSize - 1], sites[i]);
		}
		stack[stackSize++] = sites[i];
	}

	if (DEBUG) {
		int k = 0;
		printf("stack:\n");
		for (k = 0; k < stackSize; k++) {
			printf("[%lld,  %lld] %f  ", stack[k]->x, stack[k]->y, stack[k]->angle);
		}
		printf("\n");
	}

}

int main(int argc, char * argv[]) {
	int i, j, n;
	long long int x, y, a, b, c;
	struct Point * z = newPoint(0, 0);
	for (;;) {
		scanf("%d", &n);
		if (n == 0)
			break;
		sitesSize = 0;
		for (i = 0; i < n; i++) {
			scanf("%lld %lld %lld", &a, &b, &c);
			x = b - a;
			y = c - a;
			sites[sitesSize++] = newPoint(x, y);
		}
		cal_convex_hull();
		if (isPointInPolygon(z)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}
