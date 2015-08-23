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
	string line1;
	map<string, set<string> > countries;
	int n;
	getline(cin, line1);
	istringstream is(line1);
	is >> n;
	for (int i = 0; i < n; i++) {
		getline(cin, line1);
		stringstream ss(line1);
		string country;
		ss >> country;
		string name, word;
		while (ss >> word) {
			name = name + word;
		}
		if (DEBUG) {
			cout << "name:" << name << endl;
		}
		map<string, set<string> >::iterator it = countries.find(country);
		if (it == countries.end()) {
			set<string> names;
			names.insert(name);
			countries[country] = names;
		} else {
			it->second.insert(name);
		}
	}
	for (map<string, set<string> >::iterator it = countries.begin(); it != countries.end(); it++) {
		cout << (*it).first << " " << (*it).second.size() << endl;
	}

	return 0;
}
