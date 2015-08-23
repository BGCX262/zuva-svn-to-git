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
 * uva 674
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
		int num;
		int[] changes = new int[7490];
		int[] coins = { 1, 5, 10, 25, 50 };
		changes[0] = 1;
		for (int i = 0; i < 5; i++) {
			for (int j = coins[i]; j < 7490; j++) {
				changes[j] += changes[j - coins[i]];
			}
		}

		while (cin.hasNext()) {
			num = cin.nextInt();
			System.out.println(changes[num]);
		}
	}
}
