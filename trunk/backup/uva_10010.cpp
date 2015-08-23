#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
using namespace std;

#define DEBUG 0
static int m = 0, n = 0, k = 0, cases = 0, x = 0, y = 0;
static char grid[50][50];

void getLocation(string & s) {
	// trim the string
	stringstream mt;
	mt << s;
	s.clear();
	mt >> s;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int idx = 0, len = s.length();
			if (j + len - 1 < n) {
				idx = 0;
				for (; idx < len; idx++) {
					if (toupper(grid[i][j + idx]) != toupper(s[idx]))
						break;
				}
			}
			if (idx != len && j - (len - 1) >= 0) {
				idx = 0;
				for (; idx < len; idx++) {
					if (toupper(grid[i][j - idx]) != toupper(s[idx]))
						break;
				}
			}
			if (idx != len && i + len - 1 < m) {
				idx = 0;
				for (; idx < len; idx++) {
					if (toupper(grid[i + idx][j]) != toupper(s[idx]))
						break;
				}
			}
			if (idx != len && i - (len - 1) >= 0) {

				idx = 0;
				for (; idx < len; idx++) {
					if (toupper(grid[i - idx][j]) != toupper(s[idx]))
						break;
				}
			}
			if (idx != len && j + len - 1 < n && i + len - 1 < m) {
				idx = 0;
				for (; idx < len; idx++) {
					if (toupper(grid[i + idx][j + idx]) != toupper(s[idx]))
						break;
				}
			}
			if (idx != len && i - (len - 1) >= 0 && j - (len - 1) >= 0) {
				idx = 0;
				for (; idx < len; idx++) {
					if (toupper(grid[i - idx][j - idx]) != toupper(s[idx]))
						break;
				}
			}
			if (idx == len) {
				x = i;
				y = j;
				return;
			}
		}
	}
	return;
}

int main(int argc, char * argv[]) {
	string str;
	getline(cin, str);
	istringstream ss(str);
	ss >> cases;

	bool firstCase = true;
	for (int i = 0; i < cases; i++) {
		getline(cin, str);
		getline(cin, str);
		istringstream ss2(str);
		ss2 >> m;
		ss2 >> n;
		for (int j = 0; j < m; j++) {
			getline(cin, str);
			for (int k = 0; k < n; k++) {
				grid[j][k] = str[k];
			}
		}
		getline(cin, str);
		istringstream ss3(str);
		ss3 >> k;
		if (!firstCase) {
			cout << endl;
		} else {
			firstCase = false;
		}
		for (int j = 0; j < k; j++) {
			getline(cin, str);
			getLocation(str);
			cout << (x + 1) << " " << (y + 1) << endl;
		}
	}
	return 0;
}
