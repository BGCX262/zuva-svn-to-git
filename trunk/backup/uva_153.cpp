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

void cal_perm(string & s, int index, long long & totalSum) {
	if (DEBUG) {
		cout << "index:" << index << " sum:" << totalSum << endl;
	}

	if (index == s.size() - 1)
		return;

	int numChar[26];
	memset(numChar, 0, sizeof(int) * 26);
	for (int i = index; i < s.size(); i++) {
		++numChar[s[i] - 'a'];
	}
	/**
	 * x1 for number of a
	 * x2 for number of b
	 * ...
	 *
	 * sum = (f1)! / (x1! * x2! * ... * xn!)
	 * where f1 = (x1+x2+..+xn)
	 */
	for (int i = 0; i < (s[index] - 'a'); i++) {
		if (numChar[i] == 0)
			continue;

		--numChar[i];

		int maxNumChar = 0;
		int maxNumIndex = 0;
		for (int j = 0; j < 26; j++) {
			if (numChar[j] == 0)
				continue;
			if (maxNumChar < numChar[j]) {
				maxNumChar = numChar[j];
				maxNumIndex = j;
			}
		}

		long long sum = 1;
		for (int j = s.size() - index - 1; j > maxNumChar; j--) {
			sum *= j;
		}
		for (int j = 0; j < 26; j++) {
			if (numChar[j] == 0 || j == maxNumIndex)
				continue;
			int fact = 1;
			for (int k = 1; k <= numChar[j]; k++) {
				fact *= k;
			}
			sum /= fact;
		}
		++numChar[i];
		if (DEBUG) {
			cout << "sum:" << sum << endl;
		}
		totalSum += sum;
	}
	cal_perm(s, index + 1, totalSum);
}

int main(int argc, char * argv[]) {
	string s;
	while (cin >> s) {
		if (s == "#")
			break;
		if (DEBUG)
			cout << "s:" << s << endl;
		int index = 0;
		long long sum = 1;
		cal_perm(s, 0, sum);
		if (!DEBUG)
			cout << setw(10) << sum << endl;
		else
			cout << "sum:" << sum << endl;
	}
	return 0;
}
