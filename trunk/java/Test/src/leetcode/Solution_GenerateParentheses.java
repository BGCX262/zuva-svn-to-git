package leetcode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.EmptyStackException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Stack;

public class Solution_GenerateParentheses {
	public List<String> generateParenthesis(int n) {
		List<String> result = new ArrayList<String>();
		add(result, "", n, 0);
		return result;
	}

	private void add(List<String> result, String s, int left, int right) {
		if (left == 0 && right == 0) {
			result.add(s);
			return;
		}
		if (right > 0) {
			add(result, s + ")", left, right - 1);
		}
		if (left > 0) {
			add(result, s + "(", left - 1, right + 1);
		}
	}

	public static void main(String[] args) {
		Solution_GenerateParentheses solution_GenerateParentheses = new Solution_GenerateParentheses();
		System.out.println(solution_GenerateParentheses.generateParenthesis(1));
	}
}
