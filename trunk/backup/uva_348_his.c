#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 1

#define max(a,b) (a>b)?a:b

int d[15];
int dp[15][15];
int hub[15][15];

int solve(int a, int b) {
	if (dp[a][b] != -1)
		return dp[a][b];
	if (a == b)
		return dp[a][b] = 0;
	int k;
	for (k = a; k < b; k++) {
		int cost = d[a - 1] * d[k] * d[b] + solve(a, k) + solve(k + 1, b);
		if (dp[a][b] == -1 || cost < dp[a][b]) {
			dp[a][b] = cost;
			hub[a][b] = k;
		}
	}
	return dp[a][b];
}

void path(int a, int b) {
	if (a == b)
		printf("A%d", a);
	else {
		printf("(");
		path(a, hub[a][b]);
		printf(" x ");
		path(hub[a][b] + 1, b);
		printf(")");
	}
}

int main() {
	int n;
	int kase = 1;

	while (scanf("%d", &n), n) {
		int i;
		for (i = 0; i < n; i++)
			scanf("%d %d", d + i, d + i + 1);
		memset(dp, -1, sizeof dp);
		solve(1, n);
		printf("Case %d: ", kase++);
		path(1, n);
		printf("\n");
	}

	return 0;
}
