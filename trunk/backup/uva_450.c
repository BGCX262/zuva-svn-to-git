#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

/**
 * uva 450
 */

#define max 20001

struct Info {
	char dept[61];
	char title[26];
	char first[26];
	char last[26];
	char address[51];
	char home[51];
	char work[31];
	char mail[31];
} in[max];

int inSize;

int cmp_info(const void * a, const void * b) {
	return strcmp(((struct Info *) a)->last, ((struct Info *) b)->last);
}

int main() {
	int i, j, n;
	char line[1024], department[61];
	scanf("%d\n", &n);
	inSize = 0;
	for (i = 0; i < n; i++) {
		gets(line);
		strcpy(department, line);
		while (gets(line) != NULL) {
			if (strlen(line) < 3) {
				break;
			}

			strcpy(in[inSize].dept, department);
			char* token = strtok(line, ",");
			strcpy(in[inSize].title, token);
			token = strtok(NULL, ",");
			strcpy(in[inSize].first, token);
			token = strtok(NULL, ",");
			strcpy(in[inSize].last, token);
			token = strtok(NULL, ",");
			strcpy(in[inSize].address, token);
			token = strtok(NULL, ",");
			strcpy(in[inSize].home, token);
			token = strtok(NULL, ",");
			strcpy(in[inSize].work, token);
			token = strtok(NULL, ",");
			strcpy(in[inSize].mail, token);
			inSize++;
		}
	}

	qsort(in, inSize, sizeof(struct Info), cmp_info);

	for (i = 0; i < inSize; i++) {
		printf("----------------------------------------\n");
		printf("%s %s %s\n", in[i].title, in[i].first, in[i].last);
		printf("%s\n", in[i].address);
		printf("Department: %s\n", in[i].dept);
		printf("Home Phone: %s\n", in[i].home);
		printf("Work Phone: %s\n", in[i].work);
		printf("Campus Box: %s\n", in[i].mail);
	}

	return 0;
}

