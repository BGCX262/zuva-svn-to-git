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

int cutoff(int * reg, int N, int m) {
	int index = 0;
	for (int i = 0; i < N - 1; i++) {
		if (reg[index] == 13) {
			return 0;
		}
		reg[index] = 0;
		for (int j = 0; j < m; j++) {
			index = (index + 1) % N;
			while (reg[index] == 0)
				index = (index + 1) % N;
		}
	}
	return reg[index];
}

int main(int argc, char * argv[]) {
	int N;
	while (cin >> N) {
		if (N == 0)
			break;
		int reg[N];
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < N; j++) {
				reg[j] = j + 1;
			}
			if (cutoff(reg, N, i) == 13) {
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}
