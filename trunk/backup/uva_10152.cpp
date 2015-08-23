#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

#define DEBUG 0

int main(int argc, char * argv[]) {
	string line;
	int testNum;
	getline(cin, line);
	stringstream ss;
	ss << line;
	ss >> testNum;
	for (int t = 0; t < testNum; t++) {
		map<string, int> index;
		vector<string>::iterator it1, it2;
		vector<string> desired, original;
		int lineNum;
		getline(cin, line);
		ss.clear();
		ss << line;
		ss >> lineNum;
		for (int i = 0; i < lineNum; i++) {
			getline(cin, line);
			original.push_back(line);
		}
		for (int i = 0; i < lineNum; i++) {
			getline(cin, line);
			index[line] = i;
			desired.push_back(line);
		}
		int maxIndex = -1;
		for (it2 = it1 = original.begin(), it2++; it2 != original.end(); it1++, it2++) {
			int index1 = index[*it1], index2 = index[*it2];
			if (index1 > index2) {
				if (index2 > maxIndex) {
					maxIndex = index2;
				}
			}
		}
		for (int i = maxIndex; i >= 0; i--) {
			cout << desired[i] << endl;
		}
		cout << endl;
	}
	return 0;
}
