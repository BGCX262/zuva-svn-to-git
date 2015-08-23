#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

#define MAX_LINE 32

int main() {
	char line[MAX_LINE];
	/**
	 * colors in order "r o y g b"
	 */
	char wastes[100][5];
	int nonchange[100][5];
	int total_nonchange[100];
	int max, max_total_nonchange;
	int size = 0, i, j;
	while (scanf("%s", line) == 1) {
		if (line[0] == 'e') {
			for (j = 0; j < 5; ++j) {
				int P = 0, G = 0, S = 0, A = 0, N = 0;
				for (i = 0; i < size; ++i) {
					switch (wastes[i][j]) {
					case 'P':
						++P;
						break;
					case 'G':
						++G;
						break;
					case 'S':
						++S;
						break;
					case 'A':
						++A;
						break;
					case 'N':
						++N;
						break;
					}
				}
				for (i = 0; i < size; ++i) {
					switch (wastes[i][j]) {
					case 'P':
						nonchange[i][j] = P;
						break;
					case 'G':
						nonchange[i][j] = G;
						break;
					case 'S':
						nonchange[i][j] = S;
						break;
					case 'A':
						nonchange[i][j] = A;
						break;
					case 'N':
						nonchange[i][j] = N;
						break;
					}
				}
			}

			for (i = 0; i < size; ++i) {
				total_nonchange[i] = nonchange[i][0] + nonchange[i][1] + nonchange[i][2] + nonchange[i][3] + nonchange[i][4];
			}
			max = 1;
			max_total_nonchange = total_nonchange[0];
			for (i = 1; i < size; ++i) {
				if (total_nonchange[i] > max_total_nonchange) {
					max_total_nonchange = total_nonchange[i];
					max = i + 1;
				}
			}
			if (DEBUG) {
				printf("wastes:\n");
				for (i = 0; i < size; ++i) {
					printf("r/%c o/%c y/%c g/%c b/%c\n", wastes[i][0], wastes[i][1], wastes[i][2], wastes[i][3], wastes[i][4]);
				}
				printf("notchange:\n");
				for (i = 0; i < size; ++i) {
					printf("%d %d %d %d %d total:%d\n", nonchange[i][0], nonchange[i][1], nonchange[i][2], nonchange[i][3], nonchange[i][4], total_nonchange[i]);
				}
				printf("max:%d\n", max);
			} else {
				printf("%d\n", max);
			}
			size = 0;
		} else if (line[0] == '#') {
			break;
		} else {
			for (i = 0; i < 5; ++i) {
				switch (line[i * 4]) {
				case 'r':
					wastes[size][0] = line[i * 4 + 2];
					break;
				case 'o':
					wastes[size][1] = line[i * 4 + 2];
					break;
				case 'y':
					wastes[size][2] = line[i * 4 + 2];
					break;
				case 'g':
					wastes[size][3] = line[i * 4 + 2];
					break;
				case 'b':
					wastes[size][4] = line[i * 4 + 2];
					break;
				}
			}
			++size;
		}
	}
	return 0;
}
