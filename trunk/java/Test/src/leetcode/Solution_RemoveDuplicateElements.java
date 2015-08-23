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

public class Solution_RemoveDuplicateElements {

	public int removeElement(int[] A, int elem) {
		if (A.length == 0) {
			return 0;
		}
		int index = -1;
		for (int i = 0; i < A.length; i++) {
			if (A[i] != elem) {
				A[++index] = A[i];
			}
		}
		return index + 1;
	}

	public static void main(String[] args) {
		Solution_RemoveDuplicateElements solution_RemoveDuplicateElement = new Solution_RemoveDuplicateElements();
		System.out.println(solution_RemoveDuplicateElement.removeElement(new int[] { 0, 3, 1, 1, 0, 1, 3, 0, 3, 3, 1, 1 }, 1));
		System.out.println(solution_RemoveDuplicateElement.removeElement(new int[] { 0, 4, 4, 0, 4, 4, 4, 0, 2 }, 4));
		System.out.println(solution_RemoveDuplicateElement.removeElement(new int[] { 2, 2, 3 }, 2));
		System.out.println(solution_RemoveDuplicateElement.removeElement(new int[] { 1 }, 2));
		System.out.println(solution_RemoveDuplicateElement.removeElement(new int[] { 1, 1 }, 1));
		System.out.println(solution_RemoveDuplicateElement.removeElement(new int[] { 1 }, 1));

	}
}
