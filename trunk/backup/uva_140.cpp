#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <cctype>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <iomanip>

using namespace std;

#define DEBUG 0

void permut(int index, vector<int>& nodeArr, bool graph[26][26], vector<int> & nodeOrder, int & minBandwidth) {
	if (index == nodeArr.size() - 1) {
		int bandwidth = 0;
		int size = nodeArr.size();
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (graph[nodeArr[i]][nodeArr[j]]) {
					if (j - i > bandwidth) {
						bandwidth = j - i;
						if (bandwidth >= minBandwidth) {
							return;
						}
					}
				}
			}
		}
		minBandwidth = bandwidth;
		nodeOrder.clear();
		for (int i = 0; i < size; i++) {
			nodeOrder.push_back(nodeArr[i]);
		}
//		if (DEBUG) {
//			for (int i = 0; i < nodeArr.size(); i++) {
//				cout << char('A' + nodeArr[i]) << " ";
//			}
//			cout << endl;
//			cout << "bandwidth is " << bandwidth << endl;
//		}
		return;
	}

	for (int i = index; i < nodeArr.size(); i++) {
		int t = nodeArr[index];
		nodeArr[index] = nodeArr[i];
		nodeArr[i] = t;
		permut(index + 1, nodeArr, graph, nodeOrder, minBandwidth);
		t = nodeArr[index];
		nodeArr[index] = nodeArr[i];
		nodeArr[i] = t;
	}
}
int main(int argc, char * argv[]) {
	string str, str1;
	while (getline(cin, str)) {
		if (str == "#") {
			break;
		}
		bool graph[26][26] = { false };
		int nodeNum = 0;
		vector<int> nodeArr;
		vector<int> nodeOrder;
		set<char> nodeSet;
		int minBandwidth;
		stringstream ss2(str);
		while (getline(ss2, str1, ';')) {
			char node = str1[0];
			nodeSet.insert(node);
			int nodeI = node - 'A';
			for (int i = 2; i < str1.size(); i++) {
				nodeSet.insert(str1[i]);
				graph[nodeI][str1[i] - 'A'] = true;
				graph[str1[i] - 'A'][nodeI] = true;
			}
		}
		minBandwidth = nodeSet.size();

		for (set<char>::iterator i = nodeSet.begin(); i != nodeSet.end(); i++) {
			nodeArr.push_back((*i) - 'A');
		}

		int size = nodeArr.size();
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (nodeArr[i] > nodeArr[j]) {
					int t = nodeArr[i];
					nodeArr[i] = nodeArr[j];
					nodeArr[j] = t;
				}
			}
		}

		//		if (DEBUG) {
		//			for (int i = 0; i < size - 1; i++) {
		//				cout << char('A' + nodeArr[i]) << " ";
		//			}
		//			cout << endl;
		//		}

		permut(0, nodeArr, graph, nodeOrder, minBandwidth);
		for (int i = 0; i < size; i++) {
			cout << char('A' + nodeOrder[i]) << " ";
		}
		cout << "-> " << minBandwidth << endl;

		//		if (DEBUG) {
		//			for (int i = 0; i < 26; i++) {
		//				for (int j = 0; j < 26; j++) {
		//					if (graph[i][j]) {
		//						cout << "1 ";
		//					} else {
		//						cout << "0 ";
		//					}
		//				}
		//				cout << endl;
		//			}
		//		}
	}
	return 0;
}
