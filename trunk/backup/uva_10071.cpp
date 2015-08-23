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

int main(int argc, char * argv[]) {
	string str, str2;
	int v, t;
	while (getline(cin, str)) {
		v = 0;
		t = 0;
		istringstream is(str);
		is >> v;
		is >> t;
		cout << (2 * t * v) << endl;
	}
	return 0;
}
