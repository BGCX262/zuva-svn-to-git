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

class Interval {
	int start;
	int end;

	Interval() {
		start = 0;
		end = 0;
	}

	Interval(int s, int e) {
		start = s;
		end = e;
	}
}

public class Solution_IntervalMerge {

	public List<Interval> merge(List<Interval> intervals) {
		Collections.sort(intervals, new Comparator<Interval>() {

			@Override
			public int compare(Interval o1, Interval o2) {
				if (o1.start < o2.start) {
					return -1;
				} else if (o1.start > o2.start) {
					return 1;
				} else {
					if (o1.end < o2.end) {
						return -1;
					} else if (o1.end > o2.end) {
						return 1;
					} else {
						return 0;
					}
				}
			}
		});

		List<Interval> result = new ArrayList<Interval>();
		if (intervals.size() == 0) {
			return result;
		}
		Interval curr = new Interval(intervals.get(0).start, intervals.get(0).end);
		for (Interval i : intervals) {
			if (i.start > curr.end) {
				result.add(curr);
				curr = new Interval(i.start, i.end);
			} else {
				if (i.end > curr.end) {
					curr.end = i.end;
				}
			}
		}
		result.add(curr);

		return result;
	}

	public static void main(String[] args) {
		Solution_IntervalMerge solution_IntervalMerge = new Solution_IntervalMerge();
		System.out.println(solution_IntervalMerge.merge(Arrays.asList(new Interval[] { new Interval(2, 6), new Interval(8, 10), new Interval(1, 3), new Interval(15, 18) })));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
