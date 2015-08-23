#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

#define NODE_MAX 102
#define NUL -1

static int i[NODE_MAX], v[NODE_MAX], x[NODE_MAX], l[NODE_MAX], c[NODE_MAX];
static int iAll[NODE_MAX], vAll[NODE_MAX], xAll[NODE_MAX], lAll[NODE_MAX], cAll[NODE_MAX];

void setLessOrEqual5(int num, int index) {
	if (num == 5) {
		v[index]++;
	} else if (num == 4) {
		i[index]++;
		v[index]++;
	} else if (num <= 3) {
		i[index] += num;
	}
}

void setLessOrEqual10(int num, int index) {
	if (num == 10) {
		x[index]++;
	} else if (num == 9) {
		i[index]++;
		x[index]++;
	} else if (num < 9 && num > 5) {
		v[index]++;
		setLessOrEqual5(num - 5, index);
	} else if (num <= 5) {
		setLessOrEqual5(num, index);
	}
}

void setLessOrEqual50(int num, int index) {
	if (num == 50) {
		l[index]++;
	} else if (num <= 49 && num >= 40) {
		x[index]++;
		l[index]++;
		setLessOrEqual10(num - 40, index);
	} else if (num <= 39 && num >= 11) {
		int t = num / 10;
		x[index] += t;
		setLessOrEqual10(num - 10 * t, index);
	} else if (num <= 10) {
		setLessOrEqual10(num, index);
	}
}

void setLessOrEqual100(int num, int index) {
	if (num == 100) {
		c[index]++;
	} else if (num <= 99 && num >= 90) {
		x[index]++;
		c[index]++;
		setLessOrEqual10(num - 90, index);
	} else if (num <= 89 && num >= 51) {
		l[index]++;
		setLessOrEqual50(num - 50, index);
	} else if (num <= 50) {
		setLessOrEqual50(num, index);
	}
}

void init() {
	int num;
	for (num = 1; num <= 100; num++) {
		setLessOrEqual100(num, num);
	}

	iAll[1] = i[1];
	vAll[1] = v[1];
	xAll[1] = x[1];
	lAll[1] = l[1];
	cAll[1] = c[1];

	for (num = 2; num <= 100; num++) {
		iAll[num] = iAll[num - 1] + i[num];
		vAll[num] = vAll[num - 1] + v[num];
		xAll[num] = xAll[num - 1] + x[num];
		lAll[num] = lAll[num - 1] + l[num];
		cAll[num] = cAll[num - 1] + c[num];
	}
}
/**
 * 344
 */
int main(int argc, char * argv[]) {
	int j, num;
	memset(i, 0, NODE_MAX * sizeof(int));
	memset(v, 0, NODE_MAX * sizeof(int));
	memset(x, 0, NODE_MAX * sizeof(int));
	memset(l, 0, NODE_MAX * sizeof(int));
	memset(c, 0, NODE_MAX * sizeof(int));
	memset(iAll, 0, NODE_MAX * sizeof(int));
	memset(vAll, 0, NODE_MAX * sizeof(int));
	memset(xAll, 0, NODE_MAX * sizeof(int));
	memset(lAll, 0, NODE_MAX * sizeof(int));
	memset(cAll, 0, NODE_MAX * sizeof(int));

	init();

	for (;;) {
		scanf("%d", &num);
		if (num == 0)
			break;

		printf("%d: %d i, %d v, %d x, %d l, %d c\n", num, iAll[num], vAll[num], xAll[num], lAll[num], cAll[num]);

	}
	return 0;
}
