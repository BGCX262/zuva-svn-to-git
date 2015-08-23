#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0

static int end_x;
static int city[10000];
static int start_x = -1;

void print_city() {
	int i;
	printf("city ============================\n");
	for (i = 0; i <= end_x; i++) {
		printf("[%d]%d ", i, city[i]);
		if (i % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

void draw_skyline() {
	int i, height = city[start_x];
	printf("%d %d", start_x, city[start_x]);
	for (i = start_x + 1; i <= end_x; i++) {
		if (city[i] != height) {
			height = city[i];
			printf(" %d %d", i, height);
		}
	}
	printf("\n");
}

int main(int argc, char * argv[]) {
	int i, left, right, height;
	while (scanf("%d %d %d\n", &left, &height, &right) == 3) {
		if (DEBUG) {
			printf("left:%d, height:%d, right:%d\n", left, height, right);
		}
		if (start_x == -1) {
			start_x = left;
		}
		if (right > end_x) {
			end_x = right;
		}
		for (i = left; i < right; i++) {
			if (city[i] < height) {
				city[i] = height;
			}
		}
	}
	draw_skyline();
	if (DEBUG) {
		print_city();
	}
	return 0;
}
