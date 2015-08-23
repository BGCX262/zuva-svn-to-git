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

//class Interval {
//	int start;
//	int end;
//
//	Interval() {
//		start = 0;
//		end = 0;
//	}
//
//	Interval(int s, int e) {
//		start = s;
//		end = e;
//	}
//}

public class Solution_IntervalInsert {

	private boolean isOverlap(Interval i1, Interval i2) {
		if (i1.end < i2.start || i2.end < i1.start) {
			return false;
		}
		return true;
	}

	public List<Interval> insert(List<Interval> intervals, Interval newInterval) {
		List<Interval> result = new ArrayList<Interval>();
		boolean hasInserted = false;
		for (Interval interval : intervals) {
			if (hasInserted) {
				result.add(interval);
			} else {
				if (isOverlap(interval, newInterval)) {
					newInterval.start = Math.min(interval.start, newInterval.start);
					newInterval.end = Math.max(interval.end, newInterval.end);
				} else {
					if (interval.start < newInterval.start) {
						result.add(interval);
					} else {
						if (!hasInserted) {
							result.add(newInterval);
							result.add(interval);
							hasInserted = true;
						}
					}
				}
			}
		}
		if (!hasInserted) {
			result.add(newInterval);
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_IntervalInsert solution_IntervalInsert = new Solution_IntervalInsert();
		System.out.println(solution_IntervalInsert.insert(Arrays.asList(new Interval[] { new Interval(1, 3), new Interval(6, 9) }), new Interval(2, 5)));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
