#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define DEBUG 0

struct People {
	int parent;
	char name[32];
	int indexOfDFS;
	int level;
	int child[100];
	int child_num;
};

static struct People * family[301];
static int familySize = 0;
static int DFSPos[2 * 301 - 1];
static int DFSLevel[2 * 301 - 1];
static int dfsSize = 0;
static int DFSLevelRMQ[2 * 301 - 1][2 * 301 - 1];

struct People * newPeople(char * name) {
	struct People * p = malloc(sizeof(struct People));
	p->indexOfDFS = -1;
	p->level = -1;
	p->parent = -1;
	p->child_num = 0;
	if (name != NULL)
		strcpy(p->name, name);
	return p;
}

void printfDFS() {
	int i, j;
	for (i = 0; i < dfsSize; i++) {
		printf("DFSPos[%d]:%d ", i, DFSPos[i]);
		if (i % 5 == 0)
			printf("\n");
	}
	printf("\n");
	for (i = 0; i < dfsSize; i++) {
		printf("DFSLevel[%d]:%d ", i, DFSLevel[i]);
		if (i % 5 == 0)
			printf("\n");
	}
	printf("\n");
	for (i = 0; i < dfsSize; i++) {
		for (j = i + 1; j < dfsSize; j++) {
			printf("LevelRMQ[%d][%d]:%d ", i, j, DFSLevelRMQ[i][j]);
			if (j % 5 == 0)
				printf("\n");
		}
		if (i % 5 == 0)
			printf("\n");
	}
	printf("\n");
}

void printfFamilyArr() {
	int i, j;
	for (i = 0; i < familySize; i++) {
		printf("People[%d]:%s, indexOfDFS:%d, Level:%d, Parent:%d, \n", i, family[i]->name, family[i]->indexOfDFS, family[i]->level, family[i]->parent);
		for (j = 0; j < family[i]->child_num; j++) {
			printf(" Child[%d]:%d, ", j, family[i]->child[j]);
		}
		printf("\n");
	}
}

int getPositionInFamily(char * name) {
	int i;
	for (i = 0; i < familySize; i++) {
		if (strcmp(family[i]->name, name) == 0) {
			return i;
		}
	}
	return -1;
}

void makeRelation(int childPos, int parentPos) {
	family[childPos]->parent = parentPos;
	family[parentPos]->child[family[parentPos]->child_num] = childPos;
	family[parentPos]->child_num++;
}

int addPseudoRoot(char * name) {
	/**
	 * pseudo root position
	 */
	int rootPos = addToFamilyArr(name);
	int i;
	for (i = 0; i < familySize; i++) {
		if (family[i]->parent == -1 && i != rootPos) {
			makeRelation(i, rootPos);
		}
	}
	return rootPos;
}

int addToFamilyArr(char * name) {
	/*
	 if (DEBUG) {
	 printf("addToFamilyArr with name %s\n", name);
	 }
	 */
	struct People * people = newPeople(name);
	family[familySize] = people;
	familySize++;
	return familySize - 1;
}

/**
 * depth first search
 */
void processDFS(int pos, int level) {
	/*	if (DEBUG) {
	 printf("processDFS(%d, %d)\n", pos, level);
	 }*/
	struct People * po = family[pos];
	DFSPos[dfsSize] = pos;
	DFSLevel[dfsSize] = level;
	if (po->indexOfDFS == -1) {
		po->indexOfDFS = dfsSize;
		po->level = level;
	}
	dfsSize++;
	int i;
	for (i = 0; i < po->child_num; i++) {
		processDFS(po->child[i], level + 1);
		DFSPos[dfsSize] = pos;
		DFSLevel[dfsSize] = level;
		dfsSize++;
	}
}

void buildDFSLevelRMQ() {
	int i, j;
	for (i = 0; i < dfsSize; i++) {
		DFSLevelRMQ[i][i] = i;
	}
	for (i = 0; i < dfsSize; i++) {
		for (j = i + 1; j < dfsSize; j++) {
			if (DFSLevel[DFSLevelRMQ[i][j - 1]] < DFSLevel[j]) {
				DFSLevelRMQ[i][j] = DFSLevelRMQ[i][j - 1];
			} else {
				DFSLevelRMQ[i][j] = j;
			}
		}
	}
}

int main(int argc, char * argv[]) {
	char child[32], parent[32];
	int childPos, parentPos;
	while (scanf("%s %s\n", child, parent) != EOF) {
		if (strcmp("no.child", child) == 0) {
			break;
		}
		parentPos = getPositionInFamily(parent);
		if (parentPos == -1) {
			parentPos = addToFamilyArr(parent);
		}
		childPos = getPositionInFamily(child);
		if (childPos == -1) {
			childPos = addToFamilyArr(child);
		}
		/**
		 * set parent and child relation
		 */
		makeRelation(childPos, parentPos);
	}
	int rootPos = addPseudoRoot("douzhi");
	processDFS(rootPos, 0);
	buildDFSLevelRMQ();
	if (DEBUG) {
		printfFamilyArr();
		printfDFS();
	}

	char str1[32], str2[32];
	int pos1, pos2, i1, i2, ancestor, levelGap, i;
	while (scanf("%s %s\n", str1, str2) != EOF) {
		pos1 = getPositionInFamily(str1);
		pos2 = getPositionInFamily(str2);
		if (DEBUG) {
			printf("pos1:%d, pos2:%d\n", pos1, pos2);
		}

		if (pos1 == -1 || pos2 == -1) {
			printf("no relation\n");
			continue;
		}
		i1 = family[pos1]->indexOfDFS;
		i2 = family[pos2]->indexOfDFS;
		if (i1 < i2) {
			ancestor = DFSPos[DFSLevelRMQ[i1][i2]];
		} else {
			ancestor = DFSPos[DFSLevelRMQ[i2][i1]];
		}
		if (DEBUG) {
			printf("ancestor is %d\n", ancestor);
		}
		if (ancestor == familySize - 1) {
			/**
			 * ancestor is pseudo root
			 */
			printf("no relation\n");
			continue;
		}

		levelGap = family[pos1]->level - family[pos2]->level;
		if (levelGap < 0) {
			levelGap = -levelGap;
		}
		if (ancestor == pos1) {
			/**
			 * parent-child
			 */
			if (levelGap == 1) {
				printf("parent\n");
				continue;
			} else if (levelGap == 2) {
				printf("grand parent\n");
				continue;
			} else {
				i = 0;
				while (i++ < levelGap - 2) {
					printf("great ");
				}
				printf("grand parent\n");
				continue;
			}
		}

		if (ancestor == pos2) {
			/**
			 * child-parent
			 */
			if (levelGap == 1) {
				printf("child\n");
				continue;
			} else if (levelGap == 2) {
				printf("grand child\n");
				continue;
			} else {
				i = 0;
				while (i++ < levelGap - 2) {
					printf("great ");
				}
				printf("grand child\n");
				continue;
			}
		}
		/**
		 * cousin
		 */
		int descendGap1, descendGap2;
		descendGap1 = family[pos1]->level - family[ancestor]->level;
		descendGap2 = family[pos2]->level - family[ancestor]->level;
		if (descendGap1 == 1 && descendGap2 == 1) {
			/**
			 * 0th cousin with 0 removed is sibling
			 */
			printf("sibling\n");
			continue;
		}

		if (descendGap1 > descendGap2) {
			i = descendGap2;
			descendGap2 = descendGap1;
			descendGap1 = i;
		}
		printf("%d cousin removed %d\n", descendGap1 - 1, descendGap2 - descendGap1);
	}

	return 0;
}
