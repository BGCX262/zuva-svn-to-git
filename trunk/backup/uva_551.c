#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * uva 551
 */

#define MAX 3333

static char stack[MAX];
static int stackIndex;

void enqueue(char c) {
	stackIndex++;
	stack[stackIndex] = c;
}

char dequeue() {
	char r = stack[stackIndex];
	stackIndex--;
	return r;
}

int empty() {
	return stackIndex < 0;
}

char top() {
	return stack[stackIndex];
}

int isOpening(char c) {
	if (c == '(' || c == '[' || c == '<' || c == '{')
		return 1;
	return 0;
}

int isClosing(char c) {
	if (c == ')' || c == ']' || c == '>' || c == '}')
		return 1;
	return 0;
}

int main() {
	int i, j, count;
	char line[MAX], t;
	while (gets(line) != NULL) {
		stackIndex = -1;
		count = 0;
		int size = strlen(line);
		for (i = 0; i < size; i++) {
			count++;

			if (isOpening(line[i])) {
				if (line[i] == '(' && line[i + 1] == '*') {
					enqueue('*');
					i++;
				} else {
					enqueue(line[i]);
				}
			} else if (isClosing(line[i]) || (line[i] == '*' && line[i + 1] == ')')) {
				if (empty()) {
					break;
				}
				if (line[i] == ')') {

					if (top() != '(') {
						break;
					}
					dequeue();
				} else if (line[i] == ']') {
					if (top() != '[') {
						break;
					}
					dequeue();
				} else if (line[i] == '>') {
					if (top() != '<') {
						break;
					}
					dequeue();
				} else if (line[i] == '}') {
					if (top() != '{') {
						break;
					}
					dequeue();
				} else if (line[i] == '*') {
					if (top() != '*') {
						break;
					}
					dequeue();
					i++;
				}
			}
		}

		if (i < size || !empty()) {
			if (i >= size && !empty()) {
				count++;
			}
			printf("NO %d\n", count);
		} else
			printf("YES\n");
	}

	return 0;
}

