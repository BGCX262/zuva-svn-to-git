package leetcode;
import java.util.ArrayList;
import java.util.List;

public class Solution_ZigZagConversion {

	public String convert(String s, int nRows) {
		int i;
		List<StringBuilder> list = new ArrayList<StringBuilder>();
		for (i = 0; i < nRows; i++) {
			list.add(new StringBuilder());
		}
		int direction = 1;
		int listIndex = 0;
		for (i = 0; i < s.length(); i++) {
			list.get(listIndex).append(s.charAt(i));
			if (list.size() == 1) {
				direction = 0;
			} else if (listIndex == list.size() - 1) {
				direction = -1;
			} else if (listIndex == 0) {
				direction = 1;
			}
			listIndex = listIndex + direction;
		}
		StringBuilder sbBuilder = new StringBuilder();
		for (StringBuilder sb : list) {
			sbBuilder.append(sb.toString());
		}
		return sbBuilder.toString();
	}

	public static void main(String[] args) {
		Solution_ZigZagConversion solution_ZigZagConversion = new Solution_ZigZagConversion();
		System.out.println(solution_ZigZagConversion.convert("AB", 1));
		System.out.println(solution_ZigZagConversion.convert("PAYPALISHIRING", 3));
	}

}
