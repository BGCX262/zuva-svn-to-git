#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0

static int stack[256];
static int index = -1;
void enqueue(int n) {
	if (DEBUG) {
		printf("push %d\n", n);
	}
	index++;
	stack[index] = n;
}

int dequeue() {
	int n = stack[index];
	index--;
	if (DEBUG) {
		printf("pop : %d\n", n);
	}
	return n;
}

int getStackSum() {
	int i, sum = 0;
	for (i = 0; i <= index; i++) {
		sum += stack[i];
	}
	if (DEBUG) {
		printf("sum : %d\n", sum);
	}
	return sum;
}

int isEmpty() {
	if (index < 0) {
		return 1;
	}
	return 0;
}

int verifySum(int want_sum) {
	int result = 0;
	if (want_sum == getStackSum()) {
		result = 1;
	}
	if (DEBUG) {
		printf("verify sum result : %d\n", result);
	}
	return result;
}

int main(int argc, char * argv[]) {
	char inc[256];
	char curr_c, last_c;
	int want_sum, tree_sum, yes = 0, n, isBlkSub, isNegative;
	while (scanf("%s", inc) != EOF) {
		if (isdigit(inc[0]) || inc[0] == '-') {
			want_sum = atoi(inc);
		}
		n = 0;
		curr_c = '#';
		isBlkSub = 0;
		yes = 0;
		isNegative = 0;
		while (1) {
			if (isgraph(curr_c)) {
				last_c = curr_c;
			}
			curr_c = getchar();
			if (!isgraph(curr_c)) {
				continue;
			}
			if (DEBUG) {
				printf("current char : %c last char : %c\n", curr_c, last_c);
			}
			if (curr_c == '(') {
				if (isdigit(last_c)) {
					if (isNegative) {
						n = -n;
					}
					enqueue(n);
					n = 0;
					isNegative = 0;
				}
			} else if (curr_c == ')') {
				if (last_c == '(') {
					if (isBlkSub == 0) {
						isBlkSub = 1;
					} else {
						/*time to judge sum*/
						if (verifySum(want_sum)) {
							yes = 1;
						}
						isBlkSub = 0;
					}
				} else {
					isBlkSub = 0;
					dequeue();
				}
				if (isEmpty()) {
					break;
				}
			} else if (isdigit(curr_c)) {
				n = n * 10 + curr_c - '0';
				isBlkSub = 0;
			} else if (curr_c == '-') {
				isNegative = 1;
			}
		}
		if (yes) {
			printf("yes\n");
		} else {
			printf("no\n");
		}

	}
	return 0;
}
