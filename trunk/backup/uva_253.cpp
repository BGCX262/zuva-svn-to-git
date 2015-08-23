#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <cctype>
#include <cstring>
#include <vector>
using namespace std;

#define DEBUG 0

bool hasSameNumColor(char c1[], char c2[]) {
	int r1 = 0, g1 = 0, b1 = 0, r2 = 0, g2 = 0, b2 = 0;
	for (int i = 0; i < 6; i++) {
		if (c1[i] == 'r') {
			r1++;
		} else if (c1[i] == 'b') {
			b1++;
		} else if (c1[i] == 'g') {
			g1++;
		}
		if (c2[i] == 'r') {
			r2++;
		} else if (c2[i] == 'b') {
			b2++;
		} else if (c2[i] == 'g') {
			g2++;
		}
	}
	return r1 == r2 && b1 == b2 && g1 == g2;
}

void rotate3Up(char c[]) {
	char t[6];
	t[0] = c[3];
	t[1] = c[1];
	t[2] = c[0];
	t[3] = c[5];
	t[4] = c[4];
	t[5] = c[2];
	for (int i = 0; i < 6; i++) {
		c[i] = t[i];
	}
}

void rotate4Up(char c[]) {
	char t[6];
	t[0] = c[4];
	t[1] = c[0];
	t[2] = c[2];
	t[3] = c[3];
	t[4] = c[5];
	t[5] = c[1];
	for (int i = 0; i < 6; i++) {
		c[i] = t[i];
	}
}

void rotate2Front(char c[]) {
	char t[6];
	t[0] = c[0];
	t[1] = c[2];
	t[2] = c[4];
	t[3] = c[1];
	t[4] = c[3];
	t[5] = c[5];
	for (int i = 0; i < 6; i++) {
		c[i] = t[i];
	}
}

int main(int argc, char * argv[]) {
	string line;
	while (getline(cin, line)) {
		bool isTrue = false;
		char c1[7], c2[7];
		for (int i = 0; i < 6; i++) {
			c1[i] = line[i];
		}
		c1[6] = '\0';
		for (int i = 0; i < 6; i++) {
			c2[i] = line[i + 6];
		}
		c2[6] = '\0';
		if (!hasSameNumColor(c1, c2)) {
			cout << "FALSE" << endl;
			continue;
		}
		for (int i = 0; i < 4; i++) {
			rotate3Up(c1);
			if (c1[0] == c2[0] && c1[5] == c2[5]) {
				for (int j = 0; j < 4; j++) {
					rotate2Front(c1);
					if (strcmp(c1, c2) == 0) {
						isTrue = true;
						break;
					}
				}
			}
			if (isTrue) {
				break;
			}
		}
		if (!isTrue) {
			for (int i = 0; i < 4; i++) {
				rotate4Up(c1);
				if (c1[0] == c2[0] && c1[5] == c2[5]) {
					for (int j = 0; j < 4; j++) {
						rotate2Front(c1);
						if (strcmp(c1, c2) == 0) {
							isTrue = true;
							break;
						}
					}
				}
				if (isTrue) {
					break;
				}
			}
		}
		if (isTrue) {
			cout << "TRUE" << endl;
		} else {
			cout << "FALSE" << endl;
		}
	}
	return 0;
}

