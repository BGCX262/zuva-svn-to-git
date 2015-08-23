package backup;

import java.util.Arrays;
import java.util.Collections;

public class Solution1_IntegerBitAnd {
	private int bitAnd(int M, int N) {
		StringBuilder mStringBuilder = new StringBuilder(Integer.toBinaryString(M));
		String nString = Integer.toBinaryString(N);
		for (int i = 0; i < (nString.length() - mStringBuilder.length()); i++) {
			mStringBuilder.insert(0, "0");
		}
		String mString = mStringBuilder.toString();
		int mStringLen = mString.length();
		for (int i = 0; i < mStringLen; i++) {
			char mChar = mString.charAt(i);
			char nChar = nString.charAt(i);
			if (mChar == '1' && nChar == '1') {
				continue;
			} else {
				for (int j = i; j < mStringLen; j++) {
					mStringBuilder.setCharAt(j, '0');
				}
				break;
			}
		}
		return Integer.parseInt(mStringBuilder.toString(), 2);
	}

	public int solution(int M, int N) {
		// M <= N
		int mABS = Math.abs(M);
		int nABS = Math.abs(N);
		if (mABS > nABS) {
			int t = mABS;
			mABS = nABS;
			nABS = t;
		}
		return bitAnd(mABS, nABS);
	}

	public static void main(String[] args) {
		Solution1_IntegerBitAnd solution = new Solution1_IntegerBitAnd();
		System.out.println(solution.solution(5, 7));
	}
}
