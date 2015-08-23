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

public class Solution_Anagrams {

	private String sort(String str) {
		int[] count = new int[26];
		for (int i = 0; i < str.length(); i++) {
			count[str.charAt(i) - 'a']++;
		}
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < count.length; i++) {
			while (count[i] > 0) {
				sb.append('a' + i);
				count[i]--;
			}
		}
		return sb.toString();
	}

	public List<String> anagrams(String[] strs) {
		Map<String, List<Integer>> map = new HashMap<String, List<Integer>>();
		for (int i = 0; i < strs.length; i++) {
			String key = sort(strs[i]);
			if (map.containsKey(key)) {
				map.get(key).add(i);
			} else {
				List<Integer> list = new ArrayList<Integer>();
				list.add(i);
				map.put(key, list);
			}
		}
		List<String> result = new ArrayList<String>();
		for (Map.Entry<String, List<Integer>> entry : map.entrySet()) {
			if (entry.getValue().size() > 1) {
				for (Integer n : entry.getValue()) {
					result.add(strs[n]);
				}
			}
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_Anagrams solution_Anagrams = new Solution_Anagrams();
		System.out.println(solution_Anagrams.anagrams(new String[] { "", "" }));

	}
}
