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

public class Solution_SwapNodesInPairs {
	public ListNode swapPairs(ListNode head) {
		ListNode result = null, node1 = null, node2 = null, prev = null, next = null;
		if (head == null) {
			return null;
		}
		result = node1 = head;
		if (head.next != null) {
			result = head.next;
		}
		while (true) {
			if (node1 == null || node1.next == null) {
				break;
			}
			node2 = node1.next;
			next = node2.next;

			node2.next = node1;
			node1.next = next;
			if (prev != null) {
				prev.next = node2;
			}
			prev = node1;
			node1 = next;
		}

		return result;
	}

	public static void main(String[] args) {
		Solution_SwapNodesInPairs solution_SwapNodesInPairs = new Solution_SwapNodesInPairs();
		System.out.println(solution_SwapNodesInPairs.swapPairs(null));
	}
}
