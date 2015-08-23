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

public class Solution_CombinationSum {

	private void dfs(int[] arr, int index, int sum, int target, List<Integer> curr, List<List<Integer>> result) {
		//System.out.println("dfs index "+index+" sum "+sum+" curr "+curr);
		if (sum == target) {
			result.add(curr);
			return;
		} else if (sum > target) {
			return;
		}

		for (int i = index; i < arr.length; i++) {
			List<Integer> list = new ArrayList<Integer>(curr);
			list.add(arr[i]);
			dfs(arr, i, sum + arr[i], target, list, result);
		}
	}

	public List<List<Integer>> combinationSum(int[] candidates, int target) {
		List<List<Integer>> result = new ArrayList<List<Integer>>();
		List<Integer> curr = new ArrayList<Integer>();
		Arrays.sort(candidates);
		dfs(candidates, 0, 0, target, curr, result);
		return result;
	}

	public static void main(String[] args) {
		Solution_CombinationSum solution_CombinationSum = new Solution_CombinationSum();
		System.out.println(solution_CombinationSum.combinationSum(new int[] { 2, 3, 6, 7 }, 7));
	}
}
