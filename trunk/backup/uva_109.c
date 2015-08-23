#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0
#define PI acos(-1)

struct Point {
	int x;
	int y;
	float angle;
	struct Point * up;
	struct Point * down;
};

struct Point * newPoint(int x, int y) {
	struct Point * p = malloc(sizeof(struct Point));
	p->x = x;
	p->y = y;
	p->up = NULL;
	p->down = NULL;
	return p;
}

struct Point * enqueue(struct Point * pTop, struct Point * p) {
	if (pTop != NULL) {
		pTop->up = p;
		if (p != NULL)
			p->down = pTop;
	}
	return p;
}

struct Point * dequeue(struct Point * pTop) {
	struct Point * t = NULL;
	if (pTop != NULL) {
		if (pTop->down != NULL) {
			pTop->down->up = NULL;
			t = pTop->down;
			pTop->down = NULL;
		}
	}
	return t;
}

void print_sites(struct Point * sites[], int N) {
	int i;
	for (i = 0; i < N; i++) {
		if (i % 5 == 0)
			printf("\n");
		printf("[%2d]:(%2d,%2d)  ", i, sites[i]->x, sites[i]->y);
	}
	printf("\n");
}

void print_stack(struct Point * t) {
	while (t->up != NULL) {
		printf("(%d,%d)=>", t->x, t->y);
		t = t->up;
	}
	printf("(%d,%d)", t->x, t->y);
	printf("\n");
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

float cal_angle(struct Point * p1, struct Point * p2) {
	/**
	 * redians of angle = atan((y2-y1/x2-x1))
	 * degree of angle = redians * 180 / PI
	 */
	return atan2(p2->y - p1->y, p2->x - p1->x);
}

void ahead_min_y(struct Point * sites[], int N) {
	int i, min = 0;
	for (i = 1; i < N; i++) {
		if (comp_by_cord(sites[i], sites[min]) == -1) {
			min = i;
		}
	}
	struct Point * t = sites[0];
	sites[0] = sites[min];
	sites[min] = t;
}

void sort_by_angle(struct Point * sites[], int N) {
	int i, j;
	/**
	 * calculate angle between sites[0] and other points
	 */
	for (i = 1; i < N; i++) {
		sites[i]->angle = cal_angle(sites[0], sites[i]);
	}
	/*
	 * use insert sort
	 */
	float keyAngle;
	struct Point * keyPoint;
	for (j = 2; j < N; j++) {
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
	//  p0->p1 cross product p0->p2
	// (p1-p0)cross product(p2-p0) = (x1-x0)*(y2-y0) - (x2-x0)*(y1-y0)
	if (p0 == NULL || p1 == NULL || p2 == NULL)
		return 1;
	int r = (p1->x - p0->x) * (p2->y - p0->y) - (p2->x - p0->x) * (p1->y - p0->y);
	if (r > 0)
		return 1;
	else if (r < 0)
		return -1;
	else
		return 0;
}

int isPointInPolygon(struct Point * pV, struct Point * p) {
	/*return 1;*/
	int i, r = 1;
	struct Point * p0 = pV;
	while (pV->up != NULL) {
		if (getTurn(pV, pV->up, p) == -1) {
			r = 0;
			break;
		}
		pV = pV->up;
	}
	if (r != 0) {
		if (getTurn(pV, p0, p) == -1) {
			r = 0;
		}
	}
	if (DEBUG) {
		printf("(%d,%d) is %d in sites\n", p->x, p->y, r);
	}
	return r;
}

struct Point * cal_convex_hull(struct Point * sites[], int N) {
	/**
	 * use 1031 pages's Graham scan algorithm
	 */
	int r;
	struct Point * pTop = NULL;
	ahead_min_y(sites, N);
	sort_by_angle(sites, N);
	if (DEBUG) {
		print_sites(sites, N);
	}
	pTop = enqueue(pTop, sites[0]);
	pTop = enqueue(pTop, sites[1]);
	pTop = enqueue(pTop, sites[2]);
	int i = 0;
	for (i = 3; i < N; i++) {
		r = getTurn(pTop->down, pTop, sites[i]);
		while (r == -1 || r == 0) {
			pTop = dequeue(pTop);
			r = getTurn(pTop->down, pTop, sites[i]);
		}
		pTop = enqueue(pTop, sites[i]);
	}
	while (pTop->down != NULL) {
		pTop = pTop->down;
	}
	return pTop;
}

float cal_area(struct Point * pV) {

	float area = 0;
	struct Point * p0 = pV;
	while (pV->up != NULL) {
		area += (pV->x * pV->up->y - pV->up->x * pV->y);
		pV = pV->up;
	}
	area += (pV->x * p0->y - p0->x * pV->y);
	area /= 2;
	if (DEBUG) {
		printf("area: %f \n", area);
	}
	return area;
}

int main(int argc, char * argv[]) {
	int i, j = 0, x, y, rt, N;
	float badArea = 0;
	struct Point * kingdoms[20];
	struct Point * sites[100];
	while (scanf("%d\n", &N) == 1) {
		if (N == -1) {
			break;
		}
		for (i = 0; i < N; i++) {
			rt = scanf("%d %d\n", &x, &y);
			sites[i] = newPoint(x, y);
		}
		if (DEBUG) {
			print_sites(sites, N);
		}
		struct Point * p0 = cal_convex_hull(sites, N);
		if (DEBUG) {
			print_stack(p0);
		}
		kingdoms[j] = p0;
		j++;
	}
	while (scanf("%d %d\n", &x, &y) == 2) {
		struct Point * bomb = newPoint(x, y);
		if (DEBUG) {
			printf("bomb (%d, %d)\n", bomb->x, bomb->y);
		}
		for (i = 0; i < j; i++) {
			if (kingdoms[i] != NULL) {
				if (isPointInPolygon(kingdoms[i], bomb) == 1) {
					badArea += cal_area(kingdoms[i]);
					kingdoms[i] = NULL;
					break;
				}
			}
		}
	}
	printf("%.2f\n", badArea);
	return 0;
}
