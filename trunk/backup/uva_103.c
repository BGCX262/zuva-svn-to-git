#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0

static int box[30][11];
static int num_dimen;
static int num_box;
void print_box() {
	int i, j;
	printf("=================================================\n");
	for (i = 0; i < num_box; i++) {
		for (j = 0; j < num_dimen; j++) {
			/*printf("[%2d][%2d]%2d ", i, j, box[i][j]);*/
			printf("%2d ", box[i][j]);
		}
		printf(" box num:%2d\n", box[i][num_dimen]);
	}
}

/**
 * if box1 is smaller than box2 then return 1;
 */
int isSmaller(int box1, int box2) {
	int i;
	for (i = 0; i < num_dimen; i++) {
		if (box[box1][i] >= box[box2][i]) {
			return 0;
		}
	}
	return 1;
}

/**
 * if key is smaller than box2 then return 1;
 */
int isSmaller_Arr(int key[], int box2) {
	int i;
	for (i = 0; i < num_dimen; i++) {
		if (key[i] > box[box2][i]) {
			return 0;
		}
	}
	return 1;
}

int partition(int row, int left, int right) {
	int pivot = box[row][left];
	int temp;
	int iLarge = left + 1, index = left + 1;
	while (index <= right) {
		if (box[row][index] < pivot) {
			temp = box[row][iLarge];
			box[row][iLarge] = box[row][index];
			box[row][index] = temp;
			iLarge++;
		}
		index++;
	}
	if (iLarge - 1 > left) {
		temp = box[row][iLarge - 1];
		box[row][iLarge - 1] = box[row][left];
		box[row][left] = temp;
		return iLarge - 1;
	}
	return left;
}

void quick_sort(int row, int left, int right) {
	if (left >= right) {
		return;
	}
	if (left + 1 == right) {
		if (box[row][right] < box[row][left]) {
			int t = box[row][right];
			box[row][right] = box[row][left];
			box[row][left] = t;
		}
		return;
	}
	int pivot_index = partition(row, left, right);
	quick_sort(row, left, pivot_index - 1);
	quick_sort(row, pivot_index + 1, right);
	return;
}

void sort_box_dimen() {
	int i;
	for (i = 0; i < num_box; i++) {
		quick_sort(i, 0, num_dimen - 1);
	}
}

void sort_box() {
	/*use insert sort to sort box*/
	int i, j, k, key[num_dimen + 1];
	for (j = 1; j < num_box; j++) {
		for (k = 0; k < num_dimen + 1; k++) {
			key[k] = box[j][k];
		}
		i = j - 1;
		while (i >= 0 && isSmaller_Arr(key, i)) {
			for (k = 0; k < num_dimen + 1; k++) {
				box[i + 1][k] = box[i][k];
			}
			i--;
		}
		for (k = 0; k < num_dimen + 1; k++) {
			box[i + 1][k] = key[k];
		}
	}
}

void print_lns(int lns_box[], int num_lns) {
	int i, j;
	printf("%d\n", num_lns);
	for (i = 0; i < num_lns; i++) {
		if (i != 0) {
			printf(" ");
		}
		printf("%d", box[lns_box[i]][num_dimen]);
	}
	printf("\n");
}

int getLongestNestString(int lns_box[]) {
	int i, j, max = 0, track_end;
	int best[num_box], prev[num_box];
	for (i = 0; i < num_box; i++) {
		best[i] = 1;
		prev[i] = i;
	}
	for (i = 0; i < num_box; i++) {
		for (j = 0; j < i; j++) {
			if (isSmaller(j, i) && best[i] < best[j] + 1) {
				best[i] = best[j] + 1;
				prev[i] = j;
			}
		}
	}
	for (i = 0; i < num_box; i++) {
		if (best[i] > max) {
			max = best[i];
			track_end = i;
		}
	}
	for (i = max - 1; i >= 0; i--) {
		if (i == max - 1) {
			lns_box[i] = track_end;
		} else {
			lns_box[i] = prev[lns_box[i + 1]];
		}
	}
	return max;
}
int main(int argc, char * argv[]) {
	int i, j, num_lns;
	int lns_box[30];
	char l;
	while (scanf("%d %d\n", &num_box, &num_dimen) == 2) {
		for (i = 0; i < num_box; i++) {
			for (j = 0; j < num_dimen; j++) {
				scanf("%d", &box[i][j]);
			}
			/* box number is in the last column*/
			box[i][num_dimen] = i + 1;
		}
		if (DEBUG) {
			print_box();
		}
		sort_box_dimen();
		if (DEBUG) {
			print_box();
		}
		sort_box();
		if (DEBUG) {
			print_box();
		}
		num_lns = getLongestNestString(lns_box);
		print_lns(lns_box, num_lns);
	}
	return 0;
}
