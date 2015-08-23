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
struct Card {
	char rank;
	char suit;
};

inline bool match(struct Card & c1, struct Card & c2) {
	return (c1.rank == c2.rank) || (c1.suit == c2.suit);
}

inline void moveCard(vector<struct Card> & v1, vector<struct Card> & v2) {
	v1.push_back(v2.back());
	v2.pop_back();
}

void printResult(vector<vector<struct Card> > & piles) {
	//6 piles remaining: 40 8 1 1 1 1
	// 1 pile remaining: 52
	if (piles.size() == 1) {
		cout << "1 pile remaining: 52" << endl;
	} else {
		cout << piles.size() << " piles remaining:";
		for (int i = 0; i < piles.size(); i++) {
			cout << " " << piles[i].size();
		}
		cout << endl;
	}
}

void adjust(vector<vector<struct Card> > & piles) {
	int size = piles.size();
	for (vector<vector<struct Card> >::iterator i = piles.begin(); i != piles.end(); i++) {
		if (i - 3 >= piles.begin()) {
			if (match((*(i - 3)).back(), (*i).back())) {
				moveCard(*(i - 3), *(i));
				if ((*i).size() == 0) {
					piles.erase(i);
				}
				adjust(piles);
				return;
			}
		}
		if (i - 1 >= piles.begin()) {
			if (match((*(i - 1)).back(), (*i).back())) {
				moveCard(*(i - 1), *(i));
				if ((*i).size() == 0) {
					piles.erase(i);
				}
				adjust(piles);
				return;
			}
		}
	}
}

int main(int argc, char * argv[]) {
	string str, str2;
	vector<vector<struct Card> > piles;
	int cNum = 0;
	while (cin >> str) {
		if (cNum == 52) {
			printResult(piles);
			piles.clear();
			cNum = 0;
		}
		if (str == "#")
			break;
		Card c;
		c.rank = str[0];
		c.suit = str[1];
		vector<struct Card> v;
		v.push_back(c);
		piles.push_back(v);
		cNum++;
		adjust(piles);
	}
	return 0;
}
