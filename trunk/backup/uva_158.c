#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

struct Date {
	int day;
	int month;
};

struct Ann {
	struct Date date;
	int p;
	char desc[256];
	struct Ann * next;
};

static int monthDays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
static int monthDaysLeap[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

static struct Date dates[365];
static int dateSize = 0;
static struct Ann * anns[366];

void printInfo() {
	int i, j;
	struct Ann * a;
	printf("Anniversary:\n");
	for (i = 0; i < 366; i++) {
		a = anns[i];
		if (a != NULL) {
			printf("[%d] ", i);
			printf("%d %d %d %s ", a->date.day, a->date.month, a->p, a->desc);
			while (a->next != NULL) {
				a = a->next;
				printf(" => %d %d %d %s ", a->date.day, a->date.month, a->p, a->desc);
			}
			printf("\n");
		}
	}
	printf("Dates:\n");
	for (i = 0; i < dateSize; i++) {
		printf("[%d] %d %d\n", i, dates[i].day, dates[i].month);
	}
}

struct Ann * alloc(int d, int m, int p, char desc[]) {
	struct Ann * n = (struct Ann *) malloc(sizeof(struct Ann));
	n->date.day = d;
	n->date.month = m;
	n->p = p;
	int i, size = 0, first = 1;

	for (i = 0; i < strlen(desc); i++) {
		if (first && isspace(desc[i]))
			continue;
		first = 0;
		n->desc[size++] = desc[i];
	}
	n->desc[size - 1] = '\0';
	n->next = NULL;
	return n;
}

int getIndex(int y, struct Date* date) {
	if (y % 4 == 0) {
		/*
		 * leap year
		 */
		return monthDaysLeap[date->month - 1] + date->day - 1;
	} else {
		return monthDays[date->month - 1] + date->day - 1;
	}
}

int main(int argv, char * argc[]) {
	int r, year, day, month, pri, i;
	for (r = 0; r < 366; r++) {
		anns[r] = NULL;
	}

	char str[256];
	r = scanf("%d", &year);
	while (1) {
		r = scanf("%s", str);
		if (strcmp(str, "#") == 0)
			break;
		if (strcmp(str, "A") == 0) {
			r = scanf("%d", &day);
			r = scanf("%d", &month);
			r = scanf("%d", &pri);
			/*r = scanf("%s[^\n]", str);*/
			char * c = fgets(str, 256, stdin);
			struct Ann * a = alloc(day, month, pri, str);
			int id = getIndex(year, &a->date);
			if (anns[id] == NULL) {
				anns[id] = a;
			} else {
				struct Ann * cur = anns[id];
				while (cur->next != NULL) {
					cur = cur->next;
				}
				cur->next = a;
			}
		} else if (strcmp(str, "D") == 0) {
			r = scanf("%d", &day);
			r = scanf("%d", &month);
			struct Date d;
			d.day = day;
			d.month = month;
			dates[dateSize++] = d;
		}
	}

	for (i = 0; i < dateSize; i++) {
		if (i > 0)
			printf("\n");

		printf("Today is:%3d%3d\n", dates[i].day, dates[i].month);
		int id = getIndex(year, &dates[i]);
		if (anns[id] != NULL) {
			struct Ann * a = anns[id];
			while (a != NULL) {
				printf("%3d%3d *TODAY* %s\n", a->date.day, a->date.month, a->desc);
				a = a->next;
			}
		}

		int id2, j, k, kk;
		int daysDec = ((year % 4 == 0) ? monthDaysLeap[11] + 31 : monthDays[11]) + 31;
		for (j = 1, id2 = (j + id) % daysDec; j <= 7; j++, id2 = (j + id) % daysDec) {

			/*printf("id2:%d \n",id2);*/

			if (anns[id2] == NULL)
				continue;
			struct Ann * arr[16];
			int arrSize = 0;
			struct Ann * a = anns[id2];
			while (a != NULL) {
				if (a->p >= j) {
					arr[arrSize++] = a;
				}
				a = a->next;
			}
			for (k = 0; k < arrSize - 1; k++) {
				int max = k;
				for (kk = k + 1; kk < arrSize; kk++) {
					if (arr[max]->p < arr[kk]->p) {
						max = kk;
					}
				}
				if (max != k) {
					struct Ann* temp = arr[k];
					arr[k] = arr[max];
					arr[max] = temp;
				}
			}

			for (k = 0; k < arrSize; k++) {
				printf("%3d%3d ", arr[k]->date.day, arr[k]->date.month);
				int howManyP = arr[k]->p - j + 1;
				for (kk = 1; kk <= 7; kk++) {
					if (kk <= howManyP)
						printf("*");
					else
						printf(" ");
				}
				printf(" %s\n", arr[k]->desc);
			}
		}
	}

	if (DEBUG) {
		printInfo();
	}
	return 0;
}
