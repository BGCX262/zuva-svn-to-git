package leetcode;
public class Solution_longestPalindrome {
	public String longestPalindrome(String s) {
		int max = 0, maxLeft = 0, maxRight = 0, i, j, k, step = 1;
		if (s.length() == 1) {
			return s;
		}
		int len = s.length();
		for (k = 0; k < len; k++) {
			for (step = 0; k - step >= 0 && k + step < len; step++) {
				i = k - step;
				j = k + step;
				char c1 = s.charAt(i);
				char c2 = s.charAt(j);
				if (c1 == c2) {
					if (step * 2 + 1 > max) {
						max = step * 2 + 1;
						maxLeft = i;
						maxRight = j;
					}
				} else {
					break;
				}
			}
			for (step = 0; k - step >= 0 && k + step - 1 < len; step++) {
				i = k - step;
				if (step == 0) {
					j = k;
				} else {
					j = k + step - 1;
				}

				char c1 = s.charAt(i);
				char c2 = s.charAt(j);
				if (c1 == c2) {
					if (step * 2 > max) {
						max = step * 2;
						maxLeft = i;
						maxRight = j;
					}
				} else {
					break;
				}
			}
		}
		return s.substring(maxLeft, maxRight + 1);
	}

	public static void main(String[] args) throws Exception {
		Solution_longestPalindrome solution_longestPalindrome = new Solution_longestPalindrome();
		System.out.println(solution_longestPalindrome.longestPalindrome("bb"));
	}
}