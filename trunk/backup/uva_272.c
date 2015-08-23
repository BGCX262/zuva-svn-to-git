#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

int main(int argc, char * argv[]) {
	int c, flag = 0;
	while ((c = getchar()) != EOF) {
		if (c == '"') {
			if (flag == 0) {
				flag = 1;
				printf("``");
			} else if (flag == 1) {
				flag = 0;
				printf("''");
			}
		} else {
			printf("%c", c);
		}
	}
	return 0;
}
