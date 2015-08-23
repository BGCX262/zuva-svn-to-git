package leetcode;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class Solution_isPalindrome {

	public boolean isPalindrome(int x) {
		if (x < 0)
			return false;
		int n = (int) Math.floor(Math.log10(x)) + 1;
		for (int i = 0; i < n / 2; i++) {
			int t1 = firstDigit(x, i, n);
			int t2 = firstDigit(x, n - 1 - i, n);
			if (t1 != t2) {
				return false;
			}
		}
		return true;
	}

	public int firstDigit(int x, int offset, int n) {
		if (x == 0)
			return 0;
		int base = (int) Math.pow(10, n - 1 - offset);
		x = x / base;
		int size = (int) Math.floor(Math.log10(x)) + 1;
		for (int i = 0; i < size - 1; i++) {
			base = (int) Math.pow(10, size - 1 - i);
			x = x % base;
		}
		return x;
	}

	public static void main(String[] args) {
		Solution_isPalindrome solution_isPalindrome = new Solution_isPalindrome();
		System.out.println(solution_isPalindrome.isPalindrome(12321));
		System.out.println(solution_isPalindrome.isPalindrome(1221));
		System.out.println(solution_isPalindrome.isPalindrome(1000021));
	}

}
