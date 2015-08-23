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

//see http://www.cnblogs.com/devymex/archive/2010/08/20/1804917.html

int main(int argc, char * argv[]) {
	bool first = true;
	for (int k; cin >> k;) {
		if (first) {
			first = false;
		} else {
			cout << endl;
		}
		for (int row = 1; row <= k; row++) {
			cout << 1;
			for (int col = 1; col <= k - 1; col++) {
				// 1+(k-1)*(row-1) + col
				cout << " " << 1 + (k - 1) * (row - 1) + col;
			}
			cout << endl;
		}

		for (int i = 0; i < (k - 1); i++) {
			for (int j = 0; j < (k - 1); j++) {
				cout << (i + 2);
				for (int s = 0; s < (k - 1); s++) {
					// (j+(s*i))%m + s* (k-1) +k+1;
					cout << " " << (j + (s * i)) % (k - 1) + s * (k - 1) + k + 1;
				}
				cout << endl;
			}
		}
	}
	return 0;
}
