import java.util.HashMap;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;
import java.util.StringTokenizer;

enum sym {
	NULL, instruction, navigational, directional, how, direction, when, where, sign, signwords, sword, letter, timekeeping, record, change, cas, nnn, digit, AND, THEN, GO, KEEP, RIGHT, LEFT, FIRST, SECOND, THIRD, AT, RECORD, TIME, TO, KMH, CHANGE, AVERAGE, SPEED, CAS
}

public class Main {
	/**
	 * [symbol][subfix1][subfix2][subfix3][target symbol]
	 */
	static sym state[][] = { { sym.CHANGE, sym.AVERAGE, sym.SPEED, sym.NULL, sym.cas }, { sym.CAS, sym.NULL, sym.NULL, sym.NULL, sym.cas },
			{ sym.cas, sym.TO, sym.nnn, sym.KMH, sym.change }, { sym.RECORD, sym.TIME, sym.NULL, sym.NULL, sym.record },
			{ sym.record, sym.NULL, sym.NULL, sym.NULL, sym.timekeeping }, { sym.change, sym.NULL, sym.NULL, sym.NULL, sym.timekeeping },
			{ sym.AT, sym.sign, sym.NULL, sym.NULL, sym.where }, { sym.FIRST, sym.NULL, sym.NULL, sym.NULL, sym.when },
			{ sym.SECOND, sym.NULL, sym.NULL, sym.NULL, sym.when }, { sym.THIRD, sym.NULL, sym.NULL, sym.NULL, sym.when },
			{ sym.RIGHT, sym.NULL, sym.NULL, sym.NULL, sym.direction }, { sym.LEFT, sym.NULL, sym.NULL, sym.NULL, sym.direction },
			{ sym.GO, sym.when, sym.NULL, sym.NULL, sym.how }, { sym.GO, sym.NULL, sym.NULL, sym.NULL, sym.how },
			{ sym.KEEP, sym.NULL, sym.NULL, sym.NULL, sym.how }, { sym.how, sym.direction, sym.where, sym.NULL, sym.directional },
			{ sym.how, sym.direction, sym.NULL, sym.NULL, sym.directional }, { sym.directional, sym.AND, sym.THEN, sym.directional, sym.navigational },
			{ sym.directional, sym.NULL, sym.NULL, sym.NULL, sym.navigational }, { sym.navigational, sym.AND, sym.THEN, sym.directional, sym.navigational },
			{ sym.navigational, sym.AND, sym.THEN, sym.navigational, sym.navigational },
			{ sym.navigational, sym.AND, sym.timekeeping, sym.NULL, sym.instruction }, { sym.navigational, sym.NULL, sym.NULL, sym.NULL, sym.instruction },
			{ sym.timekeeping, sym.NULL, sym.NULL, sym.NULL, sym.instruction } };

	static HashMap<String, sym> dict = new HashMap<String, sym>();

	static void init() {
		dict.put("CHANGE", sym.CHANGE);
		dict.put("AVERAGE", sym.AVERAGE);
		dict.put("SPEED", sym.SPEED);
		dict.put("CAS", sym.CAS);
		dict.put("TO", sym.TO);
		dict.put("KMH", sym.KMH);
		dict.put("RECORD", sym.RECORD);
		dict.put("TIME", sym.TIME);
		dict.put("AT", sym.AT);
		dict.put("FIRST", sym.FIRST);
		dict.put("SECOND", sym.SECOND);
		dict.put("THIRD", sym.THIRD);
		dict.put("RIGHT", sym.RIGHT);
		dict.put("LEFT", sym.LEFT);
		dict.put("GO", sym.GO);
		dict.put("KEEP", sym.KEEP);
		dict.put("AND", sym.AND);
		dict.put("THEN", sym.THEN);
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		init();
		boolean debug = false;
		if (args.length == 1)
			debug = true;

		LinkedList<sym> all = new LinkedList<sym>();
		boolean isSign = false;
		boolean isTrap = false;

		Integer line = 0;
		while (cin.hasNext()) {

			line++;
			String s = cin.nextLine();
			if (s.equals("#"))
				return;

			boolean startBlank = false;
			boolean endBlank = false;
			if (s.length() > 0 && s.charAt(0) == ' ')
				startBlank = true;
			if (s.length() > 0 && s.charAt(s.length() - 1) == ' ')
				endBlank = true;

			StringTokenizer st = new StringTokenizer(s);
			all.clear();
			isSign = false;
			int signNum = 0;
			isTrap = false;

			while (st.hasMoreTokens()) {
				String word = st.nextToken();
				if (debug) {
					System.out.println("word:" + word);
				}

				if (!isSign && dict.containsKey(word)) {
					all.addLast(dict.get(word));
				} else if (!isSign && checkIfNumber(word)) {
					all.addLast(sym.nnn);
				} else if (validateSign(word)) {
					if (debug) {
						System.out.println("validate word");
					}

					if (word.length() > 1 && word.charAt(0) == '"' && word.charAt(word.length() - 1) != '"' && !isSign) {
						if (debug) {
							System.out.println("word.length() > 1 && word.charAt(0) == '\"' && word.charAt(word.length() - 1) != '\"' && !isSign ");
						}
						isSign = true;
						signNum++;
						continue;
					}

					if (word.length() > 1 && word.charAt(word.length() - 1) == '"' && word.charAt(0) != '"' && isSign) {
						if (debug) {
							System.out.println("word.length() > 1 && word.charAt(word.length() - 1) == '\"' && word.charAt(0) != '\"' && isSign");
						}
						isSign = false;
						signNum = 0;
						all.addLast(sym.sign);
						continue;
					}

					if (word.length() > 2 && word.charAt(word.length() - 1) == '"' && word.charAt(0) == '"' && !isSign) {
						if (debug) {
							System.out
									.println("word.length() > 2 && word.charAt(word.length() - 1) == '\"' && word.charAt(0) == '\"' && !isSign && signNum > 0");
						}
						isSign = false;
						signNum = 0;
						all.addLast(sym.sign);
						continue;
					}

					if (word.indexOf("\"") == -1 && isSign) {
						if (debug) {
							System.out.println("word.indexOf(\"\"\") == -1 && isSign");
						}
						signNum++;
						continue;
					}

					isTrap = true;
					break;
				} else {
					isTrap = true;
					break;
				}
			}
			if (isSign) {
				isTrap = true;
			}

			if (!isTrap) {
				for (int i = 0; i < state.length; i++) {
					ListIterator<sym> lt = all.listIterator();
					while (lt.hasNext()) {
						sym sm0 = lt.next();
						if (state[i][0] != sm0) {
							continue;
						}
						if (state[i][1] != sym.NULL && state[i][2] != sym.NULL && state[i][3] != sym.NULL) {
							if (!lt.hasNext())
								continue;

							if (state[i][1] == lt.next()) {
								if (!lt.hasNext())
									continue;

								if (state[i][2] == lt.next()) {
									if (!lt.hasNext())
										continue;

									if (state[i][3] == lt.next()) {
										// match
										lt.remove();
										lt.previous();
										lt.remove();
										lt.previous();
										lt.remove();
										lt.previous();
										lt.remove();
										lt.add(state[i][4]);
									} else {
										lt.previous();
										lt.previous();
										lt.previous();
									}
								} else {
									lt.previous();
									lt.previous();
								}
							} else {
								lt.previous();
							}
						} else if (state[i][1] != sym.NULL && state[i][2] != sym.NULL) {
							if (!lt.hasNext())
								continue;

							if (state[i][1] == lt.next()) {
								if (!lt.hasNext())
									continue;

								if (state[i][2] == lt.next()) {
									// match
									lt.remove();
									lt.previous();
									lt.remove();
									lt.previous();
									lt.remove();
									lt.add(state[i][4]);
								} else {
									lt.previous();
									lt.previous();
								}
							} else {
								lt.previous();
							}
						} else if (state[i][1] != sym.NULL) {
							if (!lt.hasNext())
								continue;

							if (state[i][1] == lt.next()) {
								// match
								lt.remove();
								lt.previous();
								lt.remove();
								lt.add(state[i][4]);
							} else {
								lt.previous();
							}
						} else {
							// match
							lt.remove();
							lt.add(state[i][4]);
						}
					}
					if (debug) {
						for (sym sm : all) {
							System.out.print(sm + " ");
						}
						System.out.println("");
					}
				}

				if (all.size() != 1 || all.get(0) != sym.instruction) {
					isTrap = true;
				}
			}
			if (isTrap) {
				System.out.printf("%3d. Trap!\n", line);
				continue;
			}

			StringTokenizer st2 = new StringTokenizer(s);
			System.out.printf("%3d.", line);
			if (startBlank) {
				System.out.print(" ");
			}
			while (st2.hasMoreTokens()) {
				System.out.print(" " + st2.nextToken());
			}
			if (endBlank) {
				System.out.print(" ");
			}
			System.out.printf("\n");
		}
	}

	/**
	 * Validates if input String is a number
	 */
	static public boolean checkIfNumber(String in) {
		for (char c : in.toCharArray()) {
			if (c < '0' || c > '9') {
				return false;
			}
		}
		return true;
	}

	/**
	 * Validates if input String is a Uppercase letters
	 */
	static public boolean validateSign(String in) {

		if (in.length() == 1 && in.charAt(0) == '"')
			return false;
		if (in.charAt(0) == '.')
			return false;
		if (in.length() == 2 && in.charAt(0) == '"' && in.charAt(1) == '"')
			return false;

		int sign = 0;
		for (char c : in.toCharArray()) {
			if (c == '"') {
				sign++;
				continue;
			}
			if (c == '.')
				continue;

			if (c < 'A' || c > 'Z') {
				return false;
			}
		}

		if (sign > 2)
			return false;
		return true;
	}
}