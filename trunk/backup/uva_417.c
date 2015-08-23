#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * uva 417
 */

#define MAX

static int map1[26], map2[26][26], map3[26][26][26], map4[26][26][26][26], map5[26][26][26][26][26];

void buildMap() {
	int i, j, k, l, m, n, count = 1;

	for (i = 'a'; i <= 'z'; i++) {
		map1[i - 'a'] = count++;
	}
	for (i = 'a'; i <= 'z'; i++) {
		for (j = i + 1; j <= 'z'; j++) {
			map2[i - 'a'][j - 'a'] = count++;
		}
	}
	for (i = 'a'; i <= 'z'; i++) {
		for (j = i + 1; j <= 'z'; j++) {
			for (k = j + 1; k <= 'z'; k++) {
				map3[i - 'a'][j - 'a'][k - 'a'] = count++;
			}
		}
	}
	for (i = 'a'; i <= 'z'; i++) {
		for (j = i + 1; j <= 'z'; j++) {
			for (k = j + 1; k <= 'z'; k++) {
				for (l = k + 1; l <= 'z'; l++) {
					map4[i - 'a'][j - 'a'][k - 'a'][l - 'a'] = count++;
				}
			}
		}
	}

	for (i = 'a'; i <= 'z'; i++) {
		for (j = i + 1; j <= 'z'; j++) {
			for (k = j + 1; k <= 'z'; k++) {
				for (l = k + 1; l <= 'z'; l++) {
					for (m = l + 1; m <= 'z'; m++) {
						map5[i - 'a'][j - 'a'][k - 'a'][l - 'a'][m - 'a'] = count++;
					}
				}
			}
		}
	}

}

int main() {
	int i, re, len;
	char line[128];
	buildMap();
	while (gets(line) != NULL) {
		len = 0;
		for (i = 0; i < strlen(line); i++) {
			if (line[i] >= 'a' && line[i] <= 'z') {
				len++;
			}
		}
		if (len == 1) {
			printf("%d\n", map1[line[0] - 'a']);
		} else if (len == 2) {
			printf("%d\n", map2[line[0] - 'a'][line[1] - 'a']);
		} else if (len == 3) {
			printf("%d\n", map3[line[0] - 'a'][line[1] - 'a'][line[2] - 'a']);
		} else if (len == 4) {
			printf("%d\n", map4[line[0] - 'a'][line[1] - 'a'][line[2] - 'a'][line[3] - 'a']);
		} else if (len == 5) {
			printf("%d\n", map5[line[0] - 'a'][line[1] - 'a'][line[2] - 'a'][line[3] - 'a'][line[4] - 'a']);
		}
	}
	return 0;
}

