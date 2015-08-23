package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

public class Solution_RemoveNthNodeFromEndList {
	public ListNode removeNthFromEnd(ListNode head, int n) {
		List<ListNode> list = new ArrayList<ListNode>();
		while (head != null) {
			list.add(head);
			head = head.next;
		}
		int size = list.size();
		if (size <= 1)
			return null;
		int index = size - n;
		if (index == 0) {
			list.get(0).next = null;
			return list.get(1);
		}
		if (index == list.size() - 1) {
			list.get(index - 1).next = null;
		} else {
			list.get(index - 1).next = list.get(index + 1);
		}
		return list.get(0);

	}

	public static void main(String[] args) {
		Solution_RemoveNthNodeFromEndList solution_RemoveNthNodeFromEndList = new Solution_RemoveNthNodeFromEndList();
		System.out.println(solution_RemoveNthNodeFromEndList.removeNthFromEnd(null, 0));
	}
}
