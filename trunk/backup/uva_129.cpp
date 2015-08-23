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

static int n, l, nth;

char chars[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

void printSq(string & s) {
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (i > 0 && i % 64 == 0) {
			cout << endl;
		} else if (i > 0 && i % 4 == 0) {
			cout << " ";
		}
		cout << s[i];
	}
	cout << endl << len << endl;
}

bool verify(string & s) {
	int len = s.size();
	int half = len / 2;
	if (len == 1)
		return true;
	for (int i = 1; i <= half; i++) {
		if (s.substr(len - i, i) == s.substr(len - 2 * i, i)) {
			return false;
		}
	}
	// cout << s << endl;
	return true;
}

bool gen(string & s) {
	if (nth == n) {
		printSq(s);
		return true;
	}
	int len = s.size();
	for (int i = 0; i < l; i++) {
		s.push_back(chars[i]);
		if (verify(s)) {
			nth++;
			if (gen(s)) {
				return true;
			}
		}
		s.erase(len);
	}
	return false;
}

int main(int argc, char * argv[]) {
	string str;
	while (getline(cin, str)) {
		n = 0;
		l = 0;
		istringstream ss(str);
		ss >> n;
		ss >> l;
		if (n == 0)
			break;
		nth = 0;
		string s;
		for (int i = 0; i < l; i++) {
			s.push_back(chars[i]);
			nth++;
			if (gen(s)) {
				break;
			}
			s.erase(0);
		}
	}
	return 0;
}
