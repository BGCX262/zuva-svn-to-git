package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.EmptyStackException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

public class Solution_Substring_ConcatenationAllWords {

	public List<Integer> findSubstring(String S, String[] L) {
		Map<String, Integer> dict = new HashMap<String, Integer>();
		for (String l : L) {
			dict.put(l, (dict.containsKey(l) ? dict.get(l) : 0) + 1);
		}
		List<Integer> result = new ArrayList<Integer>();
		int len = L[0].length();
		if (L != null && L.length > 0 && S != null && S.length() > 0 && L[0] != null && L[0].length() > 0) {
			for (int i = 0; i < len; i++) {
				Map<String, Integer> map = new HashMap<String, Integer>(dict);
				Queue<String> queue = new LinkedList<String>();
				for (int j = i; j + len <= S.length(); j += len) {
					String str = S.substring(j, j + len);
					if (dict.containsKey(str)) {
						queue.add(str);
						if (map.get(str) == 0) {
							String s = null;
							while (!(s = queue.poll()).equals(str)) {
								map.put(s, map.get(s) + 1);
							}
						} else {
							map.put(str, map.get(str) - 1);
						}
						if (queue.size() == L.length) {
							result.add(j - (L.length - 1) * len);
						}
					} else {
						map = new HashMap<String, Integer>(dict);
						queue = new LinkedList<String>();
					}
				}
			}
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_Substring_ConcatenationAllWords solution_Substring_ConcatenationAllWords = new Solution_Substring_ConcatenationAllWords();
		//System.out.println(solution.findSubstring("barfoothefoobarman", new String[] { "foo", "bar" }));
		System.out.println(solution_Substring_ConcatenationAllWords.findSubstring("a", new String[] { "a" }));
	}
}
