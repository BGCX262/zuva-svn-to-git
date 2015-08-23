import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;
import java.util.Set;
import java.util.Stack;
import java.util.StringTokenizer;

/**
 * uva 188
 */
public class Main {
	static boolean debug = false;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		while (cin.hasNext()) {
			String line = cin.nextLine();
			ArrayList<Integer> ws = new ArrayList<Integer>();
			StringTokenizer st = new StringTokenizer(line);
			int c = 0;
			while (st.hasMoreTokens()) {
				int w = getIntValue(st.nextToken());
				if (c == 0 || c > w) {
					c = w;
				}
				ws.add(w);
			}

			if (Main.debug) {
				System.out.println("w " + ws);
			}
			int nextC = 0;
			int n = ws.size();

			while (nextC != c) {
				if (nextC == 0) {
					nextC = c;
				}
				c = nextC;
				for (int i = 0; i < n - 1; i++) {
					for (int j = i + 1; j < n; j++) {
						if ((c / ws.get(i)) % n == (c / ws.get(j)) % n) {
							int temp = min((c / ws.get(i) + 1) * ws.get(i), (c / ws.get(j) + 1) * ws.get(j));
							if (nextC < temp)
								nextC = temp;
						}
					}
				}

				if (Main.debug) {
					System.out.println("nextC " + nextC);
				}

			}

			System.out.println(line);
			System.out.println(c+"\n");
		}
	}

	private static int min(int i, int j) {
		return (i < j ? i : j);
	}

	private static Integer getIntValue(String word) {
		int result = 0;
		for (int i = 0; i < word.length(); i++) {
			int n = word.charAt(i) - 'a' + 1;
			result += n * Math.pow(32, word.length() - 1 - i);
		}
		return result;
	}
}