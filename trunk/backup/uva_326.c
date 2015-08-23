#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define DEBUG 0

int table[10][10], table_k[10];

int main() {
	int i, j, n, k;

	for (;;) {
		scanf("%d", &n);
		if (n == 0)
			break;
		memset(table, 0, 10 * 10 * sizeof(int));
		memset(table_k, 0, 10 * sizeof(int));
		for (i = 0; i < n; i++) {
			scanf("%d", &table[i][0]);
		}
		scanf("%d", &k);

		for (j = 1; j < n; j++) {
			for (i = 0; i < (n - j); i++) {
				table[i][j] = table[i + 1][j - 1] - table[i][j - 1];
			}
		}

		for (i = 0; i < n; i++) {
			table_k[i] = table[n - 1 - i][i];
		}

		for (i = 0; i < k; i++) {
			for (j = n - 2; j >= 0; j--) {
				table_k[j] = table_k[j] + table_k[j + 1];
			}
		}

		printf("Term %d of the sequence is %d\n", (n + k), table_k[0]);

		if (DEBUG) {
			for (i = 0; i < 10; i++) {
				for (j = 0; j < 10; j++) {
					printf("[%d][%d]%d ", i, j, table[i][j]);
				}
				printf("\n");
			}
			for (i = 0; i < 10; i++) {
				printf("[%d]%d ", i, table_k[i]);
			}
			printf("\n\n");
		}

	}

	return 0;
}
