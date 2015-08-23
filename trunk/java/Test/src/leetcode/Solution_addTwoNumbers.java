package leetcode;
class ListNode {
	int val;
	ListNode next;

	ListNode(int x) {
		val = x;
		next = null;
	}
}

public class Solution_addTwoNumbers {
	public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
		ListNode head = null, curr = null, prev = null;
		int borrow = 0;
		while (l1 != null && l2 != null) {
			int v = l1.val + l2.val + borrow;
			borrow = v / 10;
			v = v % 10;
			curr = new ListNode(v);
			if (head == null) {
				head = curr;
			}
			if (prev != null) {
				prev.next = curr;
			}
			prev = curr;
			l1 = l1.next;
			l2 = l2.next;
		}
		while (l1 != null) {
			int v = l1.val + borrow;
			borrow = v / 10;
			v = v % 10;
			curr = new ListNode(v);
			if (head == null) {
				head = curr;
			}
			if (prev != null) {
				prev.next = curr;
			}
			prev = curr;
			l1 = l1.next;
		}
		while (l2 != null) {
			int v = l2.val + borrow;
			borrow = v / 10;
			v = v % 10;
			curr = new ListNode(v);
			if (head == null) {
				head = curr;
			}
			if (prev != null) {
				prev.next = curr;
			}
			prev = curr;
			l2 = l2.next;
		}
		if (borrow > 0) {
			int v = borrow;
			curr = new ListNode(v);
			if (head == null) {
				head = curr;
			}
			if (prev != null) {
				prev.next = curr;
			}
		}
		return head;
	}
}