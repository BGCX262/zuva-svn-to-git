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

public class Solution_PermutationsII {

	private List<Integer> nextPermute(List<Integer> list) {

		for (int i = list.size() - 1; i > 0; i--) {
			if (list.get(i) > list.get(i - 1)) {
				List<Integer> result = new ArrayList<Integer>(list.subList(0, i));
				List<Integer> result2 = new ArrayList<Integer>(list.subList(i, list.size()));
				Collections.sort(result2);
				result.addAll(result2);
				for (int j = i; j < result.size(); j++) {
					if (result.get(j) > result.get(i - 1)) {
						Collections.swap(result, i - 1, j);
						return result;
					}
				}
			}
		}
		return null;
	}

	public List<List<Integer>> permuteUnique(int[] num) {
		List<List<Integer>> result = new ArrayList<List<Integer>>();
		List<Integer> list = new ArrayList<Integer>();
		for (int n : num) {
			list.add(n);
		}
		Collections.sort(list);
		result.add(new ArrayList<Integer>(list));
		while ((list = nextPermute(list)) != null) {
			result.add(new ArrayList<Integer>(list));
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_PermutationsII solution_PermutationsII = new Solution_PermutationsII();
		// System.out.println(solution.permuteUnique(new int[] { 1, 1, 2 }));
		// System.out.println(solution.permuteUnique(new int[] { -1, -1, 3, -1
		// }));
		System.out.println(solution_PermutationsII.permuteUnique(new int[] { 1, 2, 3 }));

	}
}
