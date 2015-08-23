#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1

/**
 * uva 346
 */

struct Chord {
	char name[2];
	int index;
};
static struct Chord simpleChords[7] = { { "A", 0 }, { "B", 2 }, { "C", 3 }, { "D", 5 }, { "E", 7 }, { "F", 8 }, { "G", 10 } };
static struct Chord doubleChords[14] = { { "A#", 1 }, { "Bb", 1 }, { "Cb", 2 }, { "B#", 3 }, { "C#", 4 }, { "Db", 4 }, { "D#", 6 }, { "Eb", 6 }, { "Fb", 7 }, {
		"E#", 8 }, { "F#", 9 }, { "Gb", 9 }, { "G#", 11 }, { "Ab", 11 } };

static int all[12];

int getSimpleIndex(char c) {
	int i;
	if (c >= 'a' && c <= 'z') {
		c -= 32;
	}
	for (i = 0; i < 7; i++) {
		if (simpleChords[i].name[0] == c) {
			return simpleChords[i].index;
		}
	}
	return -1;
}

int getDoubleIndex(char c1, char c2) {
	int i;
	if (c1 >= 'a' && c1 <= 'z') {
		c1 -= 32;
	}
	for (i = 0; i < 14; i++) {
		if (doubleChords[i].name[0] == c1 && doubleChords[i].name[1] == c2) {
			return doubleChords[i].index;
		}
	}
	return -1;
}

int getSimpleName(int index, char c[]) {
	int i;

	for (i = 0; i < 7; i++) {
		if (simpleChords[i].index == index) {
			c[0] = simpleChords[i].name[0];
			return 1;
		}
	}
	return -1;
}

int getDoubleName(int index, char c[]) {
	int i;
	for (i = 0; i < 14; i++) {
		if (doubleChords[i].index == index && doubleChords[i].name[1] == '#') {
			c[0] = doubleChords[i].name[0];
			c[1] = doubleChords[i].name[1];
			return 1;
		}
	}
	return -1;
}

int main() {
	int test;
	char line[1024], c1[3], c2[3], c3[3], doubleName = 0;
	while (fgets(line, 1024, stdin) != NULL) {
		int i, j, i1 = -1, i2 = -1, i3 = -1;
		memset(all, 0, sizeof(int) * 12);

		for (j = 0; j < strlen(line) - 1; doubleName ? j += 2 : j++) {
			doubleName = 0;
			if (isalpha(line[j])) {
				if (line[j + 1] == 'b' || line[j + 1] == '#') {
					i = getDoubleIndex(line[j], line[j + 1]);
					doubleName = 1;
				} else {
					i = getSimpleIndex(line[j]);
				}
				if (i1 == -1) {
					i1 = i;
					if (doubleName) {
						c1[0] = line[j];
						c1[1] = line[j + 1];
						c1[2] = '\0';
					} else {
						c1[0] = line[j];
						c1[1] = '\0';
					}
				} else if (i2 == -1) {
					i2 = i;
					if (doubleName) {
						c2[0] = line[j];
						c2[1] = line[j + 1];
						c2[2] = '\0';
					} else {
						c2[0] = line[j];
						c2[1] = '\0';
					}
				} else {
					i3 = i;
					if (doubleName) {
						c3[0] = line[j];
						c3[1] = line[j + 1];
						c3[2] = '\0';
					} else {
						c3[0] = line[j];
						c3[1] = '\0';
					}
					all[i1] = all[i2] = all[i3] = 1;
					int recognized = 0;
					for (i = 0; i < 12; i++) {
						if (all[i] && all[(i + 4) % 12] && all[((i + 4) % 12 + 3) % 12]) {
							recognized = 1;
							char name[2];
							int r = getSimpleName(i, name);
							if (r != -1) {
								printf("%s %s %s is a %c Major chord.\n", c1, c2, c3, name[0]);
							} else {
								r = getDoubleName(i, name);
								printf("%s %s %s is a %c%c Major chord.\n", c1, c2, c3, name[0], name[1]);
							}
							break;
						} else if (all[i] && all[(i + 3) % 12] && all[((i + 3) % 12 + 4) % 12]) {
							recognized = 1;
							char name[2];
							int r = getSimpleName(i, name);
							if (r != -1) {
								printf("%s %s %s is a %c Minor chord.\n", c1, c2, c3, name[0]);
							} else {
								r = getDoubleName(i, name);
								printf("%s %s %s is a %c%c Major chord.\n", c1, c2, c3, name[0], name[1]);
							}
							break;
						}
					}
					if (!recognized) {
						printf("%s %s %s is unrecognized.\n", c1, c2, c3);
					}
				}
			}
		}
	}

	return 0;
}

