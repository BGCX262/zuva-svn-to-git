import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		int gameNum = 0;
		while (cin.hasNext()) {
			gameNum++;
			List<Integer> secret = new ArrayList<Integer>();
			Map<Integer, Integer> secretHit = new HashMap<Integer, Integer>();
			List<ArrayList<Integer>> guesses = new ArrayList<ArrayList<Integer>>();
			String line = cin.nextLine().trim();
			int n = Integer.parseInt(line);
			if (n == 0)
				break;
			line = cin.nextLine().trim();
			StringTokenizer st = new StringTokenizer(line);
			while (st.hasMoreTokens()) {
				Integer it = Integer.parseInt(st.nextToken());
				secret.add(it);
				if (secretHit.containsKey(it)) {
					Integer v = secretHit.get(it);
					v++;
					secretHit.put(it, v);
				} else {
					secretHit.put(it, new Integer(1));
				}
			}

			while (cin.hasNext()) {
				ArrayList<Integer> guess = new ArrayList<Integer>();
				line = cin.nextLine().trim();
				st = new StringTokenizer(line);
				while (st.hasMoreTokens()) {
					guess.add(Integer.parseInt(st.nextToken()));
				}
				boolean isZero = true;
				for (Integer g : guess) {
					if (g != 0) {
						isZero = false;
						break;
					}
				}
				if (isZero) {
					break;
				}
				guesses.add(guess);
			}
			System.out.println("Game " + gameNum + ":");
			for (ArrayList<Integer> guess : guesses) {
				Map<Integer, Integer> secretHitClone = new HashMap<Integer, Integer>();
				secretHitClone.putAll(secretHit);
				int strong = 0, weak = 0;
				for (int i = 0; i < guess.size(); i++) {
					Integer g = guess.get(i);
					if (secret.get(i) == g) {
						strong++;
						Integer v = secretHitClone.get(g);
						if (v > 0) {
							v--;
							secretHitClone.put(g, v);
						}
					}
				}
				for (int i = 0; i < guess.size(); i++) {
					Integer g = guess.get(i);
					if (secret.get(i) != g && secretHitClone.containsKey(g)) {
						Integer v = secretHitClone.get(g);
						if (v > 0) {
							weak++;
							v--;
							secretHitClone.put(g, v);
						}
					}
				}
				System.out.println("    (" + strong + "," + weak + ")");
			}
		}
	}
}