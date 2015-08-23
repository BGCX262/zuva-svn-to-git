package leetcode;
import java.util.ArrayList;
import java.util.List;

public class Solution_reverseString {

	public int reverse(int x) {
		boolean isNegative = x < 0 ? true : false;
		x = Math.abs(x);
		String rev = new StringBuilder(Integer.toString(x)).reverse().toString();
		if (isNegative) {
			return 0 - Integer.parseInt(rev);
		} else {
			return Integer.parseInt(rev);
		}
	}

	public static void main(String[] args) {
		Solution_reverseString solution_reverseString = new Solution_reverseString();
		System.out.println(solution_reverseString.reverse(123));
		System.out.println(solution_reverseString.reverse(-123));
	}

}
