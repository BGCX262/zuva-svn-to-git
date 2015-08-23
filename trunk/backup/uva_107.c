#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DEBUG 0
/**
 * logn (x) = (log(x)) / (log(n))
 */
float lognx(int n, int x) {
	float result = log(x) / log(n);
	return result;
}

long long nx(int n, int x) {
	if (x == 0)
		return 1;
	int i = 1;
	long long result = 1;
	while (i++ <= x) {
		result = result * n;
	}
	return result;
}

int getNumNoWork(int n, int numWork) {
	if (n == 1)
		return 1;
	return (numWork - 1) / (n - 1);
}

long long getHeightAll(int n, int heightIni, int numWorker) {
	long long t1 = heightIni * (n + 1);
	long long t2 = heightIni / nx(n + 1, lognx(n, numWorker) ) ;
	long long t3 = numWorker * n;
	if (DEBUG) {
		printf("t1:%lld, t2:%lld, t3:%lld\n", t1, t2, t3);
	}
	return t1 - t2*t3;
}

int main(int argc, char * argv[]) {
	int n, heightIni, numWorker, height;
	while (scanf("%d %d\n", &heightIni, &numWorker) == 2) {
		if (heightIni == 0 && numWorker == 0) {
			break;
		}
		if (DEBUG) {
			printf("heightIni:%d, numWorker:%d\n", heightIni, numWorker);
		}
		if (heightIni == 1) {
			printf("0 1\n");
			continue;
		}
		if (numWorker == 1) {
			printf("%d %d\n", (int) lognx(2, heightIni), 2 * heightIni - 1);
			continue;
		}
		n = 2;
		while (lognx(n + 1, heightIni) != lognx(n, numWorker)) {
			n++;
		}
		if (DEBUG) {
			printf("n:%d\n", n);
		}
		printf("%d %lld\n", getNumNoWork(n, numWorker), getHeightAll(n, heightIni, numWorker));
	}
	return 0;
}
