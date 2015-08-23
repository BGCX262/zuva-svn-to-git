import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		boolean debug = false;
		String s;
		StringBuffer sb = new StringBuffer();
		boolean concatenate = false;
		while (cin.hasNext()) {

			s = cin.nextLine();
			if (!concatenate && s.equals("#"))
				return;

			// System.out.println("nextLine:" + s);
			if (!concatenate) {
				sb = new StringBuffer();
			}
			sb.append(s);
			if (s.length() > 0 && s.charAt(s.length() - 1) == '-') {
				concatenate = true;
			} else {
				concatenate = false;
			}
			if (concatenate)
				continue;

			Message msg = new Message(sb.toString(), debug);
			msg.parseWord();
			for (Word w : msg.words) {
				System.out.println(w.str);
			}

			System.out.println("*");
		}
	}
}

class Message {
	boolean debug;
	String str;
	ArrayList<Word> words = new ArrayList<Word>();

	Message(String s, boolean d) {
		str = s;
		debug = d;
	}

	public void parseWord() {
		int i, len, j, start, end;
		char cArr[];
		boolean hasSame;
		StringBuffer sb = new StringBuffer();
		// filter out no alphabet char
		for (i = 0; i < str.length(); i++) {
			char c = str.charAt(i);
			if (c >= 'a' && c <= 'z') {
				sb.append(c);
			}
		}
		// words occurs more than 1 times and it doesn't include a pair of
		// spacer letters which is used to separate a word
		// spacer letters must match and not within the word
		// the message is bounded by a pair of joker letters that can match any
		// letter
		// word appears more than once with different letters' order is true
		// word
		// Every true word in the message
		// contains at least two and no more than 250 letters, overlaps with
		// another true word, and is repeated somewhere
		// in the message (possibly with the letters in a different order).
		len = sb.toString().length();
		if (len <= 2)
			return;
		cArr = sb.toString().toCharArray();
		if (debug) {
			System.out.println(sb.toString());
		}
		// start joker letter
		for (i = 1; i < len; i++) {
			char c = cArr[i];
			hasSame = false;
			for (j = 0; j < i; j++) {
				if (c == cArr[j]) {
					hasSame = true;
					break;
				}
			}
			if (hasSame) {
				continue;
			}
			start = 0;
			end = i - 1;
			Word w = new Word(sb.substring(start, end + 1), start, end);
			if (w.validate()) {
				words.add(w);
			}

		}
		// behind joker letter
		for (i = len - 2; i >= 0; i--) {
			char c = cArr[i];
			hasSame = false;
			for (j = len - 1; j > i; j--) {
				if (c == cArr[j]) {
					hasSame = true;
					break;
				}
			}
			if (hasSame) {
				continue;
			}
			start = i + 1;
			end = len - 1;
			Word w = new Word(sb.substring(start, end + 1), start, end);
			if (w.validate()) {
				words.add(w);
			}

		}

		if (len <= 3)
			return;
		// pick up words
		for (i = 0; i < len - 3; i++) {
			hasSame = false;
			for (j = i + 1; j < len; j++) {
				if (cArr[i] == cArr[j]) {
					hasSame = true;
					break;
				}
			}
			if (hasSame) {
				start = i + 1;
				end = j - 1;
				Word w = new Word(sb.substring(start, end + 1), start, end);
				if (w.validate()) {
					words.add(w);
				}
			}
		}

		HashMap<String, ArrayList<Word>> map = new HashMap<String, ArrayList<Word>>();
		for (Word w : words) {
			if (map.containsKey(w.getKey())) {
				map.get(w.getKey()).add(w);
			} else {
				ArrayList<Word> arr = new ArrayList<Word>();
				arr.add(w);
				map.put(w.getKey(), arr);
			}
		}

		for (String k : map.keySet()) {
			if (map.get(k).size() == 1) {
				map.get(k).get(0).istrue = false;
			}
		}

		ArrayList<Word> tempArr = new ArrayList<Word>();
		for (Word w : words) {
			if (w.istrue) {
				w.istrue = false;
				tempArr.add(w);
			} else {
				map.remove(w.getKey());
			}
		}

		words.clear();
		if (debug) {
			System.out.println("tempArr:");
			for (Word w : tempArr) {
				System.out.println(w.toString());
			}
		}
		
		for (Word w1 : tempArr) {
			if (w1.istrue)
				continue;

			for (Word w2 : tempArr) {
				if (w1.getKey().equals(w2.getKey())) {
					continue;
				}
				if (w1.overlaps(w2)) {
					for (Word w : map.get(w1.getKey())) {
						w.istrue = true;
					}
					for (Word w : map.get(w2.getKey())) {
						w.istrue = true;
					}
					if (debug) {
						System.out.println("overlap! w1:" + w1 + ", w2:" + w2);
					}
					break;
				}
			}
		}

		for (String k : map.keySet()) {
			Collections.sort(map.get(k), new Comparator<Word>() {
				@Override
				public int compare(Word w1, Word w2) {
					return w1.start - w2.start;
				}
			});
		}
		
		if (debug) {
			System.out.println("map ...");
			System.out.println(map);
		}

		for (Word w1 : tempArr) {
			if (!w1.istrue)
				continue;

			if (map.containsKey(w1.getKey()) && map.get(w1.getKey()).get(0).equals(w1)) {
				map.remove(w1.getKey());
				words.add(w1);
				continue;
			}
		}

		if (debug) {
			System.out.println("words:");
			for (Word w : words) {
				System.out.println(w.toString());
			}
		}

		Collections.sort(words, new Comparator<Word>() {
			@Override
			public int compare(Word w1, Word w2) {
				if (w1.end == w2.end)
					return w1.start - w2.start;
				if (w1.start == w2.start)
					return w1.end - w2.end;
				if (w1.overlaps(w2))
					return w1.end - w2.end;
				return w1.start - w2.start;
			}
		});
	}
}

class Word {
	private String key;
	String str;
	boolean istrue;
	int start;
	int end;

	Word(String s, int st, int e) {
		str = s;
		this.start = st;
		this.end = e;
		this.istrue = true;
	}

	boolean validate() {
		if (str.length() < 2 || str.length() > 250) {
			return false;
		}
		return true;
	}

	public String getKey() {
		if (key == null) {
			int i;
			StringBuffer sb = new StringBuffer();
			int[] chars = new int[26];
			for (i = 0; i < str.length(); i++) {
				chars[str.charAt(i) - 'a']++;
			}
			for (i = 0; i < 26; i++) {
				if (chars[i] > 0) {
					char c = (char) ('a' + i);
					sb.append(c);
					sb.append(chars[i]);
				}
			}
			key = sb.toString();
		}
		return key;
	}

	public boolean overlaps(Word w) {
		if (w.start >= this.start && w.start <= this.end)
			return true;
		if (w.end >= this.start && w.end <= this.end)
			return true;
		if (this.start >= w.start && this.start <= w.end)
			return true;
		if (this.end >= w.start && this.end <= w.end)
			return true;
		
		return false;
	}

	public boolean equals(Object o) {
		Word w = (Word) o;
		if (this.str.equals(w.str) && this.start == w.start && this.end == w.end)
			return true;
		return false;
	}

	public String toString() {
		return "[" + start + " to " + end + "," + str + "," + istrue + "]";
	}
}
