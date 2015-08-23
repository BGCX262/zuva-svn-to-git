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

public class Solution_CountAnySay {
	private String count(String nStr) {
		StringBuilder sb = new StringBuilder();
		int i, j;
		for (i = 0; i < nStr.length();) {
			for (j = i; j < nStr.length() && nStr.charAt(i) == nStr.charAt(j); j++) {
			}
			sb.append(j - i).append(nStr.charAt(i));
			i = j;
		}
		return sb.toString();

	}

	public String countAndSay(int n) {
		String s = "1";
		n--;
		for (int i = 0; i < n; i++) {
			s = count(s);
		}
		return s;
	}

	public static void main(String[] args) {
		Solution_CountAnySay solution_CountAnySay = new Solution_CountAnySay();
		System.out.println(solution_CountAnySay.countAndSay(3));
	}
}
