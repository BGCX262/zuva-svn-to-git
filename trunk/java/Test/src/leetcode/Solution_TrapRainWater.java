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

import javax.swing.border.Border;
import javax.swing.text.ChangedCharSetException;

//class ListNode {
//	int val;
//	ListNode next;
//
//	ListNode(int x) {
//		val = x;
//		next = null;
//	}
//}

public class Solution_TrapRainWater {
	public int trap(int[] A) {
		if (A.length == 0)
			return 0;

		int leftMax = 0, rightMax = 0;
		int left = 0, right = A.length - 1;
		int result = 0;
		while (left <= right) {
			if (A[left] < A[right]) {
				if (A[left] < leftMax) {
					result += leftMax - A[left];
				} else {
					leftMax = A[left];
				}
				left++;
			} else {
				if (A[right] < rightMax) {
					result += rightMax - A[right];
				} else {
					rightMax = A[right];
				}
				right--;
			}
		}

		return result;
	}

	public static void main(String[] args) {
		Solution_TrapRainWater solution_TrapRainWater = new Solution_TrapRainWater();
		System.out.println(solution_TrapRainWater.trap(new int[] { 0,1,0,2,1,0,1,3,2,1,2,1 }));
	}
}
