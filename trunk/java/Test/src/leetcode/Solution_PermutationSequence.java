package leetcode;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

//class ListNode {
//	int val;
//	ListNode next;
//s
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

public class Solution_PermutationSequence {

	private Integer factorial(int n) {
		int fact = 1; // this will be the result
		for (int i = 1; i <= n; i++) {
			fact *= i;
		}
		return fact;
	}

	private Integer nextPermutateChar(Set<Integer> nums, int range, int k) {
		if (nums.size() == 1) {
			return nums.iterator().next();
		}
		Iterator<Integer> iterator = nums.iterator();
		for (int i = 0; i < k / range ; i++) {
			iterator.next();
		}
		return iterator.next();
	}

	public String getPermutation(int n, int k) {
		StringBuilder sb = new StringBuilder();
		Set<Integer> nums = new TreeSet<Integer>();
		for (int i = 1; i <= n; i++) {
			nums.add(i);
		}
		int range;
		k--;
		for (int i = n - 1; i >= 0; i--) {
			range = factorial(i);
			Integer integer = nextPermutateChar(nums, range, k);
			nums.remove(integer);
			k = k % range;
			sb.append(integer);
		}

		return sb.toString();
	}

	public static void main(String[] args) {
		Solution_PermutationSequence solution_PermutationSequence = new Solution_PermutationSequence();
		System.out.println(solution_PermutationSequence.getPermutation(4, 8));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
