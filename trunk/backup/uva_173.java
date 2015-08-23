import java.util.HashMap;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Map;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.TreeMap;

public class Main {
	static boolean debug = false;

	static char letters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			if (line.equals("#"))
				return;

			int net[][] = new int[26][26];
			int visited[] = new int[26];
			char source = 'A';
			int paskill, lisper, next;
			boolean isTarget = false;

			for (char c : line.toCharArray()) {
				if (c == ':') {
					isTarget = true;
				} else if (c == ';') {
					isTarget = false;
				} else if (c == '.') {
					break;
				} else {
					if (!isTarget) {
						source = c;
					} else {
						net[source - 'A'][c - 'A'] = 1;
						net[c - 'A'][source - 'A'] = 1;
					}
				}
			}
			StringTokenizer st = new StringTokenizer(line);
			st.nextToken();
			paskill = st.nextToken().charAt(0) - 'A';
			lisper = st.nextToken().charAt(0) - 'A';
			boolean paskillTrapped = false, lisperTrapped = false, lisperDestroyed = false, both = false;
			if (paskill == lisper) {
				System.out.println("Both annihilated in node " + letters[paskill]);
				continue;
			}
			visited[paskill] = 1;
			visited[lisper] = 2;
			StringBuilder sb = new StringBuilder();

			for (;;) {

				if (debug) {
					System.out.println("paskill:" + letters[paskill] + ", lisper:" + letters[lisper]);
				}
				next = getNextPaskill(net, visited, paskill);
				if (debug) {
					System.out.println("paskill next:" + letters[next]);
				}
				if (next == -1) {
					paskillTrapped = true;
				} else {
					paskill = next;
				}
				next = getNextLisper(net, visited, lisper);
				if (debug) {
					System.out.println("lisper next:" + letters[next]);
				}

				if (next == -1) {
					lisperTrapped = true;
				} else {
					lisper = next;
					if (visited[lisper] == 1) {
						lisperDestroyed = true;
					}
				}

				if (paskill != -1 && paskill == lisper) {
					both = true;
				}

				if (paskillTrapped) {
					sb.append("Paskill trapped in node ");
					sb.append(letters[paskill]);
				}
				if (lisperTrapped) {
					if (sb.length() > 0) {
						sb.append(" ");
					}
					sb.append("Lisper trapped in node ");
					sb.append(letters[lisper]);
				} else if (!both && lisperDestroyed) {
					if (sb.length() > 0) {
						sb.append(" ");
					}
					sb.append("Lisper destroyed in node ");
					sb.append(letters[lisper]);
				} else if (both) {
					if (sb.length() > 0) {
						sb.append(" ");
					}
					sb.append("Both annihilated in node " + letters[paskill]);
				}
				if (paskillTrapped || lisperTrapped || lisperDestroyed || both) {
					System.out.println(sb.toString());
					break;
				}
				visited[paskill] = 1;
				visited[lisper] = 2;
			}
		}
	}

	private static int getNextLisper(int[][] net, int[] visited, int lisper) {
		int i = lisper;
		while (true) {
			i--;
			if (i < 0)
				i = 25;
			if (i == lisper)
				return -1;

			if (net[lisper][i] != 0 && visited[i] != 2) {
				return i;
			}
		}

	}

	private static int getNextPaskill(int[][] net, int[] visited, int paskill) {
		int i = paskill;
		while (true) {
			i = (i + 1) % 26;
			if (i == paskill)
				return -1;

			if (net[paskill][i] != 0 && visited[i] == 0) {
				return i;
			}
		}
	}
}
