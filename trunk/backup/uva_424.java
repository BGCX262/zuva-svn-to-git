import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.StringTokenizer;

public class Main {
	public static boolean debug = false;

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		if (args.length > 0)
			debug = true;
		List<String> nums = new ArrayList<String>();

		while (cin.hasNext()) {
			String line = cin.nextLine().trim();
			if (line.equals("0"))
				break;
			nums.add(line);
		}

		String result = nums.get(0);
		for (int i = 1; i < nums.size(); i++) {
			result = add(result, nums.get(i));
		}
		System.out.println(result);
	}

	static public String add(String s1, String s2) {
		StringBuilder result = new StringBuilder();
		int i, j, borrow = 0;

		for (i = s1.length() - 1, j = s2.length() - 1; i >= 0 && j >= 0; i--, j--) {
			int n1 = Integer.parseInt("" + s1.charAt(i));
			int n2 = Integer.parseInt("" + s2.charAt(j));
			int sum = n1 + n2 + borrow;
			borrow = (sum) / 10;
			result.append(sum % 10);
		}

		if (i >= 0) {
			for (; i >= 0; i--) {
				int n1 = Integer.parseInt("" + s1.charAt(i));
				int n2 = 0;
				int sum = n1 + n2 + borrow;
				borrow = (sum) / 10;
				result.append(sum % 10);
			}
		}
		if (j >= 0) {
			for (; j >= 0; j--) {
				int n1 = 0;
				int n2 = Integer.parseInt("" + s2.charAt(j));
				int sum = n1 + n2 + borrow;
				borrow = (sum) / 10;
				result.append(sum % 10);
			}
		}
		if (borrow > 0)
			result.append(borrow);
		return result.reverse().toString();
	}
}