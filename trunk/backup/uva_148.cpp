#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <cctype>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <stack>

using namespace std;

#define DEBUG 0

bool isSigOk(string & s, int sig[26]) {
	for (int i = 0; i < s.size(); i++) {
		if (sig[s[i] - 'A'] == 0)
			return false;
	}
	return true;
}

void setSig(string & s, int sig[26]) {
	for (int i = 0; i < s.size(); i++) {
		sig[s[i] - 'A']--;
	}
}

void unsetSig(string & s, int sig[26]) {
	for (int i = 0; i < s.size(); i++) {
		sig[s[i] - 'A']++;
	}
}

bool isZero(int sig[26]) {
	for (int i = 0; i < 26; i++) {
		if (sig[i] != 0)
			return false;
	}
	return true;
}

bool validate(vector<string> & words, vector<int> & cand, string dic[2000], int dicFltIdx[2000]) {
	int same = 0;
	for (int i = 0; i < cand.size(); i++) {
		for (int j = 0; j < words.size(); j++) {
			if (dic[dicFltIdx[cand[i]]] == words[j]) {
				++same;
				break;
			}
		}
	}
	if (same == cand.size())
		return false;
	return true;
}

int main(int argc, char * argv[]) {
	string line;
	bool isDic = true;
	string dic[2000];
	int dicSize = 0;
	vector<string> phrase;
	while (getline(cin, line)) {
		if (line == "#" && isDic) {
			isDic = false;
			continue;
		} else if (line == "#" && !isDic) {
			break;
		} else if (isDic) {
			dic[dicSize] = line;
			++dicSize;
		} else {
			phrase.clear();
			stringstream ss2(line);
			string word;
			int sig[26];
			memset(sig, 0, 26 * sizeof(int));
			while (getline(ss2, word, ' ')) {
				phrase.push_back(word);
				for (int i = 0; i < word.size(); i++) {
					sig[word[i] - 'A']++;
				}
			}
			// holding filtered dic index
			int dicFltIdx[2000];
			int dicFltIdxSize = 0;
			for (int i = 0; i < dicSize; i++) {
				if (isSigOk(dic[i], sig)) {
					dicFltIdx[dicFltIdxSize] = i;
					++dicFltIdxSize;
				}
			}

			// begin back tracking
			vector<int> cand;
			int p = -1;
			while (true) {
				++p;
//				if (DEBUG) {
//					if (p == dicFltIdxSize) {
//						cout << "p is outof scope " << endl;
//					} else {
//						cout << "p: " << dic[dicFltIdx[p]] << endl;
//					}
//
//					cout << "sig: ";
//					for (int i = 0; i < 26; i++) {
//						cout << sig[i] << " ";
//					}
//					cout << endl;
//					cout << "cand: ";
//					for (int i = 0; i < cand.size(); i++) {
//						cout << dic[cand[i]] << " ";
//					}
//					cout << endl;
//				}
				if (p < dicFltIdxSize) {
					if (isSigOk(dic[dicFltIdx[p]], sig)) {
						cand.push_back(p);
						setSig(dic[dicFltIdx[p]], sig);
						if (isZero(sig) && validate(phrase, cand, dic, dicFltIdx)) {
							for (int i = 0; i < phrase.size(); i++) {
								cout << phrase[i] << " ";
							}
							cout << "= ";
							for (int i = 0; i < cand.size() - 1; i++) {
								cout << dic[dicFltIdx[cand[i]]] << " ";
							}
							cout << dic[dicFltIdx[cand[cand.size() - 1]]] << endl;
						}
					}
				} else {
					if (cand.empty()) {
						break;
					} else {
						p = cand[cand.size() - 1];
						unsetSig(dic[dicFltIdx[cand[cand.size() - 1]]], sig);
						cand.pop_back();
					}
				}
			}
		}
	}
	return 0;
}
