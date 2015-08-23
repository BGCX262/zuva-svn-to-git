#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0

static int num_curr;
static float best[21][21][21];
static int path[21][21][21];
static int stack[21];
static int top = -1;
void enqueue(int item) {
	top++;
	stack[top] = item;
}
int dequeue() {
	if (top == -1) {
		return -1;
	}
	top--;
	return stack[top + 1];
}

void print_matrix() {
	int i, j, step;
	printf("best =================================================\n");
	for (step = 1; step <= num_curr; step++) {
		printf("step %d ==================\n", step);
		for (i = 1; i <= num_curr; i++) {
			for (j = 1; j <= num_curr; j++) {
				printf("%f ", best[i][j][step]);
			}
			printf("\n");
		}
	}
	printf("path =================================================\n");
	for (step = 1; step <= num_curr; step++) {
		printf("step %d ==================\n", step);
		for (i = 1; i <= num_curr; i++) {
			for (j = 1; j <= num_curr; j++) {
				printf("%d ", path[i][j][step]);
			}
			printf("\n");
		}
	}
}

void find_fewest_exchange() {
	int i, j, step, k, path_temp, b;
	float temp;
	for (step = 2; step <= num_curr; step++) {
		for (k = 1; k <= num_curr; k++) {
			for (i = 1; i <= num_curr; i++) {
				for (j = 1; j <= num_curr; j++) {
					temp = best[i][k][step - 1] * best[k][j][1];
					if (temp > best[i][j][step]) {
						best[i][j][step] = temp;
						path[i][j][step] = k;
					}
				}
			}
		}
	}
	for (step = 1; step <= num_curr; step++) {
		for (i = 1; i <= num_curr; i++) {
			if (best[i][i][step] > 1) {
				if (DEBUG) {
					printf("find sum:%f\n", best[i][i][step]);
				}
				int t = step;
				int path_temp = path[i][i][t];
				enqueue(i);
				enqueue(path_temp);
				while (t > 1) {
					enqueue(path[i][path_temp][t - 1]);
					path_temp = path[i][path_temp][t - 1];
					t--;
				}
				b = 0;
				while ((path_temp = dequeue()) != -1) {
					if (b == 0) {
						printf("%d", path_temp);
						b = 1;
					} else {
						printf(" %d", path_temp);
					}
				}
				printf("\n");
				return;
			}
		}
	}
	printf("no arbitrage sequence exists\n");
}

int main(int argc, char * argv[]) {
	int i, j, step;
	while (scanf("%d\n", &num_curr) == 1) {
		for (step = 1; step <= num_curr; step++) {
			for (i = 1; i <= num_curr; i++) {
				for (j = 1; j <= num_curr; j++) {
					best[i][j][step] = 0;
					path[i][j][step] = 0;
				}
			}
		}
		for (i = 1; i <= num_curr; i++) {
			for (j = 1; j <= num_curr; j++) {
				if (i == j) {
					best[i][j][1] = 1;
				} else {
					scanf("%f", &best[i][j][1]);
				}
				path[i][j][1] = i;
			}
		}
		if (DEBUG) {
			print_matrix();
		}
		find_fewest_exchange();
		if (DEBUG) {
			print_matrix();
		}
	}
	return 0;
}
