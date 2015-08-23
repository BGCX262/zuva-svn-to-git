package leetcode;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class Solution_atoi {
	public int atoi(String str) {
		boolean isPositive = false;
		boolean isNegative = false;
		boolean validStart = false;
		boolean validEnd = false;
		StringBuilder sb = new StringBuilder();
		for (char c : str.trim().toCharArray()) {
			if (validEnd) {
				break;
			}
			if (!validStart && c == '+') {
				isPositive = true;
				validStart = true;
				continue;
			}
			if (!validStart && c == '-') {
				isNegative = true;
				validStart = true;
				continue;
			}
			if (c >= '0' && c <= '9') {
				if (!validStart) {
					validStart = true;
				}
				sb.append(c);
			} else {
				if (validStart) {
					validEnd = true;
				} else {
					return 0;
				}
			}
		}
		str = sb.toString();
		if ((isPositive && isNegative) || str.length() == 0) {
			return 0;
		}
		BigInteger re = new BigInteger(isNegative ? "-" + str : str);
		BigInteger max = new BigInteger(new Integer(Integer.MAX_VALUE).toString());
		BigInteger min = new BigInteger(new Integer(Integer.MIN_VALUE).toString());
		if (re.compareTo(min) < 0) {
			return min.intValue();
		} else if (re.compareTo(max) > 0) {
			return max.intValue();
		}
		return re.intValue();
	}

	public int atoi_useRegExp(String str) {
		boolean isPositive = false;
		boolean isNegative = false;
		if (str.indexOf("+") >= 0) {
			isPositive = true;
		}
		if (str.indexOf("-") >= 0) {
			isNegative = true;
		}
		str = str.replaceAll("[^0-9]", "");
		if ((isPositive && isNegative) || str.length() == 0) {
			return 0;
		}
		BigInteger re = new BigInteger(isNegative ? "-" + str : str);
		BigInteger max = new BigInteger(new Integer(Integer.MAX_VALUE).toString());
		BigInteger min = new BigInteger(new Integer(Integer.MIN_VALUE).toString());
		if (re.compareTo(min) < 0) {
			return min.intValue();
		} else if (re.compareTo(max) > 0) {
			return max.intValue();
		}
		return re.intValue();
	}

	public static void main(String[] args) {
		Solution_atoi solution_atoi = new Solution_atoi();
		System.out.println(solution_atoi.atoi(" asdf123 "));
		System.out.println(solution_atoi.atoi("aasd-2342"));
		System.out.println(solution_atoi.atoi(""));
		System.out.println(solution_atoi.atoi("123"));
		System.out.println(solution_atoi.atoi("  ++c"));
		System.out.println(solution_atoi.atoi("  -0012a42"));
		System.out.println(solution_atoi.atoi("-2147483649"));
		System.out.println(solution_atoi.atoi("   - 321"));
		System.out.println(solution_atoi.atoi(" b11228552307"));
	}

}
