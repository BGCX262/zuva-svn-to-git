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

public class Solution_MaxSubArray {

	private Sub max(Sub[] sub) {
		int max = sub[0].sum;
		Sub maxSub = sub[0];
		for (Sub s : sub) {
			if (s != null && s.sum > max) {
				maxSub = s;
				max = s.sum;
			}
		}
		return maxSub;
	}

	private Sub merge(int A[], Sub[] subArr) {
		Sub sub = new Sub();
		sub.left = subArr[0].left;
		sub.right = subArr[subArr.length - 1].right;
		for (int i = sub.left; i <= sub.right; i++) {
			sub.sum += A[i];
		}
		return sub;
	}

	private class Sub {
		public int left, right, sum;

		public String toString() {
			return left + " " + right + " sum " + sum;
		}
	}

	private Sub dp(int[] A, int left, int right) {
		Sub sub = new Sub();
		if (left > right) {
			return null;
		} else if (left == right) {
			sub.left = left;
			sub.right = right;
			sub.sum = A[left];
			return sub;
		} else if (left == right - 1) {
			int sum = A[left] + A[right];
			if (sum >= A[left] && sum >= A[right]) {
				sub.left = left;
				sub.right = right;
				sub.sum = sum;
			} else {
				if (A[left] < A[right]) {
					sub.left = sub.right = right;
					sub.sum = A[right];
				} else {
					sub.left = sub.right = left;
					sub.sum = A[left];
				}
			}
			return sub;
		}

		int mid = (left + right) / 2;
		Sub leftSub = dp(A, left, mid);
		Sub rightSub = dp(A, mid + 1, right);
		Sub middleSub = dp(A, leftSub.right + 1, rightSub.left - 1);
		if (middleSub == null) {
			sub = max(new Sub[] { leftSub, rightSub, merge(A, new Sub[] { leftSub, rightSub }) });
		} else {
			sub = max(new Sub[] { leftSub, rightSub, middleSub, merge(A, new Sub[] { leftSub, middleSub }), merge(A, new Sub[] { middleSub, rightSub }),
					merge(A, new Sub[] { leftSub, middleSub, rightSub }) });
		}
		return sub;
	}

	public int maxSubArray(int[] A) {
		Sub sub = dp(A, 0, A.length - 1);
		return sub.sum;
	}

	public static void main(String[] args) {
		Solution_MaxSubArray solution_MaxSubArray = new Solution_MaxSubArray();
		System.out.println(solution_MaxSubArray.maxSubArray(new int[] { -2, 1, -3, 4, -1, 2, 1, -5, 4 }));
	}
}
