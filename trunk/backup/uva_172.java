import java.util.HashMap;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Map;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.TreeMap;

public class Main {
	static boolean debug = false;
	static Map<String, Long> previous = new HashMap<String, Long>();
	static Map<String, Long> current = new HashMap<String, Long>();
	static Map<String, Long> change = new TreeMap<String, Long>();
	static LinkedList<String> epr = new LinkedList<String>();

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		while (cin.hasNext()) {
			String line = cin.nextLine();
			if (line.equals("#"))
				return;
			StringBuilder sb = new StringBuilder();
			for (char c : line.toCharArray()) {
				if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
					sb.append(" ");
					sb.append(c);
					sb.append(" ");
				} else
					sb.append(c);
			}
			for (String s : current.keySet()) {
				previous.put(s, current.get(s));
			}
			current.clear();
			change.clear();
			epr.clear();
			StringTokenizer st = new StringTokenizer(sb.toString());
			while (st.hasMoreTokens()) {
				epr.add(st.nextToken());
			}

			calExp();

			for (String s : current.keySet()) {
				if (previous.containsKey(s) && current.get(s) != previous.get(s)) {
					change.put(s, current.get(s));
				} else if (!previous.containsKey(s) && current.get(s) != 0) {
					change.put(s, current.get(s));
				}
			}

			boolean firstKey = true;
			if (change.size() == 0) {
				System.out.println("No Change");
				continue;
			}

			for (String v : change.keySet()) {
				if (firstKey) {
					System.out.print(v + " = " + change.get(v));
					firstKey = false;
				} else {
					System.out.print(", " + v + " = " + change.get(v));
				}
			}
			System.out.print("\n");
		}
	}

	static long calExp() {
		if (debug) {
			System.out.println("calExp: ");
			System.out.println(epr);
		}
		long dig1 = 0, dig2 = 0, result = 0;
		String opr = "";
		boolean firstDig = false;
		boolean assign = false;
		while (epr.size() > 0) {
			if (debug) {
				System.out.println("firstDig: " + firstDig + ", assign:" + assign);
				System.out.println(epr);
			}
			String s = epr.getLast();
			epr.removeLast();
			if (validateNum(s)) {
				if (!firstDig) {
					dig2 = getNum(s);
					result = dig2;
					firstDig = true;
				} else {
					firstDig = false;
					dig1 = getNum(s);
					result = calculate(dig1, opr, dig2);
					epr.addLast(new Long(result).toString());
				}
			} else if (validateVar(s) && !assign) {
				long dig = 0;
				if (current.containsKey(s)) {
					dig = current.get(s);
				} else if (previous.containsKey(s)) {
					dig = previous.get(s);
					current.put(s, dig);
				} else {
					current.put(s, dig);
				}
				if (!firstDig) {
					dig2 = dig;
					result = dig2;
					firstDig = true;
				} else {
					firstDig = false;
					dig1 = dig;
					result = calculate(dig1, opr, dig2);
					epr.addLast(new Long(result).toString());
				}
			} else if (validateVar(s) && assign) {
				current.put(s, result);
				epr.addLast(new Long(result).toString());
				assign = false;
				firstDig = false;
			} else if (s.equals("=")) {
				assign = true;
			} else if (s.equals("+") || s.equals("-") || s.equals("*") || s.equals("/")) {
				opr = s;
			} else if (s.equals(")")) {
				result = calExp();
				epr.addLast(new Long(result).toString());
			} else if (s.equals("(")) {
				return result;
			}
		}
		return result;
	}

	private static long calculate(long dig1, String opr, long dig2) {
		if (opr.equals("+")) {
			return dig1 + dig2;
		} else if (opr.equals("-")) {
			return dig1 - dig2;
		} else if (opr.equals("*")) {
			return dig1 * dig2;
		} else if (opr.equals("/")) {
			return dig1 / dig2;
		}
		throw new IllegalArgumentException();
	}

	/**
	 * Validates if input String is a number
	 */
	static public long getNum(String in) {
		boolean isNegative = false;
		if (in.charAt(0) == '_') {
			isNegative = true;
			in = in.substring(1);
		}

		long result = Long.parseLong(in);
		if (isNegative) {
			result = 0 - result;
		}
		return result;
	}

	/**
	 * Validates if input String is a number
	 */
	static public boolean validateNum(String in) {
		if (in.length() == 1 && in.equals("-"))
			return false;

		for (int i = 0; i < in.length(); i++) {
			if (i == 0 && (in.charAt(i) == '_' || in.charAt(i) == '-'))
				continue;

			if (in.charAt(i) < '0' || in.charAt(i) > '9') {
				return false;
			}
		}
		return true;
	}

	/**
	 * Validates if input String is a Uppercase letters
	 */
	static public boolean validateVar(String in) {
		for (char c : in.toCharArray()) {
			if (c < 'A' || c > 'Z') {
				return false;
			}
		}
		return true;
	}
}