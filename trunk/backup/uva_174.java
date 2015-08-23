import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.TreeMap;

enum Command {
	TRADE, CHEAT, NULL
};

enum Op {
	AND, OR
};

enum Memory {
	MYLAST1, MYLAST2, YOURLAST1, YOURLAST2
}

public class Main {
	public static boolean debug = false;
	public static Command[][] mem1;
	public static Command[][] mem2;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		StringBuilder sb = new StringBuilder();
		ArrayList<Strategy> all = new ArrayList<Strategy>();
		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			if (line.equals("#"))
				break;

			if (line.charAt(line.length() - 1) == '.') {
				sb.append(line.substring(0, line.length() - 1));
				ArrayList<String> arr = splitLine(sb);
				if (debug) {
					System.out.println("line:" + arr);
				}
				Statement statement = new Statement(arr);
				if (Main.debug) {
					System.out.println("Statement:" + statement.toString());
				}
				all.add(new Strategy(statement));
				sb = new StringBuilder();
			} else {
				if (sb == null)
					sb = new StringBuilder();
				sb.append(line);
			}
		}
		if (debug) {
			System.out.println("===================================================================");
			System.out.println(all);
		}
		mem1 = new Command[all.size()][all.size()];
		mem2 = new Command[all.size()][all.size()];
		for (int i = 0; i < all.size(); i++) {
			for (int j = 0; j < all.size(); j++) {
				mem1[i][j] = Command.NULL;
				mem2[i][j] = Command.NULL;
			}
		}

		// begin

		for (int i = 0; i < all.size() - 1; i++) {
			for (int j = i + 1; j < all.size(); j++) {
				for (int t = 0; t < 10; t++) {

					Strategy s1 = all.get(i);
					Strategy s2 = all.get(j);
					if (debug) {
						System.out.println("===================================================================");
						System.out.println("i:" + i + ", " + s1 + ", mem1:" + Main.mem1[i][j] + ", mem2:" + Main.mem2[i][j]);
						System.out.println("j:" + j + ", " + s2 + ", mem1:" + Main.mem1[j][i] + ", mem2:" + Main.mem2[j][i]);
					}

					Command c1 = s1.play(i, j);
					Command c2 = s2.play(j, i);
					if (c1 == Command.TRADE && c2 == Command.TRADE) {
						s1.points++;
						s2.points++;
					}
					if (c1 == Command.CHEAT && c2 == Command.CHEAT) {
						s1.points--;
						s2.points--;
					}
					if (c1 == Command.TRADE && c2 == Command.CHEAT) {
						s1.points -= 2;
						s2.points += 2;
					}
					if (c1 == Command.CHEAT && c2 == Command.TRADE) {
						s1.points += 2;
						s2.points -= 2;
					}
					mem2[i][j] = mem1[i][j];
					mem1[i][j] = c1;
					mem2[j][i] = mem1[j][i];
					mem1[j][i] = c2;
					if (debug) {
						System.out.println("i:" + i + ", " + s1 + ", mem1:" + Main.mem1[i][j] + ", mem2:" + Main.mem2[i][j]);
						System.out.println("j:" + j + ", " + s2 + ", mem1:" + Main.mem1[j][i] + ", mem2:" + Main.mem2[j][i]);
					}
				}
			}
		}

		for (Strategy s : all) {
			System.out.printf("%3d\n", s.points);
		}
	}

	private static ArrayList<String> splitLine(StringBuilder sb) {
		ArrayList<String> result = new ArrayList<String>();
		String s = sb.toString();
		s = s.replaceAll(" ", "");
		s = s.replaceAll("IF", " IF ");
		s = s.replaceAll("THEN", " THEN ");
		s = s.replaceAll("ELSE", " ELSE ");
		s = s.replaceAll("AND", " AND ");
		s = s.replaceAll("OR", " OR ");
		s = s.replaceAll("=", " = ");
		s = s.replaceAll("#", " # ");
		s = s.replaceAll("MY", " MY ");
		s = s.replaceAll("YOUR", " YOUR ");
		s = s.replaceAll("LAST1", " LAST1 ");
		s = s.replaceAll("LAST2", " LAST2 ");
		s = s.replaceAll("TRADE", " TRADE ");
		s = s.replaceAll("CHEAT", " CHEAT ");
		s = s.replaceAll("NULL", " NULL ");
		StringTokenizer st = new StringTokenizer(s);
		while (st.hasMoreTokens()) {
			result.add(st.nextToken());
		}
		return result;
	}

}

class Strategy {
	int points;
	Statement statement;

	Strategy(Statement s) {
		this.statement = s;
	}

	public Command play(int s1, int s2) {
		return this.statement.cal(s1, s2);
	}

	public String toString() {
		return "points:" + points;
	}
}

class Statement {
	Command cmd = Command.NULL;
	Ifstat ifstat;

	Statement(List<String> list) {
		// remove THEN, ELSE
		if (list.get(0).equals("THEN") || list.get(0).equals("ELSE"))
			list.remove(0);
		if (list.get(0).equals("CHEAT")) {
			list.remove(0);
			cmd = Command.CHEAT;
		} else if (list.get(0).equals("TRADE")) {
			list.remove(0);
			cmd = Command.TRADE;
		} else if (list.get(0).equals("IF")) {
			ifstat = new Ifstat(list);
		}
	}

	Command cal(int my, int your) {
		if (cmd != Command.NULL)
			return cmd;
		return ifstat.cal(my, your);
	}

	public String toString() {
		String s = "Command: " + cmd + ",";
		if (ifstat != null) {
			s += "Ifstat: " + ifstat;
		}
		return s;
	}
}

class Ifstat {
	Condition condition;
	Statement thenSt, elseSt;

	Ifstat(List<String> list) {
		// remove "IF"
		list.remove(0);
		condition = new Condition(list);
		thenSt = new Statement(list);
		elseSt = new Statement(list);
	}

	Command cal(int my, int your) {
		if (condition.cal(my, your))
			return thenSt.cal(my, your);
		else
			return elseSt.cal(my, your);
	}

	public String toString() {
		return "Condition:" + condition.toString() + "\n" + "then:" + thenSt + "\n" + "elseSt:" + elseSt;
	}
}

class Condition {
	Cond cond;
	Op op;
	Condition condition;

	Condition(List<String> list) {

		cond = new Cond(list);
		if (list.size() > 0) {
			if (list.get(0).equals("AND")) {
				op = Op.AND;
				list.remove(0);
				condition = new Condition(list);
			} else if (list.get(0).equals("OR")) {
				op = Op.OR;
				list.remove(0);
				condition = new Condition(list);
			}
		}
	}

	public boolean cal(int my, int your) {
		boolean result = cond.cal(my, your);
		if (op == Op.AND) {
			result = result && condition.cal(my, your);
		} else if (op == Op.OR) {
			result = result || condition.cal(my, your);
		}
		return result;
	}

	public String toString() {
		String s = "cond:" + cond + ", ";
		if (op != null) {
			s += ("op:" + op);
			s += "condition:" + condition;
		}
		return s;
	}
}

class Cond {
	Memory memory;
	boolean equals;
	Command command;

	Cond(List<String> list) {
		if (list.size() > 3) {
			if (list.get(0).equals("MY")) {
				if (list.get(1).equals("LAST1")) {
					memory = Memory.MYLAST1;
				} else if (list.get(1).equals("LAST2")) {
					memory = Memory.MYLAST2;
				}
			} else if (list.get(0).equals("YOUR")) {
				if (list.get(1).equals("LAST1")) {
					memory = Memory.YOURLAST1;
				} else if (list.get(1).equals("LAST2")) {
					memory = Memory.YOURLAST2;
				}
			}
			if (list.get(2).equals("=")) {
				equals = true;
			} else if (list.get(2).equals("#")) {
				equals = false;
			}

			if (list.get(3).equals("TRADE")) {
				command = Command.TRADE;
			} else if (list.get(3).equals("CHEAT")) {
				command = Command.CHEAT;
			} else if (list.get(3).equals("NULL")) {
				command = Command.NULL;
			}

			list.remove(0);
			list.remove(0);
			list.remove(0);
			list.remove(0);
		}
	}

	public boolean cal(int my, int your) {
		Command temp = Command.NULL;
		switch (memory) {
		case MYLAST1:
			temp = Main.mem1[my][your];
			break;
		case MYLAST2:
			temp = Main.mem2[my][your];
			break;
		case YOURLAST1:
			temp = Main.mem1[your][my];
			break;
		case YOURLAST2:
			temp = Main.mem2[your][my];
			break;
		}
		if (equals) {
			return temp == command;
		} else {
			return temp != command;
		}

	}

	public String toString() {
		return "Memory:" + memory + ", equals:" + equals + ", command:" + command;
	}
}
