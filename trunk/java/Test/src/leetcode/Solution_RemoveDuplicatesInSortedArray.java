package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.EmptyStackException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
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

public class Solution_RemoveDuplicatesInSortedArray {

	public int removeDuplicates(int[] A) {
		if (A.length < 2) {
			return A.length;
		}

		int index = 1;
		for (int i = 1; i < A.length; i++) {
			if (A[i] != A[i - 1]) {
				A[index++] = A[i];
			}
		}
		return index;
	}

	public static void main(String[] args) {
		Solution_RemoveDuplicatesInSortedArray solution_RemoveDuplicatesInSortedArray = new Solution_RemoveDuplicatesInSortedArray();
		System.out.println(solution_RemoveDuplicatesInSortedArray.removeDuplicates(new int[] {}));
		System.out.println(solution_RemoveDuplicatesInSortedArray.removeDuplicates(new int[] { 1 }));
		System.out.println(solution_RemoveDuplicatesInSortedArray.removeDuplicates(new int[] { 1, 1 }));
		System.out.println(solution_RemoveDuplicatesInSortedArray.removeDuplicates(new int[] { 0, 3, 1, 1 }));

	}
}
