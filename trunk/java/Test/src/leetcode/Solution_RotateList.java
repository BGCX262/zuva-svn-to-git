package leetcode;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

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

public class Solution_RotateList {

	private int size(ListNode head) {
		int i = 0;
		while (head != null) {
			head = head.next;
			i++;
		}
		return i;
	}

	public ListNode rotateRight(ListNode head, int n) {
		int size = size(head);
		if (size < 2) {
			return head;
		}
		n = n % size;
		if (n == 0) {
			return head;
		}
		ListNode curr = head;
		for (int i = 0; i < size - n - 1; i++) {
			curr = curr.next;
		}
		ListNode end = curr;
		curr = curr.next;
		ListNode newHead = curr;
		while (curr.next != null) {
			curr = curr.next;
		}
		curr.next = head;
		end.next = null;
		return newHead;
	}

	public static void main(String[] args) {
		Solution_RotateList solution_RotateList = new Solution_RotateList();
		System.out.println(solution_RotateList.rotateRight(null, 0));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
