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

public class Solution_MultiplyBigNumber {
	private String mul(String s, int n) {
		StringBuilder sb = new StringBuilder();
		int b = 0;
		for (int i = s.length() - 1; i >= 0; i--) {
			int result = (s.charAt(i) - '0') * n + b;
			sb.insert(0, result > 0 ? new Integer(result % 10).toString() : "0");
			b = result / 10;
		}
		if (b > 0) {
			sb.insert(0, new Integer(b).toString());
		}
		return sb.toString();
	}

	private String add(String s1, String s2) {
		StringBuilder sb = new StringBuilder();
		int i1 = s1.length() - 1, i2 = s2.length() - 1;
		int b = 0;
		while (i1 >= 0 && i2 >= 0) {
			int result = s1.charAt(i1) - '0' + s2.charAt(i2) - '0' + b;
			sb.insert(0, new Integer(result % 10).toString());
			b = result / 10;
			i1--;
			i2--;
		}
		while (i1 >= 0) {
			int result = s1.charAt(i1) - '0' + b;
			sb.insert(0, new Integer(result % 10).toString());
			b = result / 10;
			i1--;
		}
		while (i2 >= 0) {
			int result = s2.charAt(i2) - '0' + b;
			sb.insert(0, new Integer(result % 10).toString());
			b = result / 10;
			i2--;
		}
		if (b > 0) {
			sb.insert(0, new Integer(b).toString());
		}
		return sb.toString();
	}

	public String multiply(String num1, String num2) {
		StringBuilder sb = new StringBuilder();
		for (int i = num2.length() - 1; i >= 0; i--) {
			StringBuilder curr = new StringBuilder(mul(num1, num2.charAt(i) - '0'));
			for (int j = 0; j < num2.length() - 1 - i; j++) {
				curr.append('0');
			}
			String result = add(sb.toString(), curr.toString());
			sb.setLength(0);
			sb.append(result);
		}
		StringBuilder result = new StringBuilder();
		for (int i = 0; i < sb.length(); i++) {
			if (sb.charAt(i) != '0') {
				result.append(sb.substring(i));
				break;
			}
		}
		if (result.length() == 0) {
			result.append("0");
		}
		return result.toString();
	}

	public static void main(String[] args) {
		Solution_MultiplyBigNumber solution_MultiplyBigNumber = new Solution_MultiplyBigNumber();
		System.out.println(solution_MultiplyBigNumber.multiply("123456789", "987654321"));
	}
}
