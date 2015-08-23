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

public class Solution_POW {

	public double pow(double x, int n) {
		if (n == 0) {
			return 1;
		} else if (n == 1) {
			return x;
		}
		long num = Math.abs(n);
		double result = Math.abs(x);
		double base = Math.abs(x);
		long exp = 1;
		long curr = 1;
		while (curr < num) {
			if (exp + curr <= num) {
				result = result * base;
				curr += exp;
				exp *= 2;
				base *= base;
			} else {
				exp /= 2;
				base = Math.sqrt(base);
			}
		}
		if (n < 0) {
			result = 1 / result;
		}
		if (x < 0 && num % 2 != 0) {
			result = 0 - result;
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_POW solution_POW = new Solution_POW();
		System.out.println(solution_POW.pow(34.00515, -3));

	}
}
