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
string s;
int main(int argc, char * argv[]) {
	string str;
	while (getline(cin, str)) {
		if (str == "#")
			break;
		int len = str.size();
		if (len == 0) {
			cout << "00 00" << endl;
			continue;
		}
		long long crc = 0;
		for (int i = 0; i < len; i++) {
			crc = ((crc << 8) + str[i]) % 34943;
		}
		crc = 34943 - ((crc << 16) % 34943);
		s = "0000";
		int i = 3;
		while (crc != 0) {
			int res = crc % 16;
			if (res < 10) {
				s[i] = res + '0';
			} else {

				s[i] = res - 10 + 'A';
			}
			crc /= 16;
			i--;
		}
		cout << s[0] << s[1] << " " << s[2] << s[3] << endl;
	}
	return 0;
}
