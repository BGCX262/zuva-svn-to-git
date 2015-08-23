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

struct Node {
	set<char> in;
	set<char> out;
};

static int relGrid[26][26];

void init(set<char> & charSet, map<char, struct Node *> & charMap) {
	memset(relGrid, 0, sizeof(relGrid));
	for (set<char>::iterator i = charSet.begin(); i != charSet.end(); i++) {
		delete charMap[*i];
	}
	charMap.clear();
	charSet.clear();
}

void setRelGrid(vector<char>& dfsVec) {
	/*
	 if (DEBUG) {
	 cout << "dfs vector : ";
	 int size = dfsVec.size();
	 for (int i = 0; i < size; i++) {
	 cout << dfsVec[i] << ",";
	 }
	 cout << endl;
	 }
	 */
	int size = dfsVec.size();
	for (int m = 0; m < size - 1; m++) {
		for (int n = m + 1; n < size; n++) {
			relGrid[dfsVec[m] - 'a'][dfsVec[n] - 'a'] = -1;
			relGrid[dfsVec[n] - 'a'][dfsVec[m] - 'a'] = 1;
			/*
			 if (DEBUG) {
			 cout << "relGrid[" << dfsVec[m] << "][" << dfsVec[n] << "] = " << relGrid[dfsVec[m] - 'a'][dfsVec[n] - 'a'] << endl;
			 cout << "relGrid[" << dfsVec[n] << "][" << dfsVec[m] << "] = " << relGrid[dfsVec[n] - 'a'][dfsVec[m] - 'a'] << endl;
			 }
			 */
		}
	}

}

void dfs(char c, map<char, struct Node *> & charMap, vector<char> & dfsVec) {
	dfsVec.push_back(c);
	if (charMap[c]->out.size() == 0) {
		setRelGrid(dfsVec);
		dfsVec.pop_back();
		return;
	}
	for (set<char>::iterator i = charMap[c]->out.begin(); i != charMap[c]->out.end(); i++) {
		dfs(*i, charMap, dfsVec);
	}
}

void buildRelationGrid(set<char> & charSet, map<char, struct Node *> & charMap) {
	vector<char> dfsVec;
	for (set<char>::iterator i = charSet.begin(); i != charSet.end(); i++) {
		if (charMap[*i]->in.size() == 0) {
			dfsVec.clear();
			dfs(*i, charMap, dfsVec);
		}
	}
}

bool verify(string &s) {
	int len = s.size();
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			char c1 = s[i];
			char c2 = s[j];
			if (relGrid[c1 - 'a'][c2 - 'a'] == 1) {
				return false;
			}
		}
	}
	return true;
}

void permutate(string & s, int pos, vector<string> & permVec) {
	if (pos == s.size() - 1) {

		if (verify(s)) {
			permVec.push_back(s);
		}
		return;
	}
	for (int i = pos; i < s.size(); i++) {
		char c = s[pos];
		s[pos] = s[i];
		s[i] = c;
		permutate(s, pos + 1, permVec);
		c = s[pos];
		s[pos] = s[i];
		s[i] = c;
	}
}

bool stringCompare(const string &left, const string &right) {
	for (string::const_iterator lit = left.begin(), rit = right.begin(); lit != left.end() && rit != right.end(); ++lit, ++rit)
		if (tolower(*lit) < tolower(*rit))
			return true;
		else if (tolower(*lit) > tolower(*rit))
			return false;
	if (left.size() < right.size())
		return true;
	return false;
}
int partition(vector<string> & v, int begin, int end) {
	int i, j;
	for (i = begin - 1, j = begin; j < end; j++) {
		if (stringCompare(v[j], v[end]) == true) {
			i++;
			string t = v[j];
			v[j] = v[i];
			v[i] = t;
		}

	}
	i++;
	string t = v[end];
	v[end] = v[i];
	v[i] = t;
	return i;
}

void quickSort(vector<string> & v, int begin, int end) {
	if (begin < end) {
		int pivot = partition(v, begin, end);
		quickSort(v, begin, pivot - 1);
		quickSort(v, pivot + 1, end);
	}
}

int main(int argc, char * argv[]) {
	string str;
	map<char, struct Node *> charMap;
	set<char> charSet;
	bool isCharSet = true;
	bool first = true;
	while (getline(cin, str)) {
		istringstream iss(str);
		if (isCharSet) {
			init(charSet, charMap);
			char c;
			while (iss >> c) {
				charSet.insert(c);
				charMap[c] = new struct Node();
			}
			isCharSet = false;
		} else {
			if (!first) {
				cout << endl;
			} else {
				first = false;
			}

			isCharSet = true;
			char c1, c2;
			while (iss >> c1) {
				iss >> c2;
				/**
				 * c1 < c2 then, c1->c2
				 */
				charMap[c1]->out.insert(c2);
				charMap[c2]->in.insert(c1);
			}

			/*
			 if (DEBUG) {
			 for (set<char>::iterator itr = charSet.begin(); itr != charSet.end(); itr++) {
			 cout << "char " << (*itr) << " has in[";
			 for (set<char>::iterator jtr = charMap[(*itr)]->in.begin(); jtr != charMap[(*itr)]->in.end(); jtr++) {
			 cout << (*jtr) << ",";
			 }
			 cout << "] out[";
			 for (set<char>::iterator jtr = charMap[(*itr)]->out.begin(); jtr != charMap[(*itr)]->out.end(); jtr++) {
			 cout << (*jtr) << ",";
			 }
			 cout << "]" << endl;

			 }
			 }
			 */

			buildRelationGrid(charSet, charMap);
			string s;
			vector<string> permVec;
			for (set<char>::iterator i = charSet.begin(); i != charSet.end(); i++) {
				s += (*i);
			}
			permutate(s, 0, permVec);

			/*			int len = permVec.size();
			 for (int i = 0; i < len; i++) {
			 cout << (permVec[i]) << endl;
			 }

			 cout << "===========================================" << endl;

			 */
			quickSort(permVec, 0, permVec.size() - 1);
			/*			sort(permVec.begin(), permVec.end());*/
			int len = permVec.size();
			for (int i = 0; i < len; i++) {
				cout << (permVec[i]) << endl;
			}

		}

	}
	return 0;
}
