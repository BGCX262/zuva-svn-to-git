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

public class Solution_JumpGame {

	public boolean canJump(int[] A) {
		int max = 0;
		for (int i = 0; i < A.length; i++) {
			if (max >= A.length - 1) {
				return true;
			}
			if (i > max) {
				break;
			}
			if (A[i] + i > max) {
				max = i + A[i];
			}
		}

		return false;
	}

	public static void main(String[] args) {
		Solution_JumpGame solution_JumpGame = new Solution_JumpGame();
		System.out.println(solution_JumpGame.canJump(new int[] { 3,2,1,0,4}));

	}
}
