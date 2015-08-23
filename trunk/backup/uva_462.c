#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

/**
 * uva 462
 */

static char cards[13][2];
static int suite[26];

int isStopped(char s) {
	/**
	 * A suit is stopped if it contains an ace, or if it contains a king and at least one other card, or if it contains a queen and at least two other cards.
	 */
	int i;

	for (i = 0; i < 13; i++) {
		if (cards[i][0] == 'A' && cards[i][1] == s)
			return 1;
		if (cards[i][0] == 'K' && suite[cards[i][1] - 'A'] > 1 && cards[i][1] == s)
			return 1;
		if (cards[i][0] == 'Q' && suite[cards[i][1] - 'A'] > 2 && cards[i][1] == s)
			return 1;
	}
	return 0;

}

int rule7() {
	/*
	 * Add two points for each suit in which the hand contains no cards.
	 */
	char s[] = "SHDC";
	int r = 0, i, j;
	for (i = 0; i < 4; i++) {
		if (suite[s[i] - 'A'] == 0) {
			r += 2;
		}
	}
	return r;
}

int rule6() {
	/*
	 * Add two points for each suit in which the hand contains exactly one card.
	 */
	char s[] = "SHDC";
	int r = 0, i;
	for (i = 0; i < 4; i++) {
		if (suite[s[i] - 'A'] == 1)
			r += 2;
	}
	return r;
}

int rule5() {
	/*
	 * Add a point for each suit in which the hand contains exactly two cards
	 */
	char s[] = "SHDC";
	int r = 0, i;
	for (i = 0; i < 4; i++) {
		if (suite[s[i] - 'A'] == 2)
			r += 1;
	}
	return r;
}

int rule4() {
	/*
	 * Subtract a point for any jack in a suit in which the hand holds only zero, one, or two other cards.
	 */
	int r = 0, i;
	for (i = 0; i < 13; i++) {
		if (cards[i][0] == 'J') {
			int n = suite[cards[i][1] - 'A'];
			if (n == 1 || n == 2 || n == 3)
				r -= 1;
		}
	}
	return r;
}

int rule3() {
	/*
	 * Subtract a point for any queen in a suit in which the hand holds only zero or one other cards
	 */
	int r = 0, i;
	for (i = 0; i < 13; i++) {
		if (cards[i][0] == 'Q') {
			int n = suite[cards[i][1] - 'A'];
			if (n == 1 || n == 2)
				r -= 1;
		}
	}
	return r;
}

int rule2() {
	/*
	 * Subtract a point for any king of a suit in which the hand holds no other cards
	 */
	int r = 0, i;
	for (i = 0; i < 13; i++) {
		if (cards[i][0] == 'K') {
			if (suite[cards[i][1] - 'A'] == 1) {
				r -= 1;
			}
		}
	}
	return r;
}

int rule1() {
	/*
	 * Each ace counts 4 points. Each king counts 3 points. Each queen counts 2 points. Each jack counts one point.
	 */
	int r = 0, i;
	for (i = 0; i < 13; i++) {
		if (cards[i][0] == 'A') {
			r += 4;
		}
		if (cards[i][0] == 'K') {
			r += 3;
		}
		if (cards[i][0] == 'Q') {
			r += 2;
		}
		if (cards[i][0] == 'J') {
			r += 1;
		}
	}
	return r;
}

int main() {
	int i, start, n;
	char line[256];
	for (; fgets(line, 256, stdin) != NULL;) {
		start = 0, n = 0;
		memset(suite, 0, sizeof(int) * 26);
		for (i = 0; i < strlen(line); i++) {
			char c = line[i];
			if ((c >= '2' && c <= '9') || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K') {
				cards[n][0] = c;
				start = 1;
			} else if (c == 'S' || c == 'H' || c == 'D' || c == 'C') {
				cards[n][1] = c;
				suite[c - 'A']++;
			} else {
				if (start) {
					n++;
				}
			}
		}
		int p1234 = rule1() + rule2() + rule3() + rule4();
		int p567 = rule5() + rule6() + rule7();

		if (p1234 + p567 < 14) {
			printf("PASS\n");
		} else if (p1234 >= 16 && isStopped('S') && isStopped('H') && isStopped('D') && isStopped('C')) {
			printf("BID NO-TRUMP\n");
		} else {
			char maxS;
			int maxCards = 0;
			char s[] = "SHDC";
			for (i = 0; i < 4; i++) {
				if (suite[s[i] - 'A'] > maxCards) {
					maxCards = suite[s[i] - 'A'];
					maxS = s[i];
				}
			}
			printf("BID %c\n", maxS);
		}

	}
	return 0;
}

