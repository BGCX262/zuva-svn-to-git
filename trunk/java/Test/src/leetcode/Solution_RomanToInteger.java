package leetcode;
public class Solution_RomanToInteger {
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

	public int[] getInt(String s, int index) {
		for (int i = 0; i < romanArr.length; i++) {
			char one = romanArr[i][0];
			char nextOne = i + 1 < romanArr.length ? romanArr[i + 1][0] : ' ';
			char five = romanArr[i][1];
			char currChar = s.charAt(index);
			char nextChar = index + 1 < s.length() ? s.charAt(index + 1) : ' ';
			char nextNextChar = index + 2 < s.length() ? s.charAt(index + 2) : ' ';
			char nextNextNextChar = index + 3 < s.length() ? s.charAt(index + 3) : ' ';

			int base = 1;
			for (int j = 0; j < i; j++) {
				base *= 10;
			}

			if (currChar == one) {
				if (nextChar != ' ' && nextChar == one) {
					if (nextNextChar != ' ' && nextNextChar == one) {
						return new int[] { 3 * base, 3 };
					}
					return new int[] { 2 * base, 2 };
				}
				if (nextChar != ' ' && nextChar == five) {
					return new int[] { 4 * base, 2 };
				}
				if (nextChar != ' ' && nextChar == nextOne) {
					return new int[] { 9 * base, 2 };
				}
				return new int[] { 1 * base, 1 };
			}
			if (currChar == five) {
				if (nextChar != ' ' && nextChar == one) {
					if (nextNextChar != ' ' && nextNextChar == one) {
						if (nextNextNextChar != ' ' && nextNextNextChar == one) {
							return new int[] { 8 * base, 4 };
						}
						return new int[] { 7 * base, 3 };
					}
					return new int[] { 6 * base, 2 };

				}
				return new int[] { 5 * base, 1 };
			}
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

	public int romanToInt(String s) {
		int result = 0;
		for (int i = 0; i < s.length();) {
			int[] re = getInt(s, i);
			result += re[0];
			i += re[1];
		}
		return result;
	}

	public static void main(String[] args) {
		Solution_RomanToInteger solution_RomanToInteger = new Solution_RomanToInteger();
		System.out.println(solution_RomanToInteger.romanToInt("DCXXI"));
	}

}
