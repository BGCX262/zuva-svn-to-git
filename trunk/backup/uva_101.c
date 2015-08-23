#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

struct Node {
	int item;
	struct Node * up;
	struct Node * down;
};

struct Node * newStackNode(int i) {
	struct Node * pNode = malloc(sizeof(struct Node));
	pNode->up = NULL;
	pNode->down = NULL;
	pNode->item = i;
	return pNode;
}

void print_blocks(struct Node * pList[], int size) {
	int i;
	struct Node * pNode;
	for (i = 0; i < size; i++) {
		printf("%d:", i);
		pNode = pList[i];
		while (pNode != NULL) {
			printf(" %d", pNode->item);
			pNode = pNode->up;
		}
		printf("\n");
	}
}
void print_lookup(int lookup[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("lookup:%d:%d\n", i, lookup[i]);
	}
}
int verify(int lookup[], int size, int from, int to) {
	if (from > (size - 1) || from < 0 || to > (size - 1) || to < 0) {
		return 1;
	}
	if (from == to || lookup[from] == lookup[to]) {
		return 1;
	}
	return 0;
}

/*push a item n to the ith stack*/
void enqueue(struct Node * stacks[], int i, struct Node * node) {
	struct Node * pStackNode = stacks[i];
	if (pStackNode != NULL) {
		while (pStackNode->up != NULL) {
			pStackNode = pStackNode->up;
		}
		pStackNode->up = node;
		node->down = pStackNode;
		node->up = NULL;
	} else {
		stacks[i] = node;
		node->down = NULL;
		node->up = NULL;
	}
}

/*pop a item from the ith stack*/
struct Node * dequeue(struct Node * stacks[], int i) {
	struct Node * pStackNode = stacks[i];
	if (pStackNode != NULL) {
		while (pStackNode->up != NULL) {
			pStackNode = pStackNode->up;
		}
		if (pStackNode->down != NULL) {
			pStackNode->down->up = NULL;
			pStackNode->down = NULL;
		} else {
			stacks[i] = NULL;
		}
		return pStackNode;
	} else {
		return NULL;
	}
}

/*get top node's item of the ith stack*/
int top(struct Node * stacks[], int i) {
	struct Node * pStackNode = stacks[i];
	while (pStackNode != NULL) {
		if (pStackNode->up == NULL) {
			return pStackNode->item;
		}
		pStackNode = pStackNode->up;
	}
	return -1;
}

/*put all nodes on top of x to their initial place, including x*/
void init_top(struct Node * stacks[], int lookup[], int x) {
	struct Node * node = NULL;
	while (top(stacks, lookup[x]) != x) {
		node = dequeue(stacks, lookup[x]);
		enqueue(stacks, node->item, node);
		lookup[node->item] = node->item;
	}
}

void move_onto(struct Node * stacks[], int lookup[], int a, int b) {
	if (DEBUG) {
		printf("move %d onto %d===============================\n", a, b);
	}
	init_top(stacks, lookup, a);
	init_top(stacks, lookup, b);
	struct Node * node = dequeue(stacks, lookup[a]);
	enqueue(stacks, lookup[b], node);
	lookup[a] = lookup[b];
}

void move_over(struct Node * stacks[], int lookup[], int a, int b) {
	if (DEBUG) {
		printf("move %d over %d===============================\n", a, b);
	}
	init_top(stacks, lookup, a);
	struct Node * node = dequeue(stacks, lookup[a]);
	enqueue(stacks, lookup[b], node);
	lookup[a] = lookup[b];
}

void pile_onto(struct Node * stacks[], int lookup[], int a, int b) {
	if (DEBUG) {
		printf("pile %d onto %d===============================\n", a, b);
	}
	init_top(stacks, lookup, b);
	struct Node * node = NULL;
	while (top(stacks, lookup[a]) != a) {
		if (node == NULL) {
			node = dequeue(stacks, lookup[a]);
		} else {
			node->down = dequeue(stacks, lookup[a]);
			node->down->up = node;
			node = node->down;
		}
	}
	if (node == NULL) {
		node = dequeue(stacks, lookup[a]);
	} else {
		node->down = dequeue(stacks, lookup[a]);
		node->down->up = node;
		node = node->down;
	}

	struct Node * tmp = NULL;
	while (node != NULL) {
		tmp = node;
		node = node->up;
		enqueue(stacks, lookup[b], tmp);
		lookup[tmp->item] = lookup[b];
	}
}

void pile_over(struct Node * stacks[], int lookup[], int a, int b) {
	if (DEBUG) {
		printf("pile %d over %d===============================\n", a, b);
	}
	struct Node * node = NULL;
	while (top(stacks, lookup[a]) != a) {
		if (node == NULL) {
			node = dequeue(stacks, lookup[a]);
		} else {
			node->down = dequeue(stacks, lookup[a]);
			node->down->up = node;
			node = node->down;
		}
	}
	if (node == NULL) {
		node = dequeue(stacks, lookup[a]);
	} else {
		node->down = dequeue(stacks, lookup[a]);
		node->down->up = node;
		node = node->down;
	}
	struct Node * tmp = NULL;
	while (node != NULL) {
		tmp = node;
		node = node->up;
		enqueue(stacks, lookup[b], tmp);
		lookup[tmp->item] = lookup[b];
	}
}

int main(int argc, char * argv[]) {
	char cmd1[16], cmd2[16];
	int n, a, b, i;
	scanf("%d\n", &n);
	struct Node * stacks[n];
	/*used to lookup every nth block node*/
	int lookup[n];
	/* init block list*/
	for (i = 0; i < n; i++) {
		stacks[i] = newStackNode(i);
		lookup[i] = i;
	}
	while (scanf("%s %d %s %d\n", cmd1, &a, cmd2, &b) == 4) {
		if (verify(lookup, n, a, b) == 1) {
			continue;
		}
		if (strcmp(cmd1, "move") == 0) {
			if (strcmp(cmd2, "onto") == 0) {
				move_onto(stacks, lookup, a, b);
				if (DEBUG) {
					print_blocks(stacks, n);
					/*print_blocks(stacks, n);*/

				}
			} else if (strcmp(cmd2, "over") == 0) {
				move_over(stacks, lookup, a, b);
				if (DEBUG) {
					print_blocks(stacks, n);
					/*print_blocks(stacks, n);*/
				}
			}
		} else if (strcmp(cmd1, "pile") == 0) {
			if (strcmp(cmd2, "onto") == 0) {
				pile_onto(stacks, lookup, a, b);
				if (DEBUG) {
					print_blocks(stacks, n);
					/*print_blocks(stacks, n);*/
				}
			} else if (strcmp(cmd2, "over") == 0) {
				pile_over(stacks, lookup, a, b);
				if (DEBUG) {
					print_blocks(stacks, n);
					/*print_blocks(stacks, n);*/
				}
			}
		}
	}
	if (!DEBUG) {
		if (strcmp(cmd1, "quit") == 0) {
			print_blocks(stacks, n);
		}
	}
	return 0;
}
