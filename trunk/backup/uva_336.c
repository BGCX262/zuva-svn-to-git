#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

typedef struct NODE {
	int num;
	int ttl;
	int visited;
	struct NODE * conn[64];
	int connSize;
} Node;

Node * new(int n) {
	Node * p = malloc(sizeof(Node));
	p->num = n;
	p->connSize = 0;
	p->ttl = 0;
	return p;
}

static Node * nodes[64];
static Node * queue[64];
static int nodesSize;
static int left, right;
static int caseNum = 0;

void qIn(Node * p) {
	right++;
	queue[right] = p;
	if (left == -1)
		left = right;
}

Node * qOut() {
	Node * r = (left > right ? NULL : queue[left]);
	left++;
	return r;
}

int main(int argc, char * argv[]) {
	int n, n1, n2, i, j, from, ttl;
	for (;;) {
		scanf("%d\n", &n);
		if (n == 0)
			break;
		nodesSize = 0;
		for (i = 0; i < n; i++) {
			Node * p1 = NULL;
			Node * p2 = NULL;
			scanf("%d", &n1);
			scanf("%d", &n2);
			if (DEBUG) {
				printf("n1 %d n2 %d\n", n1, n2);
			}

			for (j = 0; j < nodesSize; j++) {
				if (nodes[j]->num == n1) {
					p1 = nodes[j];
				}
				if (nodes[j]->num == n2) {
					p2 = nodes[j];
				}
				if (p1 != NULL && p2 != NULL)
					break;
			}
			if (n1 == n2) {
				if (p1 == NULL) {
					p1 = new(n1);
					nodes[nodesSize++] = p1;
				}
				continue;
			}
			if (p1 == NULL) {
				p1 = new(n1);
				nodes[nodesSize++] = p1;
			}
			if (p2 == NULL) {
				p2 = new(n2);
				nodes[nodesSize++] = p2;
			}
			p1->conn[p1->connSize++] = p2;
			p2->conn[p2->connSize++] = p1;
		}

		if (DEBUG) {
			int index;
			/*printf("nodesSize %d visitedNum %d\n", nodesSize, visitedNum);*/
			printf("nodes list ===============================================\n");
			for (index = 0; index < nodesSize; index++) {
				printf("visited %d num %d ttl %d connSize %d\n", nodes[index]->visited, nodes[index]->num, nodes[index]->ttl, nodes[index]->connSize);
			}
			printf("end list ===============================================\n");
		}

		for (;;) {
			left = -1;
			right = -1;
			scanf("%d", &from), scanf("%d", &ttl);
			if (from == 0 && ttl == 0)
				break;

			for (i = 0; i < nodesSize; i++) {
				nodes[i]->ttl = 0;
				nodes[i]->visited = 0;
				if (nodes[i]->num == from) {
					nodes[i]->visited = 1;
					nodes[i]->ttl = ttl;
					qIn(nodes[i]);
				}
			}
			if (DEBUG) {
				int index;
				printf("from %d ttl %d\n", from, ttl);
				printf("nodes list  ===============================================\n");
				for (index = 0; index < nodesSize; index++) {
					printf("visited %d num %d ttl %d connSize %d\n", nodes[index]->visited, nodes[index]->num, nodes[index]->ttl, nodes[index]->connSize);
				}
				printf("end list ===============================================\n");
			}

			/*begin bfs*/
			Node * curr;
			int visitedNum = 0;
			for (curr = qOut(); curr != NULL; curr = qOut()) {
				visitedNum++;
				if (curr->ttl > 0) {
					int conIndex;
					for (conIndex = 0; conIndex < curr->connSize; conIndex++) {
						if (curr->conn[conIndex]->visited == 0) {
							curr->conn[conIndex]->visited = 1;
							curr->conn[conIndex]->ttl = curr->ttl - 1;
							qIn(curr->conn[conIndex]);
						}
					}
				}
				if (DEBUG)
					printf("visited %d num %d ttl %d connSize %d\n", curr->visited, curr->num, curr->ttl, curr->connSize);

			}
			caseNum++;
			printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", caseNum, (nodesSize - visitedNum), from, ttl);

		}
	}

	return 0;
}
