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

public class Solution_NextPermutation {

	public void nextPermutation(int[] num) {
		for (int i = num.length - 1; i > 0; i--) {
			if (num[i - 1] < num[i]) {
				Arrays.sort(num, i, num.length);
				for (int j = i; j < num.length; j++) {
					if (num[j] > num[i - 1]) {
						int t = num[i - 1];
						num[i - 1] = num[j];
						num[j] = t;
						return;
					}
				}
				return;
			}
		}
		Arrays.sort(num);
		return;
	}

	public static void main(String[] args) {
		Solution_NextPermutation solution_NextPermutation = new Solution_NextPermutation();
		solution_NextPermutation.nextPermutation(new int[] { 1, 3, 2 });
		//System.out.println(solution.nextPermutation(new int[] { 1, 3, 2 }));
	}
}
