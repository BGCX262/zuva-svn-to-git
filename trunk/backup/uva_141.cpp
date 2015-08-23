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

bool comp(vector<vector<bool> > & b1, vector<vector<bool> > & b2) {
	int n = b1.size();
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (b1[i][j] != b2[i][j])
				return false;
		}
	}

	//	if (DEBUG) {
	//
	//		cout << "b1" << endl;
	//		for (int i = 0; i < n; i++) {
	//			for (int j = 0; j < n; j++) {
	//				cout << b1[i][j] << " ";
	//			}
	//			cout << endl;
	//		}
	//		cout << "b2" << endl;
	//		for (int i = 0; i < n; i++) {
	//			for (int j = 0; j < n; j++) {
	//				cout << b2[i][j] << " ";
	//			}
	//			cout << endl;
	//		}
	//
	//	}

	return true;
}

int main(int argc, char * argv[]) {
	int n = 0;
	while (cin >> n) {
		if (n == 0) {
			break;
		}

		int moveSize = 2 * n + 1;
		vector<vector<vector<bool> > > board(moveSize);
		vector<vector<vector<bool> > > boardLeft90(moveSize);
		vector<vector<vector<bool> > > boardRight90(moveSize);
		vector<vector<vector<bool> > > board180(moveSize);
		for (int i1 = 0; i1 < moveSize; i1++) {
			board[i1].resize(n + 1);
			boardLeft90[i1].resize(n + 1);
			boardRight90[i1].resize(n + 1);
			board180[i1].resize(n + 1);
			for (int i2 = 1; i2 < n + 1; i2++) {
				board[i1][i2].resize(n + 1, false);
				boardLeft90[i1][i2].resize(n + 1, false);
				boardRight90[i1][i2].resize(n + 1, false);
				board180[i1][i2].resize(n + 1, false);
			}
		}

		int x, y;
		string opr;
		bool gameWin = false;
		int winMove;
		int moveInx;
		for (int move = 1; move < moveSize; move++) {
			cin >> x;
			cin >> y;
			cin >> opr;
			if (gameWin) {
				continue;
			}
			if (DEBUG) {
				cout << x << ", " << y << ", " << opr << endl;
			}

			for (int i1 = 1; i1 < board[move].size(); i1++) {
				for (int i2 = 1; i2 < board[move][i1].size(); i2++) {
					board[move][i1][i2] = board[move - 1][i1][i2];
					boardLeft90[move][i1][i2] = boardLeft90[move - 1][i1][i2];
					boardRight90[move][i1][i2] = boardRight90[move - 1][i1][i2];
					board180[move][i1][i2] = board180[move - 1][i1][i2];
				}
			}

			if (opr == "+") {
				board[move][x][y] = true;
				boardLeft90[move][x][n + 1 - y] = true;
				boardRight90[move][n + 1 - x][y] = true;
				board180[move][n + 1 - x][n + 1 - y] = true;
			} else {
				board[move][x][y] = false;
				boardLeft90[move][x][n + 1 - y] = false;
				boardRight90[move][n + 1 - x][y] = false;
				board180[move][n + 1 - x][n + 1 - y] = false;
			}

			if (DEBUG) {
				cout << "board" << endl;
				for (int i = 1; i <= n; i++) {
					for (int j = 1; j <= n; j++) {
						cout << board[move][i][j] << " ";
					}
					cout << endl;
				}
				cout << "boardLeft90" << endl;
				for (int i = 1; i <= n; i++) {
					for (int j = 1; j <= n; j++) {
						cout << boardLeft90[move][i][j] << " ";
					}
					cout << endl;
				}
				cout << "boardRight90" << endl;
				for (int i = 1; i <= n; i++) {
					for (int j = 1; j <= n; j++) {
						cout << boardRight90[move][i][j] << " ";
					}
					cout << endl;
				}
				cout << "board180" << endl;
				for (int i = 1; i <= n; i++) {
					for (int j = 1; j <= n; j++) {
						cout << board180[move][i][j] << " ";
					}
					cout << endl;
				}
			}

			for (moveInx = 0; moveInx < move; moveInx++) {
				if (comp(board[move], board[moveInx]) || comp(board[move], boardLeft90[moveInx]) || comp(board[move], boardRight90[moveInx])
						|| comp(board[move], board180[moveInx])) {
					gameWin = true;
					winMove = move;
					break;
				}
			}
		}

		if (DEBUG) {
			cout << "move " << moveInx << " with move " << winMove << endl;
		}

		if (gameWin) {
			cout << "Player " << ((moveInx % 2) == 0 ? "1" : "2") << " wins on move " << winMove << endl;
		} else {
			cout << "Draw" << endl;
		}
	}
	return 0;
}
