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

public class Solution_WildcardMatching {
	// private boolean match(String s, int sPos, String p, int pPos) {
	// if (sPos >= s.length() && pPos >= p.length()) {
	// return true;
	// } else if (sPos >= s.length() || pPos >= p.length()) {
	// return false;
	// }
	// char sChar = s.charAt(sPos);
	// char pChar = p.charAt(pPos);
	// if (pChar == '?') {
	// return match(s, sPos + 1, p, pPos + 1);
	// } else if (pChar == '*') {
	// for (int i = sPos; i <= s.length(); i++) {
	// if (match(s, i, p, pPos + 1)) {
	// return true;
	// }
	// }
	// } else {
	// if (pChar == sChar) {
	// return match(s, sPos + 1, p, pPos + 1);
	// }
	// }
	//
	// return false;
	// }
	//

	public boolean isMatch(String str, String pattern) {
		int s = 0, p = 0, match = 0, starIdx = -1;
		while (s < str.length()) {
			// advancing both pointers
			if (p < pattern.length() && (pattern.charAt(p) == '?' || str.charAt(s) == pattern.charAt(p))) {
				s++;
				p++;
			}
			// * found, only advancing pattern pointer
			else if (p < pattern.length() && pattern.charAt(p) == '*') {
				starIdx = p;
				match = s;
				p++;
			}
			// last pattern pointer was *, advancing string pointer
			else if (starIdx != -1) {
				p = starIdx + 1;
				match++;
				s = match;
			}
			// current pattern pointer is not star, last patter pointer was not
			// *
			// characters do not match
			else
				return false;
		}

		// check for remaining characters in pattern
		while (p < pattern.length() && pattern.charAt(p) == '*')
			p++;

		return p == pattern.length();
	}

	public static void main(String[] args) {
		Solution_WildcardMatching solution_WildcardMatching = new Solution_WildcardMatching();
		System.out.println(solution_WildcardMatching.isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b"));
	}
}
