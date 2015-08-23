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

static int levelMap[6] = { 1024, 256, 64, 16, 4, 1 };

class Node {
public:
	char color;
	int level;
	Node * sub1;
	Node * sub2;
	Node * sub3;
	Node * sub4;

	Node(char value, int l) {
		this->color = value;
		this->level = l;
	}

	string toStr() {
		stringstream ss;
		ss << "color " << color << " level " << level;
		return ss.str();
	}
};

class Tree {
private:
	Node* root;

public:
	int black;
	Tree(string & s) {
		root = build(s, 0);
		black = 0;
	}

	Node * build(string & s, int level) {
		Node * node = new Node(s[0], level);
		if (DEBUG) {
			cout << "build node:" << node->toStr() << endl;
		}

		if (node->color == 'p') {
			s = s.substr(1, s.size() - 1);
			node->sub1 = build(s, level + 1);
			s = s.substr(1, s.size() - 1);
			node->sub2 = build(s, level + 1);
			s = s.substr(1, s.size() - 1);
			node->sub3 = build(s, level + 1);
			s = s.substr(1, s.size() - 1);
			node->sub4 = build(s, level + 1);
		}
		return node;
	}

	void merge(Tree & tree) {
		mergeNode(this->root, tree.root);
	}

	void dfs() {
		dfsNode(root);
	}

	void dfsNode(Node * node) {
		if (DEBUG) {
			cout << "dfs Node1:" << node->toStr() << endl;
		}

		if (node->color == 'f') {
			this->black += levelMap[node->level];
			return;
		}

		if (node->color == 'p') {
			dfsNode(node->sub1);
			dfsNode(node->sub2);
			dfsNode(node->sub3);
			dfsNode(node->sub4);
			return;
		}

	}

	void mergeNode(Node * n1, Node * n2) {
		if (DEBUG) {
			cout << "merge Node1:" << n1->toStr() << ", node2:" << n2->toStr() << endl;
		}

		if (n1->color == 'p' && n2->color == 'p') {
			mergeNode(n1->sub1, n2->sub1);
			mergeNode(n1->sub2, n2->sub2);
			mergeNode(n1->sub3, n2->sub3);
			mergeNode(n1->sub4, n2->sub4);
			return;
		}

		if (n2->color == 'f') {
			n1->color = 'f';
			return;
		}

		if (n1->color == 'e' && n2->color == 'p') {
			n1->color = 'p';
			n1->sub1 = n2->sub1;
			n1->sub2 = n2->sub2;
			n1->sub3 = n2->sub3;
			n1->sub4 = n2->sub4;
			return;
		}
	}
};

int main(int argc, char * argv[]) {
	string line;
	int n;
	getline(cin, line);
	istringstream is(line);
	is >> n;
	for (int i = 0; i < n; i++) {
		int black = 0;
		getline(cin, line);
		Tree t1(line);
		getline(cin, line);
		Tree t2(line);
		t1.merge(t2);
		t1.dfs();
		cout << "There are " << t1.black << " black pixels." << endl;
	}
	return 0;
}

