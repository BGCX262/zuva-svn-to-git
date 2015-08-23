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

struct Card {
	char faceC;
	char suitC;
	int suit;
	int face;
};

typedef bool (*pFuc)(int v[4][15]);

bool straight_flush(int v[4][15]) {
	for (int i = 0; i < 4; i++) {
		int seq = 0;
		for (int j = 2; j < 15; j++) {
			if (v[i][j]) {
				seq++;
				if (seq == 5 || (seq == 4 && j == 5 && v[i][14]))
					return true;
			} else {
				seq = 0;
			}
		}
	}
	return false;
}

bool four_of_a_kind(int v[4][15]) {
	for (int j = 2; j < 15; j++) {
		if (v[0][j] && v[1][j] && v[2][j] && v[3][j]) {
			return true;
		}
	}
	return false;
}

bool full_house(int v[4][15]) {
	bool three = false, pair = false;
	int sum;
	for (int j = 2; j < 15; j++) {
		sum = v[0][j] + v[1][j] + v[2][j] + v[3][j];
		if (sum == 3) {
			three = true;
		} else if (sum == 2) {
			pair = true;
		}
		if (three && pair) {
			return true;
		}
	}
	return false;
}

bool flush(int v[4][15]) {
	int sum;
	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (int j = 2; j < 15; j++) {
			sum += v[i][j];
		}
		if (sum == 5)
			return true;
	}
	return false;
}

bool straight(int v[4][15]) {
	int seq = 0;
	for (int j = 2; j < 15; j++) {
		if (v[0][j] || v[1][j] || v[2][j] || v[3][j]) {
			seq++;
			if (seq == 5 || (seq == 4 && j == 5 && (v[0][14] || v[1][14] || v[2][14] || v[3][14])))
				return true;
		} else {
			seq = 0;
		}
	}
	return false;
}

bool three_of_a_kind(int v[4][15]) {
	bool three = false;
	int sum;
	for (int j = 2; j < 15; j++) {
		sum = v[0][j] + v[1][j] + v[2][j] + v[3][j];
		if (sum == 3) {
			three = true;
		}
		if (three) {
			return true;
		}
	}
	return false;
}

bool two_pairs(int v[4][15]) {
	bool pair = false;
	int sum;
	for (int j = 2; j < 15; j++) {
		sum = v[0][j] + v[1][j] + v[2][j] + v[3][j];
		if (sum == 2 && !pair) {
			pair = true;
		} else if (sum == 2 && pair) {
			return true;
		}
	}
	return false;
}
bool one_pair(int v[4][15]) {
	int sum;
	for (int j = 2; j < 15; j++) {
		sum = v[0][j] + v[1][j] + v[2][j] + v[3][j];
		if (sum == 2) {
			return true;
		}
	}
	return false;
}

bool highest_card(int v[4][15]) {
	return true;
}

static pFuc funArr[9] = { straight_flush, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pairs, one_pair, highest_card };

void setValue(struct Card c[5]) {
	for (int i = 0; i < 5; i++) {
		switch (c[i].faceC) {
		case 'T':
			c[i].face = 10;
			break;
		case 'J':
			c[i].face = 11;
			break;
		case 'Q':
			c[i].face = 12;
			break;
		case 'K':
			c[i].face = 13;
			break;
		case 'A':
			c[i].face = 14;
			break;
		default:
			c[i].face = c[i].faceC - '0';
			break;
		}
		switch (c[i].suitC) {
		case 'C':
			c[i].suit = 0;
			break;
		case 'D':
			c[i].suit = 1;
			break;
		case 'H':
			c[i].suit = 2;
			break;
		case 'S':
			c[i].suit = 3;
			break;
		}
	}
}

void bestHand(struct Card c[5], int & bestIdx) {
	int v[4][15] = { 0 };
	for (int i = 0; i < 5; i++) {
		v[c[i].suit][c[i].face] = 1;
	}
	for (int i = 0; i < bestIdx; i++) {
		if (funArr[i](v)) {
			//			for (int m = 0; m < 4; m++) {
			//				for (int n = 2; n < 15; n++) {
			//					cout << "[" << m << "," << n << "]" << v[m][n] << " ";
			//				}
			//				cout << endl;
			//			}
			//			cout << "best hand is " << i << endl;
			bestIdx = i;
			return;
		}
	}
}

void permut(struct Card hand[5], struct Card deck[5], int deckIdx, int & bestIdx) {

//	cout << "deckIdex:" << deckIdx << ", bestIdx:" << bestIdx << endl;
//	cout << "Hand: ";
//	for (int i = 0; i < 5; i++) {
//		cout << hand[i].faceC << hand[i].suitC << " ";
//	}
//	cout << "Deck: ";
//	for (int i = 0; i < 5; i++) {
//		cout << deck[i].faceC << deck[i].suitC << " ";
//	}
//	cout << endl;

	bestHand(hand, bestIdx);

	if (deckIdx == 5)
		return;

	struct Card temp;
	for (int i = deckIdx; i < 5; i++) {
		temp = hand[deckIdx];
		hand[deckIdx] = hand[i];
		hand[i] = temp;
		temp = hand[deckIdx];
		hand[deckIdx] = deck[deckIdx];
		permut(hand, deck, deckIdx + 1, bestIdx);
		hand[deckIdx] = hand[i];
		hand[i] = temp;
	}
}

//void bestHand(struct Card c1[5], struct Card c2[5], int & bestIdx) {
//	int v[4][15] = { 0 };
//	for (int i = 0; i < 5; i++) {
//		v[c1[i].suit][c1[i].face] = 1;
//		v[c2[i].suit][c2[i].face] = 1;
//	}
//	for (int i = 0; i < bestIdx; i++) {
//		if (funArr[i](v)) {
//			for (int m = 0; m < 4; m++) {
//				for (int n = 2; n < 15; n++) {
//					cout << "[" << m << "," << n << "]" << v[m][n] << " ";
//				}
//				cout << endl;
//			}
//			cout << "best hand is " << i << endl;
//			bestIdx = i;
//			return;
//		}
//	}
//}

int main(int argc, char * argv[]) {
	string best[9] = { "straight-flush", "four-of-a-kind", "full-house", "flush", "straight", "three-of-a-kind", "two-pairs", "one-pair", "highest-card" };
	string str;
	while (getline(cin, str)) {
		string strCard;
		int bestIdx;
		struct Card hand[5], deck[5];
		bestIdx = 9;
		istringstream ss(str);
		for (int i = 0; i < 5; i++) {
			getline(ss, strCard, ' ');
			hand[i] = Card();
			hand[i].faceC = strCard[0];
			hand[i].suitC = strCard[1];
		}
		for (int i = 0; i < 5; i++) {
			getline(ss, strCard, ' ');
			deck[i] = Card();
			deck[i].faceC = strCard[0];
			deck[i].suitC = strCard[1];
		}
		setValue(hand);
		setValue(deck);
		//		bestHand(hand, deck, bestIdx);
		bestHand(hand, bestIdx);
		permut(hand, deck, 0, bestIdx);

		cout << "Hand: ";
		for (int i = 0; i < 5; i++) {
			cout << hand[i].faceC << hand[i].suitC << " ";
		}
		cout << "Deck: ";
		for (int i = 0; i < 5; i++) {
			cout << deck[i].faceC << deck[i].suitC << " ";
		}
		cout << "Best hand: " << best[bestIdx];
		cout << endl;
	}
	return 0;
}
