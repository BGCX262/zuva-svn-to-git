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

public class Solution_LengthOfLastWord {

	public int lengthOfLastWord(String s) {
		int len = 0;
		boolean findLastWord = false;
		if (s != null && !s.trim().equalsIgnoreCase("")) {
			for (int i = s.length() - 1; i >= 0; i--) {
				char c = s.charAt(i);
				if (findLastWord && c == ' ') {
					break;
				} else {
					if (c == ' ') {
						continue;
					} else {
						len++;
						findLastWord = true;
					}
				}
			}
		}
		return len;
	}

	public static void main(String[] args) {
		Solution_LengthOfLastWord solution_LengthOfLastWord = new Solution_LengthOfLastWord();
		System.out.println(solution_LengthOfLastWord.lengthOfLastWord(" "));

		// System.out.println(solution.merge(new int[] { 3, 2, 1, 0, 4 }));

	}
}
