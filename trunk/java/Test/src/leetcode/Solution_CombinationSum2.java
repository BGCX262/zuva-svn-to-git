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

import javax.swing.border.Border;
import javax.swing.text.ChangedCharSetException;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

public class Solution_CombinationSum2 {
	static class ListInt {
		List<Integer> values;

		public ListInt(List<Integer> l) {
			this.values = l;
		}

		@Override
		public boolean equals(Object l) {
			List<Integer> list = ((ListInt) l).values;
			if (values.size() != list.size()) {
				return false;
			}
			for (int i = 0; i < values.size(); i++) {
				if (!values.get(i).equals(list.get(i))) {
					return false;
				}
			}
			return true;
		}

		@Override
		public int hashCode() {
			int re = 0;
			for (Integer i : values) {
				re += i.hashCode();
			}
			return re;
		}

	}

	private void dfs(int[] arr, int index, int sum, int target, List<Integer> curr, Set<ListInt> result) {
		// System.out.println("dfs index "+index+" sum "+sum+" curr "+curr);
		if (sum == target) {
			result.add(new ListInt(curr));
			return;
		} else if (sum > target) {
			return;
		}

		for (int i = index; i < arr.length; i++) {
			List<Integer> list = new ArrayList<Integer>(curr);
			list.add(arr[i]);
			dfs(arr, i + 1, sum + arr[i], target, list, result);
		}
	}

	public List<List<Integer>> combinationSum2(int[] candidates, int target) {
		Set<ListInt> result = new HashSet<ListInt>();
		List<Integer> curr = new ArrayList<Integer>();
		Arrays.sort(candidates);
		dfs(candidates, 0, 0, target, curr, result);
		List<List<Integer>> list = new ArrayList<List<Integer>>();
		for (ListInt l : result) {
			list.add(l.values);
		}
		return list;
	}

	public static void main(String[] args) {
		Solution_CombinationSum2 solution_CombinationSum2 = new Solution_CombinationSum2();
		System.out.println(solution_CombinationSum2.combinationSum2(new int[] { 10, 1, 2, 7, 6, 1, 5 }, 8));
	}
}
