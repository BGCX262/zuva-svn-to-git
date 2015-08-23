#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

struct Node {
	char c;
	struct Node * next;
};

struct Node * newNode(char x) {
	struct Node * p = malloc(sizeof(struct Node));
	p->c = x;
	p->next = NULL;
	return p;
}

static struct Node * vars[8];
static char
		* indents[10] = { "", "  ", "    ", "      ", "        ", "          ", "            ", "              ", "                ", "                  " };

struct Node * insert(struct Node * head, int pos, struct Node * insNode) {
	if (DEBUG) {
		printf("insert to position:%d with %c\n", pos, insNode->c);
	}
	if (pos == 0) {
		insNode->next = head;
		return insNode;
	}
	int i = 1;
	struct Node * prev = head;
	while (i < pos) {
		if (prev->next != NULL) {
			prev = prev->next;
		} else {
			break;
		}
		i++;
	}
	struct Node * temp = prev->next;
	prev->next = insNode;
	insNode->next = temp;
	return head;
}

struct Node * erase(struct Node * head, int pos) {
	if (pos == 0) {
		struct Node * temp = head;
		head = head->next;
		return head;
	}
	int i = 1;
	struct Node * prev = head;
	while (i < pos) {
		prev = prev->next;
		i++;
	}
	struct Node * delNode = prev->next;
	if (delNode->next == NULL) {
		prev->next = NULL;
		return head;
	}
	prev->next = delNode->next;
	return head;
}

struct Node * get(struct Node * t, int pos) {
	int i = 0;
	while (i < pos && t != NULL) {
		t = t->next;
		i++;
	}
	return t;
}

void setNodeStr(struct Node * t, char msg[]) {
	strcpy(msg, "");
	int size = 1;
	while (t != NULL) {
		strncat(msg, &t->c, 1);
		strncat(msg, " ", 1);
		size += 2;
		t = t->next;
	}
	msg[size] = '\0';
}

void meta_print(struct Node * varsNode, int level, int maxLevel) {
	if (DEBUG) {
		char msg[256];
		setNodeStr(varsNode, msg);
		printf("level:%d, maxLevel:%d, list:%s\n", level, maxLevel, msg);
	}
	if (level == maxLevel) {
		printf("%s", indents[level]);
		printf("writeln(");
		while (varsNode != NULL) {
			printf("%c", varsNode->c);
			varsNode = varsNode->next;
			if (varsNode != NULL) {
				printf(",");
			}
		}
		printf(")\n");
		return;
	}
	int i = 0;
	printf("%s", indents[level]);
	while (get(varsNode, i) != NULL) {
		printf("if %c < %c then\n", vars[level]->c, get(varsNode, i)->c);
		varsNode = insert(varsNode, i, vars[level]);
		meta_print(varsNode, level + 1, maxLevel);
		varsNode = erase(varsNode, i);
		printf("%s", indents[level]);
		printf("else ");
		i++;
	}
	printf("\n");
	varsNode = insert(varsNode, i, vars[level]);
	meta_print(varsNode, level + 1, maxLevel);
	varsNode = erase(varsNode, i);
}

int main(int argc, char * argv[]) {
	int n, m, i, j, size;
	vars[0] = newNode('a');
	vars[1] = newNode('b');
	vars[2] = newNode('c');
	vars[3] = newNode('d');
	vars[4] = newNode('e');
	vars[5] = newNode('f');
	vars[6] = newNode('g');
	vars[7] = newNode('h');
	scanf("%d\n", &m);
	for (i = 0; i < m; i++) {
		scanf("%d\n", &n);
		if (i != 0) {
			printf("\n");
		}
		char vars_str[256];
		strncpy(vars_str, &vars[0]->c, 1);
		size = 1;
		vars_str[size] = '\0';
		for (j = 1; j < n; j++) {
			strncat(vars_str, ",", 1);
			size += 1;
			vars_str[size] = '\0';
			strncat(vars_str, &vars[j]->c, 1);
			size += 1;
			vars_str[size] = '\0';
		}
		vars_str[size] = '\0';
		printf("program sort(input,output);\n");
		printf("var\n");
		printf("%s : integer;\n", vars_str);
		printf("begin\n");
		printf("  readln(%s);\n", vars_str);
		meta_print(vars[0], 1, n);
		printf("end.\n");
	}
	return 0;
}
