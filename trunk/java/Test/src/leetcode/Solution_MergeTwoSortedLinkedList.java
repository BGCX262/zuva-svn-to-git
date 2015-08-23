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

// class Interval {
// int start;
// int end;
//
// Interval() {
// start = 0;
// end = 0;
// }
//
// Interval(int s, int e) {
// start = s;
// end = e;
// }
// }

public class Solution_MergeTwoSortedLinkedList {

	public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
		if (l1 == null) {
			return l2;
		}
		if (l2 == null) {
			return l1;
		}
		ListNode node = new ListNode(0);
		ListNode root = node;
		while (l1 != null && l2 != null) {
			if (l1.val < l2.val) {
				node.next = l1;
				node = l1;
				l1 = l1.next;
			} else if (l1.val > l2.val) {
				node.next = l2;
				node = l2;
				l2 = l2.next;
			} else {
				ListNode t1 = l1.next;
				ListNode t2 = l2.next;
				node.next = l1;
				node = node.next;
				node.next = l2;
				node = node.next;

				l1 = t1;
				l2 = t2;
			}
		}
		if (l1 != null) {
			node.next = l1;
		} else if (l2 != null) {
			node.next = l2;
		}
		return root.next;
	}

	public static void main(String[] args) {
		Solution_MergeTwoSortedLinkedList solution_MergeTwoSortedLinkedList = new Solution_MergeTwoSortedLinkedList();
		System.out.println(solution_MergeTwoSortedLinkedList.mergeTwoLists(null, null));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
