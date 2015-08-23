#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

#define max(a,b) (a>b)?a:b

int n[6];
int parcel[6][6];

void put(int i, int j, int k) {
	int x, y;
	for (x = i; x <= i + k; x++) {
		for (y = j; y <= j + k; y++) {
			parcel[x][y] = 1;
		}
	}
}

int main() {
	int i, j, numParcel, k, l, x, y;
	for (;;) {
		scanf("%d %d %d %d %d %d\n", n, n + 1, n + 2, n + 3, n + 4, n + 5);
		if (n[0] == 0 && n[1] == 0 && n[2] == 0 && n[3] == 0 && n[4] == 0 && n[5] == 0)
			break;
		numParcel = 0;
		while (n[0] != 0 || n[1] != 0 || n[2] != 0 || n[3] != 0 || n[4] != 0 || n[5] != 0) {
			memset(parcel, 0, sizeof parcel);
			for (i = 0; i < 6; i++) {
				for (j = 0; j < 6; j++) {
					if (parcel[i][j]) {
						continue;
					}
					for (k = 5; k >= 0; k--) {
						if (j + k < 6 && i + k < 6 && n[k] > 0) {
							put(i, j, k);
							n[k]--;
							break;
						}
					}
				}
			}
			numParcel++;
		}
		printf("%d\n", numParcel);
	}
	return 0;
}
