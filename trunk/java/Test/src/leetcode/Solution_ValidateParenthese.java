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

public class Solution_ValidateParenthese {
	public boolean isValid(String s) {
		Stack<Character> stack = new Stack<Character>();
		for (char c : s.toCharArray()) {
			if (c == '(' || c == '{' || c == '[') {
				stack.push(c);
			} else {
				try {
					char left = stack.pop();
					if (c == ')' && left == '(') {
						continue;
					}
					if (c == '}' && left == '{') {
						continue;
					}
					if (c == ']' && left == '[') {
						continue;
					}
					return false;
				} catch (EmptyStackException ex) {
					return false;
				}
			}
		}
		return stack.size() > 0 ? false : true;
	}

	public static void main(String[] args) {
		Solution_ValidateParenthese solution_ValidateParenthese = new Solution_ValidateParenthese();
		System.out.println(solution_ValidateParenthese.isValid("{()[]{}}"));
		System.out.println(solution_ValidateParenthese.isValid("()[]{}"));
		System.out.println(solution_ValidateParenthese.isValid("([)]"));
	}
}
