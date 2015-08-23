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
 * uva 10101
 */

public class Main {
	static boolean debug = false;
	static int[] place;
	static int[][] cutHistory;
	static int len, num, cost;

	static int cut(int left, int right) {
		if (right - 1 == left)
			return 0;

		if (cutHistory[left][right] != 0)
			return cutHistory[left][right];

		if (right - 2 == left) {
			cutHistory[left][right] = place[right] - place[left];
			return (place[right] - place[left]);
		}

		int minCost = 0;
		for (int i = left + 1; i <= right - 1; i++) {
			int t = cut(left, i) + cut(i, right);
			if (minCost == 0 || t < minCost) {
				minCost = t;
			}
		}
		if (Main.debug) {
			System.out.println("cut " + left + " " + right + " return " + (minCost + place[right] - place[left]));
		}
		cutHistory[left][right] = minCost + place[right] - place[left];
		return minCost + place[right] - place[left];
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;

		while (cin.hasNext()) {
			len = cin.nextInt();
			if (len == 0)
				break;
			num = cin.nextInt();
			place = new int[num + 2];
			cutHistory = new int[num + 2][num + 2];
			cost = 0;
			place[0] = 0;
			place[num + 1] = len;
			for (int i = 1; i < num + 1; i++) {
				place[i] = cin.nextInt();
			}

			if (Main.debug) {
				for (int s : place)
					System.out.print(s + " ");

				System.out.print("\n");
			}
			System.out.println("The minimum cutting is " + cut(0, num + 1) + ".");
		}
	}
}
