package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Solution_LetterCombinationsPhoneNumber {
	List<String> result = new ArrayList<String>();
	String[] letter = new String[] { " ", "_", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

	void dfs(String digits, int index, StringBuilder sb) {
		if (index == digits.length()) {
			result.add(sb.toString());
			return;
		}
		char num = digits.charAt(index);
		if (num >= '0' && num <= '9') {
			for (char c : letter[num - '0'].toCharArray()) {
				if (c != '_') {
					sb.append(c);
				}
				dfs(digits, index + 1, sb);
				if (c != '_') {
					sb.deleteCharAt(sb.length() - 1);
				}
			}
		}
	}

	public List<String> letterCombinations(String digits) {
		dfs(digits, 0, new StringBuilder());
		return result;
	}

	public static void main(String[] args) {
		Solution_LetterCombinationsPhoneNumber solution_LetterCombinationsPhoneNumber = new Solution_LetterCombinationsPhoneNumber();
		System.out.println(solution_LetterCombinationsPhoneNumber.letterCombinations("203"));
		// System.out.println(solution.fourSum(new int[] { 1, 0, -1, 0, -2, 2 },
		// 0));

	}
}
