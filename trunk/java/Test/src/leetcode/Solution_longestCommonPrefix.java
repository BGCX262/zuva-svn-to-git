package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class Solution_longestCommonPrefix {
	public String longestCommonPrefix(String[] strs) {
		if (strs.length < 1) {
			return "";
		} else if (strs.length == 1) {
			return strs[0];
		}

		String max = "";
		boolean end = false;
		int i;
		for (i = 0;; i++) {
			if (i > strs[0].length() - 1) {
				break;
			}
			char c = strs[0].charAt(i);
			for (String s : strs) {
				if (i > s.length() - 1 || s.charAt(i) != c) {
					end = true;
					break;
				}
			}
			if (end == true) {
				break;
			}
		}
		if (i > 0) {
			max = strs[0].substring(0, i);
		}
		return max;
	}

	public static void main(String[] args) {
		Solution_longestCommonPrefix solution_longestCommonPrefix = new Solution_longestCommonPrefix();
		System.out.println(solution_longestCommonPrefix.longestCommonPrefix(new String[] { "cds", "cd" }));
		System.out.println(solution_longestCommonPrefix.longestCommonPrefix(new String[] { "a", "a", "b" }));
		System.out.println(solution_longestCommonPrefix.longestCommonPrefix(new String[] {}));
		System.out.println(solution_longestCommonPrefix.longestCommonPrefix(new String[] { "", "" }));
		System.out.println(solution_longestCommonPrefix.longestCommonPrefix(new String[] { "a" }));
		System.out.println(solution_longestCommonPrefix.longestCommonPrefix(new String[] { "c", "c" }));
	}
}
