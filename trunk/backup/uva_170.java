import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		boolean debug = false;
		String s;
		ArrayList<Card> deck = new ArrayList<Card>();
		ArrayList<Pile> piles = new ArrayList<Pile>();
		int i, token;
		Pile pile;
		Card card;
		while (cin.hasNext()) {
			s = cin.next();
			if (s.equals("#"))
				return;

			card = new Card(s);
			deck.add(card);
			for (i = 0; i < 51; i++) {
				s = cin.next();
				card = new Card(s);
				deck.add(card);
			}

			piles.add(0, null);
			for (i = 1; i <= 13; i++) {
				piles.add(i, new Pile());
			}
			token = 1;
			for (i = 51; i >= 0; i--) {
				card = deck.get(i);
				piles.get(token).add(card);
				token++;
				if (token > 13)
					token = 1;
			}
			token--;
			if (token == 0)
				token = 13;
			card = null;
			if (debug) {
				printInfo(piles);
			}

			for (i = 0;; i++) {
				pile = piles.get(token);
				if (!pile.hasFaceDown())
					break;
				card = pile.expose();

				token = card.pile;
				card.faceDown = false;
				piles.get(token).insert(card);

				if (debug) {
					System.out.println("token:" + token + ",i:" + i + ",card:" + card.toString());
					printInfo(piles);
				}

			}
			System.out.println((i < 10 ? "0" + new Integer(i).toString() : new Integer(i).toString()) + "," + card.rank + card.suit);
			deck.clear();
			piles.clear();
		}
	}

	static void printInfo(ArrayList<Pile> piles) {
		System.out.println("Piles:");
		for (int i2 = 1; i2 <= 13; i2++) {
			System.out.print("pile" + i2 + " ");
			for (Card c2 : piles.get(i2).cards) {
				System.out.print(c2.toString());
			}
			System.out.println("...");
		}
		System.out.println("...");
	}
}

class Pile {
	String str;
	LinkedList<Card> cards = new LinkedList<Card>();

	void add(Card c) {
		cards.addLast(c);
	}

	void insert(Card c) {
		cards.addFirst(c);
	}

	Card expose() {
		return cards.removeLast();
	}

	boolean hasFaceDown() {
		if (cards.size() == 0)
			return false;
		return cards.getLast().faceDown;
	}
}

class Card {
	char suit;
	int pile;
	char rank;
	boolean faceDown = true;

	Card(String s) {
		suit = s.charAt(1);
		rank = s.charAt(0);
		switch (rank) {
		case 'A':
			this.pile = 1;
			break;
		case '2':
			this.pile = 2;
			break;
		case '3':
			this.pile = 3;
			break;
		case '4':
			this.pile = 4;
			break;
		case '5':
			this.pile = 5;
			break;
		case '6':
			this.pile = 6;
			break;
		case '7':
			this.pile = 7;
			break;
		case '8':
			this.pile = 8;
			break;
		case '9':
			this.pile = 9;
			break;
		case 'T':
			this.pile = 10;
			break;
		case 'J':
			this.pile = 11;
			break;
		case 'Q':
			this.pile = 12;
			break;
		case 'K':
			this.pile = 13;
			break;
		}
	}

	public String toString() {
		return "" + rank + suit + (this.faceDown ? "D" : "U") + " ";
	}
}
