#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <iomanip>

using namespace std;

#define DEBUG 0

typedef int T;

int main(int argc, char * argv[]) {
	T arrX[11], arrY[11];
	T x1 = 3, y1 = 2;
	arrX[0] = 3;
	arrY[0] = 2;
	for (int i = 1; i < 11; i++) {
		arrX[i] = x1 * arrX[i - 1] + 2 * y1 * arrY[i - 1];
		arrY[i] = x1 * arrY[i - 1] + y1 * arrX[i - 1];
		cout << setw(10) << (arrY[i] / 2) << setw(10) << ((arrX[i] - 1) / 2) << endl;
	}
	return 0;
}
