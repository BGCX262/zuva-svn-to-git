#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

struct Square {
	float cX;
	float cY;
	float ltX;
	float ltY;
	float rbX;
	float rbY;
	int size;
};

struct Square * new(float centerX, float centerY, int size) {
	struct Square * s = malloc(sizeof(struct Square));
	/*float halfSide = ((float) size * 2 + 1) / 2;*/
	float halfSide = size;
	s->size = size;
	s->cX = centerX;
	s->cY = centerY;
	s->ltX = centerX - halfSide;
	s->ltY = centerY - halfSide;
	s->rbX = centerX + halfSide;
	s->rbY = centerY + halfSide;
	return s;
}

#define QUEUE_SIZE 1024
static struct Square * QUEUE[QUEUE_SIZE];
static int head = -1;
static int tail = -1;

void clean() {
	head = -1;
	tail = -1;
}

void enqueue(struct Square * s) {
	if (DEBUG) {
		printf("enqueue %f %f %f %f size:%d\n", s->ltX, s->ltY, s->rbX, s->rbY, s->size);
	}

	if (s == NULL)
		return;

	if (head == -1 && tail == -1) {
		head = 0;
		tail = 0;
	} else {
		tail = (tail + 1) % QUEUE_SIZE;
		if (tail == head) {
			printf("queue is full!\n");
			exit(0);
		}
	}
	QUEUE[tail] = s;
	return;
}

struct Square * dequeue() {
	if (head == -1) {
		return NULL;
	}

	struct Square * s = QUEUE[head];
	head = (head + 1) % QUEUE_SIZE;
	if (head == (tail + 1) % QUEUE_SIZE) {
		clean();
	}
	if (DEBUG) {
		printf("enqueue %f %f %f %f size:%d\n", s->ltX, s->ltY, s->rbX, s->rbY, s->size);
	}
	return s;
}

int isIn(struct Square * s, float xf, float yf) {
	if (xf <= s->rbX && xf >= s->ltX && yf >= s->ltY && yf <= s->rbY) {
		return 1;
	} else {
		return 0;
	}
}

int main() {
	int k;
	float x, y;
	while (scanf("%d %f %f", &k, &x, &y) == 3) {
		if (k == 0 && x == 0 && y == 0)
			break;

		int hit = 0;
		enqueue(new(1024, 1024, k));
		struct Square * s;
		while ((s = dequeue()) != NULL) {
			if (x <= s->rbX && x >= s->ltX && y >= s->ltY && y <= s->rbY) {
				if (DEBUG) {
					printf("hit! %f %f in %f %f %f %f size:%d\n", x, y, s->ltX, s->ltY, s->rbX, s->rbY, s->size);
				}
				++hit;
			}
			if (x <= s->cX && y <= s->cY && (s->size / 2) >= 1) {
				enqueue(new(s->ltX, s->ltY, s->size / 2));
			}
			if (x >= s->cX && y <= s->cY && (s->size / 2) >= 1) {
				enqueue(new(s->rbX, s->ltY, s->size / 2));
			}
			if (x <= s->cX && y >= s->cY && (s->size / 2) >= 1) {
				enqueue(new(s->ltX, s->rbY, s->size / 2));
			}
			if (x >= s->cX && y >= s->cY && (s->size / 2) >= 1) {
				enqueue(new(s->rbX, s->rbY, s->size / 2));
			}
		}
		printf("%3d\n", hit);

	}
	return 0;
}
