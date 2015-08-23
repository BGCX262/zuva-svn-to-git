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

public class Solution_ReverseNodeInKGroup {
	/**
	 * return [head,tail]
	 */
	private ListNode[] reverse(ListNode prevHead, ListNode head, int k) {
		if (k == 0) {
			return null;
		}
		List<ListNode> result = new ArrayList<ListNode>();
		ListNode curr = head;

		while (curr != null) {
			result.add(curr);
			curr = curr.next;
			if (result.size() == k)
				break;
		}
		if (result.size() < k) {
			return null;
		}
		ListNode afterTail = result.get(k - 1).next;
		for (int i = k - 1; i > 0; i--) {
			result.get(i).next = result.get(i - 1);
		}
		if (prevHead != null)
			prevHead.next = result.get(k - 1);
		result.get(0).next = afterTail;
		return new ListNode[] { result.get(k - 1), result.get(0) };
	}

	public ListNode reverseKGroup(ListNode head, int k) {
		ListNode prevHead = null;
		ListNode result = null;
		while (head != null) {
			ListNode[] headTail = reverse(prevHead, head, k);
			if (headTail == null) {
				break;
			}
			if (prevHead == null) {
				result = headTail[0];
			}
			prevHead = headTail[1];
			head = headTail[1].next;
		}
		if (result == null) {
			result = head;
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_ReverseNodeInKGroup solution_ReverseNodeInKGroup = new Solution_ReverseNodeInKGroup();
		System.out.println(solution_ReverseNodeInKGroup.reverseKGroup(null, 0));
	}
}
