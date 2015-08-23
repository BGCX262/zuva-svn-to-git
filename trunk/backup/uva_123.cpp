#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <cctype>
#include <vector>
using namespace std;

#define DEBUG 0

void ConvertToLowerCase(string & str) {
	int length = str.size();
	for (int i = 0; i < length; ++i) {
		str[i] = tolower(str[i]);
	}
}

void ConvertToUpperCase(string & str) {
	int length = str.size();
	for (int i = 0; i < length; ++i) {
		str[i] = toupper(str[i]);
	}
}

/*
int Partition(vector<string> & keyV, int begin, int end) {
	int i = begin - 1, j = end - 1;
	while (j >= 0) {
		if (keyV[j] < keyV[end]) {
			i++;
			string t = keyV[j];
			keyV[j] = keyV[i];
			keyV[i] = t;
		}
		j--;
	}
	i++;
	string t = keyV[i];
	keyV[i] = keyV[end];
	keyV[end] = t;
	return i;
}

void QuickSort(vector<string> & keyV, int begin, int end) {
	if (DEBUG) {
		cout << "begin " << begin << " end " << end << endl;
	}
	int pivot = Partition(keyV, begin, end);
	if (DEBUG) {
		cout << "pivot " << pivot << endl;
	}
	if (pivot - 1 > begin)
		QuickSort(keyV, begin, pivot - 1);
	if (pivot + 1 < end)
		QuickSort(keyV, pivot + 1, end);
}
*/

int main(int argc, char * argv[]) {
	string str;
	set<string> ignore;
	vector<string> sens;
	set<string> keysSet;
	map<string, vector<string> > keysMap;
	bool beginSen = false;
	while (getline(cin, str)) {
		if (str.compare("::") == 0) {
			beginSen = true;
			continue;
		}
		if (!beginSen) {
			ignore.insert(str);
		} else {
			ConvertToLowerCase(str);
			sens.push_back(str);
		}
	}
	/**
	 * build all keys' map
	 */

	for (vector<string>::iterator senItr = sens.begin(); senItr != sens.end(); senItr++) {
		istringstream iss(*senItr);
		string word;
		int word_begin = -1;
		while (getline(iss, word, ' ')) {
			set<string>::iterator iFound = ignore.find(word);
			if (iFound == ignore.end()) {
				/**
				 * word is key then create/update this key's map
				 */
				if (DEBUG) {
					cout << "Key '" << word << "' in '" << *senItr << "'" << endl;
				}
				keysSet.insert(word);
				/**
				 * create sentence which is been replaced upper case key word
				 */
				word_begin = (*senItr).find(word, word_begin + 1);
				/**
				 * cout << "word_begin " << word_begin << endl;
				 */
				string sen = (*senItr).substr(0, word_begin);
				string upWord(word);
				ConvertToUpperCase(upWord);
				sen += upWord;
				sen += (*senItr).substr(word_begin + upWord.size());
				if (DEBUG) {
					cout << "converted sentence : " << sen << endl;
				}
				vector<string> sensOfKey;
				map<string, vector<string> >::iterator pos = keysMap.find(word);
				if (pos == keysMap.end()) {
					keysMap[word] = sensOfKey;
				}
				keysMap[word].push_back(sen);
			}
		}
	}

	for (set<string>::iterator it = keysSet.begin(); it != keysSet.end(); it++) {
		vector<string> sensKey = keysMap[(*it)];
		int i, len = sensKey.size();
		for (i = 0; i < len; i++) {
			cout << sensKey[i] << endl;
		}
	}

	/*
	 vector<string> keyVec;
	 for (set<string>::iterator it = keysSet.begin(); it != keysSet.end(); it++)
	 keyVec.push_back(*it);

	 if (DEBUG) {
	 cout << "before sort : ";
	 int i;
	 for (i = 0; i < keyVec.size(); i++) {
	 cout << keyVec[i] << " ";
	 }
	 cout << endl;
	 }

	 QuickSort(keyVec, 0, keyVec.size() - 1);
	 if (DEBUG) {
	 cout << "after sort : ";
	 int i;
	 for (i = 0; i < keyVec.size(); i++) {
	 cout << keyVec[i] << " ";
	 }
	 cout << endl;
	 }
	 */

	return 0;
}
