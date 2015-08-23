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
 * uva 10905
 */

public class Main {
	static boolean debug = false;

	public static Comparator<String> comptr = new Comparator<String>() {
		public int compare(String s1, String s2) {
			String n1n2 = s1 + s2;
			String n2n1 = s2 + s1;
			int size = n1n2.length();
			for (int i = 0; i < size; i++) {
				char c1c2 = n1n2.charAt(i);
				char c2c1 = n2n1.charAt(i);
				if (c1c2 < c2c1) {
					return 1;
				} else if (c1c2 > c2c1) {
					return -1;
				}
			}
			return s1.length() - s2.length();
		}
	};

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int num;
		while ((num = cin.nextInt()) != 0) {
			ArrayList<String> all = new ArrayList<String>();
			for (int i = 0; i < num; i++) {
				all.add(cin.next());
			}
			if (Main.debug) {
				System.out.println("before " + all);
			}
			Collections.sort(all, comptr);
			if (Main.debug) {
				System.out.println("after " + all);
			}
			for (String s : all) {
				System.out.print(s);
			}
			System.out.print("\n");
		}
	}
}