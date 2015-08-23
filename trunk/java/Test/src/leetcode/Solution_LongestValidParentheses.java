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

public class Solution_LongestValidParentheses {

	public int longestValidParentheses(String s) {
		if (s.length() < 2) {
			return 0;
		}

		int result = 0;
		int[] longest = new int[s.length()];
		Arrays.fill(longest, 0);
		for (int i = 1; i < s.length(); i++) {
			if (s.charAt(i) == ')') {
				if (s.charAt(i - 1) == '(') {
					longest[i] = (i - 2 >= 0 ? longest[i - 2] : 0) + 2;
					if (longest[i] > result) {
						result = longest[i];
					}
				} else {
					if (i - 1 - longest[i - 1] >= 0 && s.charAt(i - 1 - longest[i - 1]) == '(') {
						longest[i] = longest[i - 1] + 2 + (i - 2 - longest[i - 1] >= 0 ? longest[i - 2 - longest[i - 1]] : 0);
						if (longest[i] > result) {
							result = longest[i];
						}
					}
				}
			}
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_LongestValidParentheses solution_LongestValidParentheses = new Solution_LongestValidParentheses();
		System.out.println(solution_LongestValidParentheses.longestValidParentheses("())"));
	}
}
