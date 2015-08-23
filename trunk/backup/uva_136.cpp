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

using namespace std;

#define DEBUG 0

typedef int T;

T inline min(T l1, T l2, T l3) {
	if (l1 <= l2 && l1 <= l3)
		return l1;
	if (l2 <= l1 && l2 <= l3)
		return l2;
	if (l3 <= l1 && l3 <= l2)
		return l3;
}

int main(int argc, char * argv[]) {
	T arr[1500];
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;
	int t2 = 1, t3 = 2, t5 = 4;
	for (int i = 5; i < 1500; i++) {
		while (arr[t2] * 2 <= arr[i - 1]) {
			t2++;
		}
		while (arr[t3] * 3 <= arr[i - 1]) {
			t3++;
		}
		while (arr[t5] * 5 <= arr[i - 1]) {
			t5++;
		}
		arr[i] = min(arr[t2] * 2, arr[t3] * 3, arr[t5] * 5);
//		if (DEBUG) {
//			cout << arr[i] << " " << t2 << "," << t3 << "," << t5 << endl;
//		}
	}
	cout << "The 1500'th ugly number is " << arr[1499] << "." << endl;
	return 0;
}
