#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

int max(int i, int j) {
	if (i < j) {
		return j;
	} else {
		return i;
	}
}

int cal_stu_points(int events[], int stu_events[], int n) {
	int i, j, lcs_len[n + 1][n + 1];
	if (DEBUG) {
		printf("events: ");
		for (i = 0; i < n; i++) {
			printf("%d ", events[i]);
		}
		printf("\nstudent events: ");
		for (i = 0; i < n; i++) {
			printf("%d ", stu_events[i]);
		}
		printf("\n");
	}
	for (i = 0; i < n + 1; i++) {
		lcs_len[0][i] = 0;
		lcs_len[i][0] = 0;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (events[i] == stu_events[j]) {
				lcs_len[i + 1][j + 1] = lcs_len[i][j] + 1;
			} else {
				lcs_len[i + 1][j + 1] = max(lcs_len[i][j + 1], lcs_len[i + 1][j]);
			}
		}
	}
	if (DEBUG) {
		printf("LCS Length:\n");
		for (i = 0; i < n + 1; i++) {
			for (j = 0; j < n + 1; j++) {
				printf("%d ", lcs_len[i][j]);
			}
			printf("\n");
		}

	}
	return lcs_len[n][n];
}

int main(int argc, char * argv[]) {
	int n, events[20], stu_events[20], i, t, rank;
	scanf("%d\n", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &rank);
		events[rank - 1] = i + 1;
	}
	i = 0;
	while (scanf("%d", &rank) != EOF) {
		stu_events[rank - 1] = i + 1;
		i++;
		if (i == n) {
			printf("%d\n", cal_stu_points(events, stu_events, n));
			i = 0;
		}
	}
	return 0;
}
