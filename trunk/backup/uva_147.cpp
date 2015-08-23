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

using namespace std;

#define DEBUG 1

//static int coins[11] = { 2000, 1000, 400, 200, 100, 40, 20, 10, 4, 2, 1 };
static int coins[11] = { 1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000 };
static long long amounts[6001] = { 1 };

int main(int argc, char * argv[]) {
	float inputNum;

	for (int coin = 0; coin < 11; coin++) {
		for (int j = coins[coin]; j < 6001; j++) {
			amounts[j] += amounts[j - coins[coin]];
		}
	}

	cout << fixed << showpoint << setprecision(2);
	while (cin >> inputNum) {
		if (inputNum == 0)
			break;
		cout << setw(6) << inputNum << setw(17) << amounts[(int) (inputNum * 20 + 0.5)] << endl;
	}
	return 0;
}

// this way is too slow
//static int coins[11] = { 2000, 1000, 400, 200, 100, 40, 20, 10, 4, 2, 1 };
//
//void count(float amount, int cIndex, long int & madeUp) {
//	if (amount == 0) {
//		madeUp++;
//		return;
//	}
//	if (cIndex == 11) {
//		return;
//	}
//	for (int i = 0; coins[cIndex] * i <= amount; i++) {
//		count(amount - coins[cIndex] * i, cIndex + 1, madeUp);
//	}
//}
//
//int main(int argc, char * argv[]) {
//	float amount;
//	while (cin >> amount) {
//		if (amount == 0)
//			break;
//		long int madeUp = 0;
//		count(amount * 20, 0, madeUp);
//		printf("%6.2lf%17ld\n", amount, madeUp);
//	}
//	return 0;
//}

