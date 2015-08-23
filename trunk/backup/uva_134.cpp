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

enum symbol {
	NONE, A, MOD, BA, DA, LA, NAM, PREDA, sentence, preclaim, preds, predname, predstring, statement, verbpred
};
bool vowel[26] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
enum symbol nameToSym(string & s) {
	int len = s.size();
	if (!islower(s[len - 1]) || !vowel[s[len - 1] - 'a'])
		return NAM;

	switch (len) {
	case 1:
		return A;
	case 2:
		switch (s[0]) {
		case 'g':
			return MOD;
		case 'b':
			return BA;
		case 'd':
			return DA;
		case 'l':
			return LA;
		}
		break;
	case 5:
		if (!vowel[s[0] - 'a']) {
			if (!vowel[s[1] - 'a']) {
				if (vowel[s[2] - 'a']) {
					if (!vowel[s[3] - 'a']) {
						if (vowel[s[4] - 'a']) {
							//CCVCV
							return PREDA;
						}
					}
				}
			} else {
				if (!vowel[s[2] - 'a']) {
					if (!vowel[s[3] - 'a']) {
						if (vowel[s[4] - 'a']) {
							//CVCCV
							return PREDA;
						}
					}
				}
			}
		}
		break;
	}
	return NONE;
}

enum symbol state[13][4] = {
//  symbol, prefix, suffix, result symbol
		// 1. PREDA + PREDA -> PREDA
		{ PREDA, NONE, PREDA, PREDA },
		// 2. PREDA -> predstring
		{ PREDA, NONE, NONE, predstring },
		// 3. NAM -> predname
		{ NAM, NONE, NONE, predname },
		// 4. LA + predstring -> predname
		{ LA, NONE, predstring, predname },
		// 5. MOD + predstring -> verbpred
		{ MOD, NONE, predstring, verbpred },
		// 6. predstring -> preds
		{ predstring, NONE, NONE, preds },
		// 7. preds + A + preds -> preds
		{ A, preds, preds, preds },
		// 8. predname + verbpred -> statement
		{ predname, NONE, verbpred, statement },
		// 9. statement + predname -> statement
		{ statement, NONE, predname, statement },
		// 10. predname + BA + preds -> preclaim
		{ BA, predname, preds, preclaim },
		// 11. DA + preds -> preclaim
		{ DA, NONE, preds, preclaim },
		// 12. statement -> sentence
		{ statement, NONE, NONE, sentence },
		// 13. preclaim -> sentence
		{ preclaim, NONE, NONE, sentence } };

int main(int argc, char * argv[]) {
	map<enum symbol, string> symMap;
	symMap[NONE] = "NONE";
	symMap[A] = "A";
	symMap[MOD] = "MOD";
	symMap[BA] = "BA";
	symMap[DA] = "DA";
	symMap[LA] = "LA";
	symMap[NAM] = "NAM";
	symMap[PREDA] = "PREDA";
	symMap[sentence] = "sentence";
	symMap[preclaim] = "preclaim";
	symMap[preds] = "preds";
	symMap[predname] = "predname";
	symMap[predstring] = "predstring";
	symMap[statement] = "statement";
	symMap[verbpred] = "verbpred";
	string str1;
	vector<symbol> v;

	for (string str; cin >> str && str != "#";) {
		int dotF = str.find('.');
		if (dotF == str.npos) {
			v.push_back(nameToSym(str));
			continue;
		}
		str.erase(str.length() - 1);
		v.push_back(nameToSym(str));

		//		if (DEBUG) {
		//			cout << "v:" << endl;
		//			for (int k = 0; k < v.size(); k++) {
		//				cout << symMap[v[k]] << "[" << v[k] << "] ";
		//			}
		//			cout << endl;
		//		}
		for (int i = 0; i < 13; i++) {
			for (vector<symbol>::iterator j = v.begin(); j != v.end();) {
				if ((*j) != state[i][0]) {
					// symbo doesn't match
					++j;
					continue;
				}
				if (state[i][1] != NONE && (j == v.begin() || *(j - 1) != state[i][1])) {
					//prefix doesn't match
					++j;
					continue;
				}
				if (state[i][2] != NONE && (j + 1 == v.end() || *(j + 1) != state[i][2])) {
					//suffix doesn't match
					++j;
					continue;
				}

				if (state[i][1] != NONE) {
					// remove prefix
					j = v.erase(j - 1);
				}
				if (state[i][2] != NONE) {
					j = v.erase(j + 1) - 1;
				}

				//				if (DEBUG) {
				//					cout << symMap[(*j)] << "[" << (*j) << "] -> ";
				//				}
				(*j) = state[i][3];
				//				if (DEBUG) {
				//					cout << symMap[(*j)] << "[" << (*j) << "]" << endl;
				//				}
				//				if (DEBUG) {
				//					for (int k = 0; k < v.size(); k++) {
				//						cout << symMap[v[k]] << "[" << v[k] << "] ";
				//					}
				//					cout << endl;
				//				}
			}
		}
		if (v.size() == 1 && v[0] == sentence)
			cout << "Good" << endl;
		else
			cout << "Bad!" << endl;
		v.clear();
	}
	return 0;
}
