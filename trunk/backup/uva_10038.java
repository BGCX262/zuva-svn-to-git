import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.StringTokenizer;

/**
 * 10038
 */

public class Main {
	static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		while (cin.hasNextLine()) {
			boolean isJolly = true;
			StringTokenizer st = new StringTokenizer(cin.nextLine());
			HashSet<Integer> set = new HashSet<Integer>();
			int n = Integer.parseInt(st.nextToken());
			ArrayList<Integer> seq = new ArrayList<Integer>();
			while (st.hasMoreTokens()) {
				seq.add(Integer.parseInt(st.nextToken()));
			}
			int size = seq.size();
			for (int i = 0; i < size - 1; i++) {
				int diff = Math.abs(seq.get(i) - seq.get(i + 1));
				if (diff > n - 1 || diff == 0 || set.contains(diff)) {
					isJolly = false;
					break;
				}
				set.add(diff);
			}
			if (isJolly)
				System.out.println("Jolly");
			else
				System.out.println("Not jolly");

		}
	}
}