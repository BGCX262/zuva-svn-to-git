#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0
#define NIL -1
#define MAX 9999

struct Vertex {
	int pre;
	/**
	 * weight from source to this one
	 */
	int w_to_source;
	int adjacent[26];
	int degree;
};
static int weight[26][26];
static struct Vertex * vertices[26];
static int queue[26];
static int queueSize = 0;

struct Vertex * newVertex() {
	struct Vertex * p = malloc(sizeof(struct Vertex));
	p->pre = NIL;
	p->w_to_source = MAX;
	p->degree = 0;
	memset(p->adjacent, NIL, sizeof(p->adjacent));
	return p;
}

void init() {
	int i;
	for (i = 0; i < 26; i++) {
		if (vertices[i] == NULL) {
			vertices[i] = newVertex();
		} else {
			vertices[i]->pre = NIL;
			vertices[i]->w_to_source = MAX;
			vertices[i]->degree = 0;
			memset(vertices[i]->adjacent, NIL, sizeof(vertices[i]->adjacent));
		}
	}
	memset(weight, NIL, sizeof(weight));
	queueSize = 0;
}

void printfQueue() {
	int i = 0;
	for (i = 0; i < queueSize; i++) {
		printf("%d[%d] ", queue[i], vertices[queue[i]]->w_to_source);
	}
	printf("\n");
}
void printfMatrix() {
	int i, j;
	printf("weight matrix:\n");
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (weight[i][j] == NIL) {
			} else {
				printf("[%d,%d]%d  ", i, j, weight[i][j]);
			}
		}
	}
	printf("\nvertex:\n");
	for (i = 0; i < 26; i++) {
		if (vertices[i] == NULL) {
		} else {
			printf("[%d]%d", i, (int) vertices[i]);
		}

	}
	printf("\n");
}

void setStreetInfo(char * streetS, char * int1, char * int2, int * weight) {
	char t;
	*int1 = *(streetS + 0);
	*weight = strlen(streetS);
	*int2 = *(streetS + *weight - 1);
	if (*int1 - 'a' > *int2 - 'a') {
		t = *int1;
		*int1 = *int2;
		*int2 = t;
	}
}

void setWeightAndVertex(char c1, char c2, int w) {
	int i1 = c1 - 'a';
	int i2 = c2 - 'a';
	weight[i1][i2] = w;
	weight[i2][i1] = w;
	if (vertices[i1] == NULL) {
		vertices[i1] = newVertex();
	}
	vertices[i1]->adjacent[i2] = 1;
	vertices[i1]->degree++;
	if (vertices[i2] == NULL) {
		vertices[i2] = newVertex();
	}
	vertices[i2]->adjacent[i1] = 1;
	vertices[i2]->degree++;
}

int getAllWeight() {
	int w = 0, i, j;
	for (i = 0; i < 25; i++) {
		for (j = i + 1; j < 26; j++) {
			if (weight[i][j] != NIL) {
				w += weight[i][j];
			}
		}
	}
	return w;
}

void enqueue(int in) {
	/*
	 if (DEBUG) {
	 printf("enqueue %d[%d]\n", in, vertices[in]->w_to_source);
	 }
	 */
	/**
	 * enqueue a item and adjust index
	 */
	int i = queueSize;
	while (i > 0) {
		if (vertices[queue[i - 1]]->w_to_source <= vertices[in]->w_to_source) {
			queue[i] = in;
			break;
		} else {
			queue[i] = queue[i - 1];
		}
		i--;
	}
	if (i == 0) {
		queue[0] = in;
	}
	queueSize++;
}

int dequeue() {
	/*
	 if (DEBUG) {
	 printf("dequeue\n");
	 }
	 */

	if (queueSize == 0)
		return NIL;

	int minIn = queue[0];
	/**
	 * move the rest forward
	 */
	int i = 0;
	while (i < queueSize - 1) {
		queue[i] = queue[i + 1];
		i++;
	}
	queueSize--;
	return minIn;
}

void rearrangeQueue() {
	/**
	 * rearrange the queue because one of them 's weight has been changed
	 */
	/*
	 if (DEBUG) {
	 printf("before rearrange\n");
	 printfQueue();
	 }
	 */
	int i = queueSize;
	while (i > 0) {
		if (vertices[queue[i]]->w_to_source < vertices[queue[i - 1]]->w_to_source) {
			break;
		}
		i--;
	}
	/**
	 * i point to this one
	 */
	int thisOne = queue[i];
	while (i > 0) {
		if (vertices[thisOne]->w_to_source < vertices[queue[i - 1]]->w_to_source) {
			queue[i] = queue[i - 1];
		} else {
			break;
		}
		i--;
	}
	queue[i] = thisOne;
	/*
	 if (DEBUG) {
	 printf("after rearrange\n");
	 printfQueue();
	 }
	 */
}

void relax(int u, int v) {
	/*
	 if (DEBUG) {
	 printf("relax %d to %d\n", u, v);
	 }
	 */

	if (vertices[v]->w_to_source > vertices[u]->w_to_source + weight[u][v]) {
		/*
		 if (DEBUG) {
		 printf("%d's %d bigger than %d plus weight uv %d\n", v, vertices[v]->w_to_source, vertices[u]->w_to_source, weight[u][v]);
		 }
		 */
		vertices[v]->w_to_source = vertices[u]->w_to_source + weight[u][v];
		vertices[v]->pre = u;
		rearrangeQueue();
	}
}

int getShortestPathWeight(int source, int dest) {
	int i;
	/*
	 if (DEBUG) {
	 printf("from %d to %d\n", source, dest);
	 }
	 */
	vertices[source]->w_to_source = 0;
	for (i = 0; i < 26; i++) {
		if (vertices[i]->degree != 0) {
			enqueue(i);
			if (DEBUG) {
				printfQueue();
			}
		}
	}

	int u = dequeue();
	while (u != NIL) {
		if (DEBUG) {
			printfQueue();
		}
		for (i = 0; i < 26; i++) {
			if (vertices[u]->adjacent[i] == 1)
				relax(u, i);
		}
		u = dequeue();
	}
	return vertices[dest]->w_to_source;
}

int calRouteWeight() {
	int spw = NIL, i, source = NIL, dest = NIL;
	for (i = 0; i < 26; i++) {
		if (vertices[i] == NULL) {
			continue;
		}
		if (vertices[i]->degree % 2 != 0) {
			if (source == NIL) {
				source = i;
			} else {
				dest = i;
			}
		}
	}
	if (source == NIL) {
		/**
		 * there is no odd degree vertex
		 */
		spw = getAllWeight();
	} else {
		spw = getAllWeight() + getShortestPathWeight(source, dest);
	}
	return spw;
}

int main(int argc, char * argv[]) {
	int i, j, w;
	char streetS[26], in1, in2;
	init();
	while (scanf("%s\n", streetS) != EOF) {
		if (strcmp(streetS, "deadend") == 0) {
			if (DEBUG) {
				printfMatrix();
			}
			printf("%d\n", calRouteWeight());
			init();
			continue;
		}
		setStreetInfo(streetS, &in1, &in2, &w);
		setWeightAndVertex(in1, in2, w);
	}
	return 0;
}

