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
 * uva 10763
 */

public class Main {
	static boolean debug = false;
	static HashMap<Integer, HashMap<Integer, Integer>> all = new HashMap<Integer, HashMap<Integer, Integer>>();

	static boolean hasExchange(int f, int t) {
		HashMap<Integer, Integer> map = all.get(f);
		if (map != null) {
			Integer v = map.get(t);
			if (v != null) {
				return v > 0;
			}
		}
		return false;
	}

	static Integer getExchange(Integer f, Integer t) {
		HashMap<Integer, Integer> map = all.get(f);
		if (map != null) {
			Integer v = map.get(t);
			if (v != null) {
				return v;
			}
		}
		return new Integer(0);
	}

	static void upExchange(Integer f, Integer t) {
		HashMap<Integer, Integer> map = all.get(f);
		if (map == null) {
			map = new HashMap<Integer, Integer>();
			map.put(t, new Integer(1));
			all.put(f, map);
			return;
		}
		Integer v = map.get(t);
		if (v == null) {
			map.put(t, new Integer(1));
			return;
		}
		v++;
	}

	static void downExchange(Integer f, Integer t) {
		HashMap<Integer, Integer> map = all.get(f);
		if (map != null) {
			Integer v = map.get(t);
			if (v != null) {
				v--;
			}
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int num;

		while ((num = cin.nextInt()) != 0) {
			all.clear();
			int noMatch = 0;
			for (int i = 0; i < num; i++) {
				Integer from = cin.nextInt();
				Integer to = cin.nextInt();
				Integer exch = getExchange(to, from);
				if (exch == 0) {
					upExchange(from, to);
					noMatch++;
				} else {
					downExchange(to, from);
					noMatch--;
				}
			}
			if (noMatch == 0)
				System.out.println("YES");
			else
				System.out.println("NO");
		}
	}
}