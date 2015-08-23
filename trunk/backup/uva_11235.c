#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct NODE {
	int from, to, num;
	struct NODE * left;
	struct NODE * right;
} Node;

Node * new(int n, int f, int t) {
	Node * p = malloc(sizeof(Node));
	p->from = f;
	p->to = t;
	p->num = n;
	p->left = NULL;
	p->right = NULL;
	return p;
}

Node * newParent(Node * left, Node * right) {
	Node * parent = new(left->num > right->num ? left->num : right->num, left->from, right->to);
	parent->left = left;
	parent->right = right;
	return parent;
}

int dfs(Node * root, int from, int to) {
	if (root->left == NULL || root->right == NULL)
		return to - from + 1;

	if (root->from == from && root->to == to)
		return root->num;

	if (to <= root->left->to) {
		return dfs(root->left, from, to);
	} else if (from >= root->right->from) {
		return dfs(root->right, from, to);
	} else {
		int leftMax = dfs(root->left, from, root->left->to);
		int rightMax = dfs(root->right, root->right->from, to);
		return leftMax > rightMax ? leftMax : rightMax;
	}
}

/**
 * 11235
 */
int main(int argc, char * argv[]) {
	int n, q, i, j;
	char line[32];

	for (scanf("%d %d", &n, &q); n != 0; scanf("%d %d", &n, &q)) {
		int a[n], freq[n];
		Node * nodes[n];
		int nodesSize = 0;
		for (i = 0; i < n; i++) {
			int t;
			scanf("%d", &t);
			a[i] = t;
		}
		for (i = 0; i < n;) {
			int f = 0;
			j = i;
			while (a[i] == a[j] && j < n) {
				f++;
				j++;
			}
			int k;
			for (k = i; k < j; k++) {
				freq[k] = f;
			}
			nodes[nodesSize++] = new(f, i, j - 1);
			i = j;
		}

		Node * parents[nodesSize];
		int parentsSize = 0;
		while (1) {
			parentsSize = 0;
			for (i = 0; i < nodesSize;) {
				if (i + 1 == nodesSize) {
					parents[parentsSize++] = nodes[i];
					break;
				} else {
					parents[parentsSize++] = newParent(nodes[i], nodes[i + 1]);
					i += 2;
				}
			}

			memcpy(nodes, parents, parentsSize * sizeof(Node *));
			nodesSize = parentsSize;
			if (nodesSize == 1)
				break;
		}
		Node * root = nodes[0];
		int from, to;
		for (i = 0; i < q; i++) {
			scanf("%d %d", &from, &to);
			printf("%d\n", dfs(root, from - 1, to - 1));
		}
	}

	return 0;
}

