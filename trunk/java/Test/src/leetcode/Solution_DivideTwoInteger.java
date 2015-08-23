package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.EmptyStackException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
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

public class Solution_DivideTwoInteger {

	public int divide(int dividend, int divisor) {
		long absDivident = Math.abs((long) dividend);
		long absDivisor = Math.abs((long) divisor);
		long result = 0;
		long currentDivisor = absDivisor;
		long base = 1;
		while (absDivident >= absDivisor) {
			if (absDivident >= currentDivisor) {
				absDivident -= currentDivisor;
				result += base;
				currentDivisor = currentDivisor << 1;
				base = base << 1;
			} else {
				currentDivisor = currentDivisor >> 1;
				base = base >> 1;
			}
		}
		if ((dividend >= 0 && divisor >= 0) || (dividend <= 0 && divisor <= 0)) {
			return (int)result;
		}
		return 0 - (int)result;
	}

	public static void main(String[] args) {
		Solution_DivideTwoInteger solution_DivideTwoInteger = new Solution_DivideTwoInteger();
		// System.out.println(solution.divide(2, 1));
		// System.out.println(solution.divide(2147483647, 1));
		//System.out.println(solution.divide(-1010369383, -2147483648));
		System.out.println(solution_DivideTwoInteger.divide(-2147483648, 1));
		
	}
}
