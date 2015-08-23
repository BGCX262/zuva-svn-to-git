import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
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
 * 10066
 */

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int index = 1;
		for (;;) {
			ArrayList<Integer> tower1 = new ArrayList<Integer>();
			ArrayList<Integer> tower2 = new ArrayList<Integer>();
			int m = cin.nextInt();
			int n = cin.nextInt();
			if (m == 0 && n == 0)
				break;

			for (int i = 0; i < m; i++) {
				tower1.add(cin.nextInt());
			}
			for (int i = 0; i < n; i++) {
				tower2.add(cin.nextInt());
			}
			System.out.println("Twin Towers #" + (index++));
			System.out.println("Number of Tiles : " + getLCS(tower1, tower2));
			System.out.println("");

		}
	}

	private static int getLCS(ArrayList<Integer> tower1, ArrayList<Integer> tower2) {
		int m = tower1.size();
		int n = tower2.size();
		int[][] lcs = new int[m + 1][n + 1];
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (tower1.get(i - 1) == tower2.get(j - 1)) {
					lcs[i][j] = lcs[i - 1][j - 1] + 1;
				} else {
					lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
				}
			}
		}

		return lcs[m][n];
	}

	private static int max(int i, int j) {
		return i > j ? i : j;
	}
}
