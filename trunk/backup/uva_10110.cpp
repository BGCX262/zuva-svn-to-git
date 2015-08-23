#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

#define DEBUG 0

int main(int argc, char * argv[]) {
	string line;
	while (getline(cin, line)) {
		if (line == "0")
			break;
		unsigned long n;
		stringstream ss;
		ss << line;
		ss >> n;
		unsigned long t = (unsigned long) sqrt(n);
		if (t * t != n)
			cout << "no" << endl;
		else
			cout << "yes" << endl;
	}
	return 0;
}
