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

struct Node {
	int value;
	struct Node * left;
	struct Node * right;
};

inline void del(struct Node * p) {
	if (DEBUG) {
		cout << "del:" << p->value << endl;
	}
	if (p->right != NULL) {
		p->right->left = p->left;
	}
	if (p->left != NULL) {
		p->left->right = p->right;
	}
	delete p;
}

inline void output(int n) {
	if (n < 10)
		cout << "  " << n;
	else
		cout << " " << n;
}

int main(int argc, char * argv[]) {
	string str1;
	int n, k, m;
	while (getline(cin, str1)) {
		istringstream ss1(str1);
		ss1 >> n;
		ss1 >> k;
		ss1 >> m;
		if (n == 0 && k == 0 && m == 0)
			break;
		struct Node * off1;
		struct Node * off2;
		struct Node * curr = NULL;
		for (int i = 1; i <= n; i++) {
			struct Node * t = new struct Node;
			t->value = i;
			t->left = curr;
			t->right = NULL;
			if (curr != NULL) {
				curr->right = t;
			} else {
				off1 = t;
			}
			curr = t;
		}
		off2 = curr;
		off2->right = off1;
		off1->left = off2;
		int i = 0;
		while (true) {
			int counter = k;
			if (DEBUG) {
				cout << "off1:" << off1->value << ", off2:" << off2->value << endl;
			}
			while (--counter > 0) {
				off1 = off1->right;
			}
			counter = m;
			while (--counter > 0) {
				off2 = off2->left;
			}
			if (DEBUG) {
				cout << "jump to off1:" << off1->value << ", off2:" << off2->value << endl;
			}

			if (off1 == off2) {
				output(off1->value);
				off1 = off1->right;
				off2 = off2->left;
				del(off1->left);
				i++;
			} else {
				output(off1->value);
				output(off2->value);
				if (off1->right == off2) {
					off1 = off1->right;
					del(off1->left);
					off2 = off2->left;
					off1 = off1->right;
					del(off2->right);
				} else {
					off1 = off1->right;
					del(off1->left);
					off2 = off2->left;
					del(off2->right);
				}
				i += 2;
			}
			if (i < n - 1)
				cout << ",";
			else if (i == n - 1) {
				cout << ",";
				break;
			} else if (i == n) {
				break;
			}
		}
		if (i == n - 1)
			output(off1->value);
		cout << endl;
	}
	return 0;
}
