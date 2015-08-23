#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>

using namespace std;

#define DEBUG 0

struct Node {
	int value;
	struct Node * left;
	struct Node * right;
};

struct Node * alloc(int value) {
	struct Node * p = new Node;
	p->value = value;
	p->left = NULL;
	p->right = NULL;
	return p;
}

static struct Node * root;
static bool isComplete;

void DeleteTree(struct Node * n) {
	if (n != NULL) {
		DeleteTree(n->left);
		DeleteTree(n->right);
	}
	delete n;
}

void addNode(int value, char *pathS) {
	/*
	 if (DEBUG) {
	 cout << "add node " << value << ", path " << (pathS == NULL ? "null" : pathS) << endl;
	 }
	 */
	int i = 0;
	char path;
	struct Node * p = root;
	if (pathS != NULL) {
		int pathSize = strlen(pathS);
		for (i = 0; i < pathSize; i++) {
			path = pathS[i];
			if (path == 'L') {
				if (p->left == NULL) {
					p->left = alloc(0);
				}
				p = p->left;
			} else {
				if (p->right == NULL) {
					p->right = alloc(0);
				}
				p = p->right;
			}
		}
	}
	/**
	 * p now points to node
	 */
	if (p->value != 0) {
		/**
		 * it has already a value!!
		 * so it's not complete!
		 */
		isComplete = false;
	}
	p->value = value;
}

void printTree() {
	/*
	 if (DEBUG) {
	 cout << "printTree" << endl;
	 }
	 */
	if (!isComplete) {
		cout << "not complete" << endl;
	} else {
		string str;
		queue<struct Node *> que;
		struct Node * node;
		que.push(root);
		while (!que.empty()) {
			node = que.front();
			que.pop();
			if (node->value == 0) {
				cout << "not complete" << endl;
				return;
			}
			stringstream ss;
			ss << node->value;
			str.append(ss.str());
			if (node->left != NULL) {
				que.push(node->left);
			}
			if (node->right != NULL) {
				que.push(node->right);
			}
			if (!que.empty()) {
				str.append(" ");
			}
		}
		cout << str << endl;
	}
	/*
	 if (DEBUG) {
	 cout << "printTree end" << endl;
	 }
	 */
}

int main(int argc, char * argv[]) {
	string str, strNum;
	int value;
	bool begin = true;
	while (cin >> str) {
		if (str.compare("()") == 0) {
			printTree();
			DeleteTree(root);
			begin = true;
		} else {
			if (begin) {
				root = alloc(0);
				isComplete = true;
				begin = false;
			}
			char ch[20];
			str = str.substr(1, str.size() - 2);
			strcpy(ch, str.c_str());
			istringstream(strtok(ch, ",")) >> value;
			addNode(value, strtok(NULL, ","));
		}
	}
	return 0;
}
