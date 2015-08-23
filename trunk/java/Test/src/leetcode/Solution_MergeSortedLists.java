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

public class Solution_MergeSortedLists {
	public ListNode mergeKLists(List<ListNode> lists) {
		List<ListNode> result = new ArrayList<ListNode>();
		for (ListNode n : lists) {
			while (n != null) {
				result.add(n);
				n = n.next;
			}
		}

		Collections.sort(result, new Comparator<ListNode>() {

			@Override
			public int compare(ListNode o1, ListNode o2) {
				if (o1.val < o2.val) {
					return -1;
				} else if (o1.val == o2.val) {
					return 0;
				} else {
					return 1;
				}
			}
		});

		for (int i = 0; i < result.size() - 1; i++) {
			if (i + 1 < result.size()) {
				result.get(i).next = result.get(i + 1);
			}
		}
		if(result.size() > 0) {
			result.get(result.size() - 1).next = null;
			return result.get(0);	
		} else {
			return null;
		}
		
	}

	public static void main(String[] args) {
		Solution_MergeSortedLists solution_MergeSortedLists = new Solution_MergeSortedLists();
		System.out.println(solution_MergeSortedLists.mergeKLists(null));
	}
}
