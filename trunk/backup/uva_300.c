#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

/**
 * uva 300
 */

int main() {
	int testN, i, j, haabYear, haabDay, haabMonth, day;
	char haabMonthStr[16], point[16];
	char * haabMonthStrAll[19] = { "pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax",
			"koyab", "cumhu", "uayet" };

	char * tzolkin[20] = { "imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban",
			"eznab", "canac", "ahau" };
	scanf("%d\n", &testN);
	printf("%d\n", testN);
	for (; testN > 0; testN--) {
		scanf("%d %s %s %d\n", &haabDay, point, haabMonthStr, &haabYear);
		for (i = 0; i < 19; i++) {
			if (strcmp(haabMonthStr, haabMonthStrAll[i]) == 0) {
				haabMonth = i;
				break;
			}
		}
		day = 0;
		day += (haabYear * 365);
		day += (haabMonth * 20);
		day += haabDay;

		printf("%d %s %d\n", 1 + (day % 13), tzolkin[day % 20], day / 260);
	}

	return 0;
}

