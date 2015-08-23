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

public class Solution_SearchRotatedSortedArray {

	private int find(int[] A, int left, int right, int target) {
		if (A[left] == target)
			return left;

		if (A[right] == target)
			return right;

		if (A[left] < A[right]) {
			return Arrays.binarySearch(A, left, right + 1, target);
		} else if (left == right) {
			return A[left] == target ? left : -1;
		}
		int mid = (left + right) / 2;
		if (A[left] < A[mid]) {
			if (target <= A[mid] && target >= A[left]) {
				return find(A, left, mid, target);
			}
			return find(A, mid, right, target);
		} else {
			if (target >= A[mid] && target <= A[right]) {
				return find(A, mid, right, target);
			}
			return find(A, left, mid, target);
		}
	}

	public int search(int[] A, int target) {
		int result = -1;
		if (A.length == 0) {
			return -1;
		} else if (A.length == 1) {
			return A[0] == target ? 0 : -1;
		} else if (A.length == 2) {
			if (A[0] == target) {
				return 0;
			}
			if (A[1] == target) {
				return 1;
			}
			return -1;
		}
		result = find(A, 0, A.length - 1, target);
		if (result >= 0) {
			return result;
		} else {
			return -1;
		}
	}

	public static void main(String[] args) {
		Solution_SearchRotatedSortedArray solution_SearchRotatedSortedArray = new Solution_SearchRotatedSortedArray();
		System.out.println(solution_SearchRotatedSortedArray.search(new int[] { 3, 4, 5, 6, 7, 0, 1, 2 }, -1));
	}
}
