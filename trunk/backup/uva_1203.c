#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * uva 1203
 */

#define MAX

struct Query {
	int qNum;
	int period;
	long long timestamp;
};

static struct Query queue[100000];
static int head = -1, tail = -1;

int cmp(const void * a, const void * b) {
	struct Query qa = *((struct Query *) a);
	struct Query qb = *((struct Query *) b);
	if (qa.timestamp != qb.timestamp) {
		return qa.timestamp - qb.timestamp;
	} else {
		return qa.qNum - qb.qNum;
	}
}
void enqueue(struct Query q) {
	if (head == tail && head == -1) {
		head = tail = 0;
		queue[tail] = q;
		return;
	}
	tail++;
	queue[tail] = q;
	qsort(queue + head			, tail - head + 1, sizeof(struct Query), cmp);

	if (DEBUG) {
		int i;
		for (i = head; i <= tail; i++) {
			printf("(%d,%d,%ld) ", queue[i].qNum, queue[i].period, queue[i].timestamp);
		}
		printf("\n");
	}
}

struct Query dequeue() {
	struct Query re = queue[head];
	if (head == tail) {
		head = tail = -1;
	} else {
		head++;
	}
	return re;
}

int main() {
	int i, j, n, k, p;
	char line[128];
	struct Query q;
	while (gets(line) != NULL) {
		if (line[0] == '#') {
			scanf("%d", &k);
			for (i = 0; i < k; i++) {
				q = dequeue();
				printf("%d\n", q.qNum);
				q.timestamp += q.period;
				enqueue(q);
			}
		} else {
			sscanf(line, "Register %d %d", &n, &p);
			q.qNum = n;
			q.period = p;
			q.timestamp = p;
			enqueue(q);
		}
	}
	return 0;
}

