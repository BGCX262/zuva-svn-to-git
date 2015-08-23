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

public class Solution_FirstMissingPositive {
	public int firstMissingPositive(int[] A) {
		Arrays.sort(A);
		int posIndex = Arrays.binarySearch(A, 0);
		int pos = 1;
		if (posIndex < 0) {
			posIndex = Math.abs(posIndex) - 1;
		} else {
			while (posIndex < A.length && A[posIndex] == 0)
				posIndex++;
		}
		for (int i = posIndex; i < A.length;) {
			if (A[i] != pos) {
				return pos;
			}
			pos++;
			int j = i + 1;
			while (j < A.length && A[j] == A[i])
				j++;
			i = j;

		}
		return pos;
	}

	public static void main(String[] args) {
		Solution_FirstMissingPositive solution_FirstMissingPositive = new Solution_FirstMissingPositive();
		System.out.println(solution_FirstMissingPositive.firstMissingPositive(new int[] { 0, 2, 2, 4, 0, 1, 0, 1, 3 }));
	}
}
