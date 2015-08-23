import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.TreeMap;

public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		StringBuilder sb = new StringBuilder();
		ArrayList<Profile> profiles = new ArrayList<Profile>();
		ArrayList<Title> titles = new ArrayList<Title>();
		boolean title = false;
		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			if (line.equals("#"))
				break;

			if (!title && line.charAt(0) == 'P' && line.charAt(1) == ':') {
				StringTokenizer st = new StringTokenizer(line);
				st.nextToken();
				int t = Integer.parseInt(st.nextToken());
				ArrayList<String> keys = new ArrayList<String>();
				while (st.hasMoreTokens()) {
					keys.add(st.nextToken());
				}
				profiles.add(new Profile(t, keys));
			} else if (!title && line.charAt(0) == 'T' && line.charAt(1) == ':') {
				title = true;
			}

			if (title) {
				if (line.charAt(0) == 'T' && line.charAt(1) == ':') {
					line = line.replaceFirst("T:", "");
					sb.append(" ");
					sb.append(line);
					if (line.charAt(line.length() - 1) == '|') {
						titles.add(new Title(getTitleWords(sb.toString())));
						sb.setLength(0);
					}
				} else {
					sb.append(" ");
					sb.append(line);
					if (line.charAt(line.length() - 1) == '|') {
						titles.add(new Title(getTitleWords(sb.toString())));
						sb.setLength(0);
					}
				}
			}
		}
		if (debug) {
			System.out.println(profiles);
			System.out.println(titles);
		}
		for (int i = 0; i < profiles.size(); i++) {
			Profile p = profiles.get(i);
			p.processHit(titles);

			System.out.print(i + 1 + ": ");
			if (p.hits.size() > 0) {
				for (int j = 0; j < p.hits.size() - 1; j++) {
					System.out.print(p.hits.get(j) + ",");
				}
				System.out.print(p.hits.get(p.hits.size() - 1));
			}
			System.out.print("\n");
		}

	}

	static List<String> getTitleWords(String l) {
		ArrayList<String> words = new ArrayList<String>();
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < l.length(); i++) {
			if (Character.isUpperCase(l.charAt(i))) {
				sb.append(Character.toLowerCase(l.charAt(i)));
			} else if (Character.isLowerCase(l.charAt(i)) || l.charAt(i) == ' ') {
				sb.append(l.charAt(i));
			}
		}
		StringTokenizer st = new StringTokenizer(sb.toString());
		while (st.hasMoreTokens()) {
			words.add(st.nextToken());
		}
		return words;
	}
}

class Profile {
	int threshold;
	List<String> keys;
	List<Integer> hits;

	Profile(int t, List<String> k) {
		this.threshold = t;
		this.keys = k;
		hits = new ArrayList<Integer>();
	}

	void processHit(List<Title> titles) {
		for (int i = 0; i < titles.size(); i++) {
			if (isHit(titles.get(i))) {
				hits.add(i + 1);
			}
		}
	}

	boolean isHit(Title title) {
		for (int i = 0; i < keys.size() - 1; i++) {
			for (int j = i + 1; j < keys.size(); j++) {
				if (title.isHit(keys.get(i), keys.get(j), this.threshold)) {
					return true;
				}
			}
		}
		return false;
	}

	public String toString() {
		return "threshhold:" + threshold + ", keys:" + keys;
	}
}

class Title {
	List<String> words;
	HashMap<String, ArrayList<Integer>> wordIndex = new HashMap<String, ArrayList<Integer>>();

	Title(List<String> ws) {
		this.words = ws;
		for (int i = 0; i < this.words.size(); i++) {
			if (wordIndex.containsKey(words.get(i))) {
				wordIndex.get(words.get(i)).add(new Integer(i));
			} else {
				ArrayList<Integer> a = new ArrayList<Integer>();
				a.add(new Integer(i));
				wordIndex.put(words.get(i), a);
			}
		}
	}

	boolean isHit(String k1, String k2, int threshold) {
		if (!wordIndex.containsKey(k1) || !wordIndex.containsKey(k2)) {
			return false;
		}
		if (k1.equals(k2)) {
			List<Integer> indexs = wordIndex.get(k1);
			for (int i = 0; i < indexs.size() - 1; i++) {
				for (int j = i + 1; j < indexs.size(); j++) {
					if (Math.abs(indexs.get(j) - indexs.get(i)) - 1 <= threshold) {
						return true;
					}
				}
			}
		} else {
			List<Integer> indexs1 = wordIndex.get(k1);
			List<Integer> indexs2 = wordIndex.get(k2);
			for (int i = 0; i < indexs1.size(); i++) {
				for (int j = 0; j < indexs2.size(); j++) {
					if (Math.abs(indexs1.get(i) - indexs2.get(j)) - 1 <= threshold) {
						return true;
					}
				}
			}
		}
		return false;
	}

	public String toString() {
		return "words:" + words + "\n" + "index:" + wordIndex;
	}

}