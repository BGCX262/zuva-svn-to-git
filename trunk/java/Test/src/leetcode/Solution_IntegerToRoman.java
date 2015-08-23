package leetcode;
public class Solution_IntegerToRoman {
	static private char[][] romanArr = { { 'I', 'V' }, { 'X', 'L' }, { 'C', 'D' }, { 'M', ' ' } };

	public String getRomanChar(char c, int offset) {
		char one = romanArr[offset][0];
		char five = romanArr[offset][1];
		
		switch (c - '0') {
		case 0:
			return "";
		case 1:
			return "" + one;
		case 2:
			return "" + one + one;
		case 3:
			return "" + one + one + one;
		case 4:
			return "" + one + five;
		case 5:
			return "" + five;
		case 6:
			return "" + five + one;
		case 7:
			return "" + five + one + one;
		case 8:
			return "" + five + one + one + one;
		case 9:
			char nextOne = romanArr[offset + 1][0];
			return "" + one + nextOne;
		default:
			break;
		}
		return null;
	}

	public String intToRoman(int num) {
		String sNum = new Integer(num).toString();
		StringBuilder sb = new StringBuilder();
		char[] cArr = sNum.toCharArray();
		for (int i = 0; i < cArr.length; i++) {
			sb.append(getRomanChar(cArr[i], cArr.length - 1 - i));
		}
		return sb.toString();
	}

	public static void main(String[] args) {
		Solution_IntegerToRoman solution_IntegerToRoman = new Solution_IntegerToRoman();
		System.out.println(solution_IntegerToRoman.intToRoman(23));
	}

}
