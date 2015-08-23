#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

enum Suites {
	S, H, D, C
};

enum Values {
	A, N2, N3, N4, N5, N6, N7, N8, N9, T, J, Q, K
};

struct Card {
	enum Suites s;
	enum Values v;
};

static struct Card * dealer[52];
static int dealerSize = 0;
static struct Card * nonDealer[52];
static int nonDealerSize = 0;
static struct Card * desk[52];
static int deskSize = 0;
/**
 * 0 - non-dealer's turn to play card
 * 1 - dealer's turn
 */
static int turn = 0;
static int lastFace;

struct Card * getCard(char c[]) {
	struct Card * card = (struct Card *) malloc(sizeof(struct Card));
	switch (c[0]) {
	case 'S':
		card->s = S;
		break;
	case 'H':
		card->s = H;
		break;

	case 'D':
		card->s = D;
		break;
	case 'C':
		card->s = C;
		break;
	}

	switch (c[1]) {
	case 'A':
		card->v = A;
		break;
	case '2':
		card->v = N2;
		break;
	case '3':
		card->v = N3;
		break;
	case '4':
		card->v = N4;
		break;
	case '5':
		card->v = N5;
		break;
	case '6':
		card->v = N6;
		break;
	case '7':
		card->v = N7;
		break;
	case '8':
		card->v = N8;
		break;
	case '9':
		card->v = N9;
		break;
	case 'T':
		card->v = T;
		break;
	case 'J':
		card->v = J;
		break;
	case 'Q':
		card->v = Q;
		break;
	case 'K':
		card->v = K;
		break;
	}
	return card;
}

void printCard(struct Card * cards[], int size) {
/*	printf("size:%d\n",size);*/
	int i;
	for (i = 0; i < size; i++) {
		switch (cards[i]->s) {
		case S:
			printf("S");
			break;
		case H:
			printf("H");
			break;
		case D:
			printf("D");
			break;
		case C:
			printf("C");
			break;
		}

		switch (cards[i]->v) {
		case A:
			printf("A");
			break;
		case N2:
			printf("2");
			break;
		case N3:
			printf("3");
			break;
		case N4:
			printf("4");
			break;
		case N5:
			printf("5");
			break;
		case N6:
			printf("6");
			break;
		case N7:
			printf("7");
			break;
		case N8:
			printf("8");
			break;
		case N9:
			printf("9");
			break;
		case T:
			printf("T");
			break;
		case J:
			printf("J");
			break;
		case Q:
			printf("Q");
			break;
		case K:
			printf("K");
			break;
		}
		printf(" ");
	}
	printf("\n");
}

void printInfo() {
	printf("non-dealers:\n");
	printCard(nonDealer, nonDealerSize);
	printf("dealers:\n");
	printCard(dealer, dealerSize);
	printf("desk:\n");
	printCard(desk, deskSize);
}

int isFaceCard(struct Card * fCard) {
	if (fCard->v == A || fCard->v == K || fCard->v == Q || fCard->v == J)
		return 1;
	return 0;
}

struct Card * faceupACard() {
	if (turn == 0) {
		if (nonDealerSize == 0)
			return NULL;
		return nonDealer[--nonDealerSize];
	} else {
		if (dealerSize == 0)
			return NULL;
		return dealer[--dealerSize];
	}
}

void place() {
	/*if (DEBUG) {
		printf("before placing.......\n");
		printInfo();
	}
	*/
	int i;
	if (lastFace == 0) {
		for (i = nonDealerSize + deskSize - 1; i >= deskSize; i--) {
			nonDealer[i] = nonDealer[i - deskSize];
		}
		for (i = 0; i < deskSize; i++) {
			nonDealer[i] = desk[deskSize - 1 - i];
		}
		nonDealerSize += deskSize;
	} else {
		for (i = dealerSize + deskSize - 1; i >= deskSize; i--) {
			dealer[i] = dealer[i - deskSize];
		}
		for (i = 0; i < deskSize; i++) {
			dealer[i] = desk[deskSize - 1 - i];
		}
		dealerSize += deskSize;
	}
	deskSize = 0;
	/*if (DEBUG) {
		printf("after placing.......\n");
		printInfo();
	}*/
}

int cover() {
	lastFace = ~turn;
	int howManyCover = 0;
	if (desk[deskSize - 1]->v == J) {
		howManyCover = 1;
	} else if (desk[deskSize - 1]->v == Q) {
		howManyCover = 2;
	} else if (desk[deskSize - 1]->v == K) {
		howManyCover = 3;
	} else if (desk[deskSize - 1]->v == A) {
		howManyCover = 4;
	}

	int i, j, r;
	struct Card * fCard;
	for (i = 0; i < howManyCover; i++) {
		fCard = faceupACard();
		if (fCard == NULL) {
			return 0;
		}
		desk[deskSize++] = fCard;
		if (isFaceCard(fCard)) {
			turn = ~turn;
			return cover();
		}
	}
	/**
	 * placing cards to turn player
	 */
	place();
	return 1;
}

void play() {
	if (DEBUG)
		printInfo();

	while (1) {
		struct Card * fCard = faceupACard();
		if (fCard == NULL) {
			break;
		}
		desk[deskSize++] = fCard;
		turn = ~turn;
		if (DEBUG) {
			printInfo();
		}

		if (isFaceCard(fCard)) {
			/**
			 * needs to be covered
			 */
			if (DEBUG) {
				printf("needs to be covered\n");
			}
			if (cover() == 0)
				break;

			turn = lastFace;
		}
	}
	/**
	 * game over
	 */
	if (DEBUG) {
		printf("Game over!\n");
		printInfo();
	}
	if (turn == 0) {
		printf("1");
		printf("%3d\n", dealerSize);
	} else {
		printf("2");
		printf("%3d\n", nonDealerSize);
	}

}

int main(int argv, char * argc[]) {
	int i, j, r;
	char c[3];

	while (1) {
		r = scanf("%s", c);
		if (c[0] == '#')
			break;
		turn = 0;
		dealerSize = 0;
		nonDealerSize = 0;
		deskSize = 0;
		nonDealer[nonDealerSize++] = getCard(c);
		for (i = 1; i < 52; i++) {
			r = scanf("%s", c);
			if (i % 2 == 0) {
				nonDealer[nonDealerSize++] = getCard(c);
			} else {
				dealer[dealerSize++] = getCard(c);
			}
		}

		play();

	}
	return 0;
}
