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

import javax.naming.spi.DirStateFactory.Result;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

public class Solution_JumpGameII {

	public int jump(int[] A) {
		if (A.length == 1) {
			return 0;
		} else if (A.length == 2) {
			return 1;
		}

		int i = 0;
		int jump = 0;
		for (; i < A.length - 1;) {
			jump++;
			if (i + A[i] >= A.length - 1) {
				break;
			}
			int max = A[i + 1] + i + 1;
			int maxIdx = i + 1;
			for (int j = i + 1; (j - i) <= A[i] && j < A.length; j++) {
				if (A[j] + j >= max) {
					max = A[j] + j;
					maxIdx = j;
				}
			}
			i = maxIdx;
		}

		return jump;
	}

	public static void main(String[] args) {
		Solution_JumpGameII solution_JumpGameII = new Solution_JumpGameII();
		// System.out.println(solution.jump(new int[] { 1, 2, 1, 1, 1 }));
		System.out.println(solution_JumpGameII.jump(new int[] { 2, 3, 1, 1, 4 }));
	}
}
