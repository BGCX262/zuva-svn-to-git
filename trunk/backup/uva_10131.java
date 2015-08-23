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
 * uva 10131
 */

class Elephant implements Comparable<Elephant> {
	int weight, iq, index, max;
	Elephant previous;

	Elephant(int w, int iq, int i) {
		this.weight = w;
		this.iq = iq;
		this.index = i;
	}

	@Override
	public int compareTo(Elephant o) {
		if (this.weight != o.weight)
			return this.weight - o.weight;
		else
			return o.iq - this.iq;
	}
}

public class Main {
	static boolean debug = false;

	private static void print(Elephant ele) {
		if (ele.previous != null)
			print(ele.previous);

		System.out.println(ele.index);
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int index = 1;
		ArrayList<Elephant> all = new ArrayList<Elephant>();
		while (cin.hasNext()) {
			all.add(new Elephant(cin.nextInt(), cin.nextInt(), index++));
		}

		Collections.sort(all);
		Elephant end = null;
		all.get(0).max = 1;
		for (int i = 1; i < all.size(); i++) {
			Elephant max = null;
			for (int j = 0; j < i; j++) {
				if (all.get(i).iq < all.get(j).iq && all.get(i).weight > all.get(j).weight) {
					if (max == null || all.get(j).max > max.max) {
						max = all.get(j);
					}
				}
			}
			if (max != null) {
				all.get(i).previous = max;
				all.get(i).max = max.max + 1;
			} else {
				all.get(i).max = 1;
			}

			if (end == null || all.get(i).max > end.max) {
				end = all.get(i);
			}
		}

		System.out.println(end.max);
		print(end);

	}

}
