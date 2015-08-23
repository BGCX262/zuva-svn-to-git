#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <cctype>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <stack>
#include <algorithm>

using namespace std;

#define DEBUG 0

int main(int argc, char * argv[]) {
	int x, y, z;
	double xArr[5000], yArr[5000], zArr[5000];
	long double d2Arr[5000];
	int histogram[10];
	memset(histogram, 0, sizeof(int) * 10);
	int size = 0;
	while (true) {
		cin >> x;
		cin >> y;
		cin >> z;
		if (x == 0 && y == 0 && z == 0)
			break;

		long double minD = 255 * 255 + 255 * 255 + 255 * 255;
		for (int i = 0; i < size; i++) {
			long double d2T = pow(xArr[i] - x, 2) + pow(yArr[i] - y, 2) + pow(zArr[i] - z, 2);
			if (d2T < d2Arr[i]) {
				d2Arr[i] = d2T;
			}
			if (d2T < minD) {
				minD = d2T;
			}
		}
		xArr[size] = x;
		yArr[size] = y;
		zArr[size] = z;
		d2Arr[size] = minD;
		++size;
	}
	for (int i = 0; i < size; i++) {
		int d = (int) sqrt(d2Arr[i]);
		if (d < 10)
			histogram[d]++;
	}
	if (!DEBUG) {
		for (int i = 0; i < 10; i++) {
			cout << setw(4);
			cout << histogram[i];
		}
		cout << endl;
	}

	if (DEBUG) {
		for (int i = 0; i < size; i++) {
			cout << "(" << xArr[i] << "," << yArr[i] << "," << zArr[i] << ") ";
			if (i > 0 && i % 11 == 0)
				cout << endl;
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << d2Arr[i] << " ";
			if (i > 0 && i % 11 == 0)
				cout << endl;
		}
		cout << endl;
		for (int i = 0; i < 10; i++) {
			cout << histogram[i] << " ";
		}
		cout << endl;

	}
	return 0;
}
