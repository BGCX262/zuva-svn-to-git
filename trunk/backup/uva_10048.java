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
 * 10048
 */

class Node {
	double x, y;
	int i;
}

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		for (int test = 1;; test++) {
			StringTokenizer st = new StringTokenizer(cin.nextLine());
			int c = Integer.parseInt(st.nextToken());
			int s = Integer.parseInt(st.nextToken());
			int q = Integer.parseInt(st.nextToken());
			if (c == 0 && s == 0 && q == 0) {
				break;
			}

			int[][] path = new int[c + 1][c + 1];

			for (int i = 1; i <= c; i++) {
				for (int j = 1; j <= c; j++) {
					if (i != j) {
						path[i][j] = 10000000;
					}
				}
			}
			for (int i = 0; i < s; i++) {
				st = new StringTokenizer(cin.nextLine());
				int c1 = Integer.parseInt(st.nextToken());
				int c2 = Integer.parseInt(st.nextToken());
				int decibal = Integer.parseInt(st.nextToken());
				path[c2][c1] = path[c1][c2] = decibal;
			}
			for (int k = 1; k <= c; k++) {
				for (int i = 1; i <= c; i++) {
					for (int j = 1; j <= c; j++) {
						int temp = path[i][k] < path[k][j] ? path[k][j] : path[i][k];
						if (temp < path[i][j]) {
							path[i][j] = temp;
						}
					}
				}
			}
			if (test != 1)
				System.out.println("");

			System.out.println("Case #" + test);
			for (int i = 0; i < q; i++) {
				st = new StringTokenizer(cin.nextLine());
				int c1 = Integer.parseInt(st.nextToken());
				int c2 = Integer.parseInt(st.nextToken());
				int decibal = path[c1][c2];
				if (decibal == 10000000) {
					System.out.println("no path");
				} else {
					System.out.println(decibal);
				}
			}

		}
	}
}
