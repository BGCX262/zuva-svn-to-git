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

public class Solution_SearchRange {

	private int[] duplicate(int[] A, int index) {
		int left = index;
		int right = index;
		while (left >= 0 && A[left] == A[index]) {
			left--;
		}
		while (right < A.length && A[right] == A[index]) {
			right++;
		}
		return new int[] { left + 1, right - 1 };
	}

	private int[] find(int[] A, int[] left, int[] right, int target) {
		if (left[0] == right[0]) {
			if (target == A[left[0]]) {
				return left;
			} else {
				return new int[] { -1, -1 };
			}
		} else if (left[0] > right[0]) {
			return new int[] { -1, -1 };
		}

		int[] mid = duplicate(A, (left[0] + right[0]) / 2);

		if (target > A[mid[0]]) {
			return find(A, duplicate(A, mid[1] + 1), right, target);
		} else if (target < A[mid[0]]) {
			return find(A, left, duplicate(A, mid[0] - 1), target);
		} else {
			return mid;
		}
	}

	public int[] searchRange(int[] A, int target) {
		return find(A, duplicate(A, 0), duplicate(A, A.length - 1), target);
	}

	public static void main(String[] args) {
		Solution_SearchRange solution_SearchRange = new Solution_SearchRange();
		int[] result = solution_SearchRange.searchRange(new int[] { 0, 0, 1, 1, 1, 4, 5, 5 }, 2);
		System.out.println(solution_SearchRange.searchRange(new int[] { 5, 7, 7, 8, 8, 10 }, 8));
	}
}
