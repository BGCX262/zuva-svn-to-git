import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

public class Main {
	public static boolean debug = false;
	private static Map<Character, Character> reverses = new HashMap<Character, Character>();
	static {
		reverses.put(new Character('A'), new Character('A'));
		reverses.put(new Character('E'), new Character('3'));
		reverses.put(new Character('H'), new Character('H'));
		reverses.put(new Character('I'), new Character('I'));
		reverses.put(new Character('J'), new Character('L'));
		reverses.put(new Character('L'), new Character('J'));
		reverses.put(new Character('M'), new Character('M'));
		reverses.put(new Character('O'), new Character('O'));
		reverses.put(new Character('S'), new Character('2'));
		reverses.put(new Character('T'), new Character('T'));
		reverses.put(new Character('U'), new Character('U'));
		reverses.put(new Character('V'), new Character('V'));
		reverses.put(new Character('W'), new Character('W'));
		reverses.put(new Character('X'), new Character('X'));
		reverses.put(new Character('Y'), new Character('Y'));
		reverses.put(new Character('Z'), new Character('5'));
		reverses.put(new Character('1'), new Character('1'));
		reverses.put(new Character('2'), new Character('S'));
		reverses.put(new Character('3'), new Character('E'));
		reverses.put(new Character('5'), new Character('Z'));
		reverses.put(new Character('8'), new Character('8'));
	}

	public static boolean isPalindrome(String line) {
		int mid = line.length() / 2;
		for (int i = 0; i < mid; i++) {
			Character head = new Character(line.charAt(i));
			Character tail = new Character(line.charAt(line.length() - 1 - i));
			if (!head.equals(tail)) {
				return false;
			}
		}
		return true;
	}

	public static boolean isMirrored(String line) {
		StringBuilder sb = new StringBuilder();
		int hasReverse = 0;
		for (int i = 0; i < line.length(); i++) {
			Character head = new Character(line.charAt(i));
			if (reverses.containsKey(head)) {
				head = reverses.get(head);
				hasReverse++;
			}
			sb.append(head);
		}

		if (hasReverse != line.length())
			return false;

		for (int i = 0; i < line.length() / 2; i++) {
			Character head = new Character(line.charAt(i));
			Character tail = new Character(sb.toString().charAt(line.length() - 1 - i));
			if (!head.equals(tail)) {
				return false;
			}
		}
		return true;
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			boolean palindrome = isPalindrome(line), mirrored = isMirrored(line);
			if (!palindrome && !mirrored) {
				System.out.println(line + " -- is not a palindrome.\n");
			} else if (palindrome && !mirrored) {
				System.out.println(line + " -- is a regular palindrome.\n");
			} else if (!palindrome && mirrored) {
				System.out.println(line + " -- is a mirrored string.\n");
			} else {
				System.out.println(line + " -- is a mirrored palindrome.\n");
			}
		}
	}
}