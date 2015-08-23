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

public class Solution_SearchInsertPosition {

	private int find(int[] A, int left, int right, int target) {
		if (left == right) {
			if (target <= A[left]) {
				return left;
			}
			return left + 1;
		} else if (left == right - 1) {
			if (target <= A[left]) {
				return left;
			} else if (target <= A[right]) {
				return right;
			}
			return right + 1;
		}

		int mid = (left + right) / 2;
		if (target < A[mid]) {
			return find(A, left, mid - 1, target);
		} else if (target > A[mid]) {
			return find(A, mid + 1, right, target);
		}
		return mid;

	}

	public int searchInsert(int[] A, int target) {
		if (A.length == 0) {
			return 0;
		}

		return find(A, 0, A.length - 1, target);
	}

	public static void main(String[] args) {
		Solution_SearchInsertPosition solution_SearchInsertPosition = new Solution_SearchInsertPosition();
		System.out.println(solution_SearchInsertPosition.searchInsert(new int[] { 5, 7, 8, 10 }, 11));
	}
}
